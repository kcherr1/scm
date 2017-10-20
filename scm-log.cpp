// Copyright (C) 2011-2012 Robert Kooima
//
// LIBSCM is free software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software
// Foundation; either version 2 of the License, or (at your option) any later
// version.
//
// This program is distributed in the hope that it will be useful, but WITH-
// OUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
// more details.

#include <stdio.h>
#include <stdlib.h>

#include <cstdarg>
#include <cstdio>

#include <iostream>
#include <fstream>

//------------------------------------------------------------------------------
static FILE* logfilec = NULL;

void scm_logopen(const char *path)
{
    if (logfilec == NULL)
    {
        logfilec = fopen(path, "w");
        fputs("<head></head><body style='background:black; color:#ddd; font-family:\"courier new\"'>", logfilec);
        fflush(logfilec);
    }
}

static char *add_break(const char *str)
{
    char *newstr = (char*)calloc(strlen(str) * 2, sizeof(char));
    int j = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] != '\n')
        {
            newstr[j++] = str[i];
        }
        else
        {
            strcat(newstr, "<br />");
            j += 6;
        }
    }
    newstr[j] = '\0';
    return newstr;
}

void scm_log(const char *fmt, ...)
{
#ifndef WIN32
    flockfile(stderr);
#endif
    {
        va_list  ap;
        va_start(ap, fmt);

        char *logmsg = (char*)calloc(1000, sizeof(char));
        vsprintf(logmsg, fmt, ap);
        sprintf(logmsg, "%s\n", logmsg);
        fputs(add_break(logmsg), logfilec);

        va_end(ap);

        fflush(logfilec);
    }
#ifndef WIN32
    funlockfile(stderr);
#endif
}

void scm_clog(const char *color, const char *fmt, ...)
{
#ifndef WIN32
    flockfile(stderr);
#endif
    {
        va_list  ap;
        va_start(ap, fmt);

        char *logmsg = (char*)calloc(1000, sizeof(char));
        vsprintf(logmsg, fmt, ap);
        sprintf(logmsg, "%s", logmsg);
        fprintf(logfilec, "<span style='color:%s'>%s</span><br />", color, add_break(logmsg));

        va_end(ap);

        fflush(logfilec);
    }
#ifndef WIN32
    funlockfile(stderr);
#endif
}

void scm_clognoflush(const char *color, const char *fmt, ...)
{
#ifndef WIN32
    flockfile(stderr);
#endif
    {
        va_list  ap;
        va_start(ap, fmt);

        char *logmsg = (char*)calloc(1000, sizeof(char));
        vsprintf(logmsg, fmt, ap);
        sprintf(logmsg, "%s", logmsg);
        fprintf(logfilec, "<span style='color:%s'>%s</span><br />", color, add_break(logmsg));

        va_end(ap);
    }
#ifndef WIN32
    funlockfile(stderr);
#endif
}

void scm_logflush()
{
    fflush(logfilec);
}

void scm_logclose(void)
{
    fputs("</body>", logfilec);
    fclose(logfilec);
}
//------------------------------------------------------------------------------
