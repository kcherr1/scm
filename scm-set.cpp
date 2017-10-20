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

#include <GL/glew.h>
#include <cassert>

#include "scm-set.hpp"
#include "scm-index.hpp"

//------------------------------------------------------------------------------

void scm_set::insert(scm_page page, int t)
{
    m[page] = t;
}

void scm_set::remove(scm_page page)
{
    m.erase(page);
}

// Search for the given page in this page set. If found, update the page entry
// with the current time t to indicate recent use.

scm_page scm_set::search(scm_page page, int t)
{
    std::map<scm_page, int>::iterator i = m.find(page);

    if (i != m.end())
    {
        scm_page p = i->first;

        remove(p);
        insert(p, t);
        return(p);
    }
    return scm_page();
}

// Eject a page from this set to accommodate the addition of a new page.
// t is the current cache time and i is the index of the incoming page.
// The general polity is LRU, but with considerations for time and priority
// that help mitigate thrashing.

scm_page scm_set::eject(int t, long long i)
{
    assert(!m.empty());

    // Determine the lowest priority and least-recently used pages.

    std::map<scm_page, int>::iterator a = m.end();
    std::map<scm_page, int>::iterator l = m.end();
    std::map<scm_page, int>::iterator e;

    for (e = m.begin(); e != m.end(); ++e)
    {
        if (a == m.end() || e->second < a->second) a = e;
        l = e;
    }

    // If the LRU page was not used in this scene or the last, eject it.
    // Otherwise consider the lowest-priority loaded page and eject if it
    // has lower priority than the incoming page.

    if (a != m.end() && a->second < t - 2)
    {
        scm_page page = a->first;
        m.erase(a);
        return page;
    }
    if (l != m.end() && i < l->first.i)
    {
        scm_page page = l->first;
        m.erase(l);
        return page;
    }
    return scm_page();
}

//------------------------------------------------------------------------------
