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

#include <cmath>

#ifdef _WIN32
#define _USE_MATH_DEFINES
#include <math.h>
#endif

#include "scm-index.hpp"



// Transform between a face-local vector u and a world vector v. ---------------

static inline void face_to_world(long long a, const double *u, double *v)
{
    switch (a)
    {
    case 0: v[0] = u[2]; v[1] = u[1]; v[2] = -u[0]; break;
    case 1: v[0] = -u[2]; v[1] = u[1]; v[2] = u[0]; break;
    case 2: v[0] = u[0]; v[1] = u[2]; v[2] = -u[1]; break;
    case 3: v[0] = u[0]; v[1] = -u[2]; v[2] = u[1]; break;
    case 4: v[0] = u[0]; v[1] = u[1]; v[2] = u[2]; break;
    case 5: v[0] = -u[0]; v[1] = u[1]; v[2] = -u[2]; break;
    }
}

static inline void world_to_face(long long a, const double *v, double *u)
{
    switch (a)
    {
    case 0: u[2] = v[0]; u[1] = v[1]; u[0] = -v[2]; break;
    case 1: u[2] = -v[0]; u[1] = v[1]; u[0] = v[2]; break;
    case 2: u[0] = v[0]; u[2] = v[1]; u[1] = -v[2]; break;
    case 3: u[0] = v[0]; u[2] = -v[1]; u[1] = v[2]; break;
    case 4: u[0] = v[0]; u[1] = v[1]; u[2] = v[2]; break;
    case 5: u[0] = -v[0]; u[1] = v[1]; u[2] = -v[2]; break;
    }
}

// Calculate the vector v toward (x, y) on root face a. ------------------------

void scm_vector(long long a, double y, double x, double *v)
{
    const double s = x * M_PI_2 - M_PI_4;
    const double t = y * M_PI_2 - M_PI_4;

    double u[3];

    u[0] = sin(s) * cos(t);
    u[1] = -cos(s) * sin(t);
    u[2] = cos(s) * cos(t);

    double k = 1.0 / sqrt(u[0] * u[0] + u[1] * u[1] + u[2] * u[2]);

    u[0] *= k;
    u[1] *= k;
    u[2] *= k;

    face_to_world(a, u, v);
}

// Calculate the root face a and coordinate (x, y) along vector v. -------------

void scm_locate(long long *a, double *y, double *x, const double *v)
{
    double u[3];

    u[0] = v[0];
    u[1] = v[1];
    u[2] = v[2];

    if (v[0] >= fabs(v[1]) && v[0] >= fabs(v[2])) *a = 0;
    else if (v[0] <= -fabs(v[1]) && v[0] <= -fabs(v[2])) *a = 1;
    else if (v[1] >= fabs(v[0]) && v[1] >= fabs(v[2])) *a = 2;
    else if (v[1] <= -fabs(v[0]) && v[1] <= -fabs(v[2])) *a = 3;
    else if (v[2] >= fabs(v[0]) && v[2] >= fabs(v[1])) *a = 4;
    else if (v[2] <= -fabs(v[0]) && v[2] <= -fabs(v[1])) *a = 5;

    world_to_face(*a, v, u);

    double s = -atan2(u[0], u[2]);
    double t = -atan2(u[1], u[2]);

    *x = (s + M_PI_4) / M_PI_2;
    *y = (t + M_PI_4) / M_PI_2;
}

// Determine the page to the north of page i. ----------------------------------

long long scm_page_north(long long i)
{
    long long l = scm_page_level(i);
    long long a = scm_page_root(i);
    long long r = scm_page_row(i);
    long long c = scm_page_col(i);

    long long n = 1LL << l, m = n - 1, t = m - c;

    if (r > 0) { r = r - 1; }
    else if (a == 0) { a = 2; r = t; c = m; }
    else if (a == 1) { a = 2; r = c; c = 0; }
    else if (a == 2) { a = 5; r = 0; c = t; }
    else if (a == 3) { a = 4; r = m; }
    else if (a == 4) { a = 2; r = m; }
    else { a = 2; r = 0; c = t; }

    return scm_page_index(a, l, r, c);
}

// Determine the page to the south of page i. ----------------------------------

long long scm_page_south(long long i)
{
    long long l = scm_page_level(i);
    long long a = scm_page_root(i);
    long long r = scm_page_row(i);
    long long c = scm_page_col(i);

    long long n = 1LL << l, m = n - 1, t = m - c;

    if (r < m) { r = r + 1; }
    else if (a == 0) { a = 3; r = c; c = m; }
    else if (a == 1) { a = 3; r = t; c = 0; }
    else if (a == 2) { a = 4; r = 0; }
    else if (a == 3) { a = 5; r = m; c = t; }
    else if (a == 4) { a = 3; r = 0; }
    else { a = 3; r = m; c = t; }

    return scm_page_index(a, l, r, c);
}

// Determine the page to the west of page i. -----------------------------------

long long scm_page_west(long long i)
{
    long long l = scm_page_level(i);
    long long a = scm_page_root(i);
    long long r = scm_page_row(i);
    long long c = scm_page_col(i);

    long long n = 1LL << l, m = n - 1, t = m - r;

    if (c > 0) { c = c - 1; }
    else if (a == 0) { a = 4; c = m; }
    else if (a == 1) { a = 5; c = m; }
    else if (a == 2) { a = 1; c = r; r = 0; }
    else if (a == 3) { a = 1; c = t; r = m; }
    else if (a == 4) { a = 1; c = m; }
    else { a = 0; c = m; }

    return scm_page_index(a, l, r, c);
}

// Determine the page to the east of page i. -----------------------------------

long long scm_page_east(long long i)
{
    long long l = scm_page_level(i);
    long long a = scm_page_root(i);
    long long r = scm_page_row(i);
    long long c = scm_page_col(i);

    long long n = 1LL << l, m = n - 1, t = m - r;

    if (c < m) { c = c + 1; }
    else if (a == 0) { a = 5; c = 0; }
    else if (a == 1) { a = 4; c = 0; }
    else if (a == 2) { a = 0; c = t; r = 0; }
    else if (a == 3) { a = 0; c = r; r = m; }
    else if (a == 4) { a = 0; c = 0; }
    else { a = 1; c = 0; }

    return scm_page_index(a, l, r, c);
}

// Calculate the four corner vectors of page i. --------------------------------

void scm_page_corners(long long i, double *v)
{
    long long l = scm_page_level(i);
    long long a = scm_page_root(i);
    long long r = scm_page_row(i);
    long long c = scm_page_col(i);

    long long n = 1LL << l;

    scm_vector(a, (double)(r + 0) / n, (double)(c + 0) / n, v + 0);
    scm_vector(a, (double)(r + 0) / n, (double)(c + 1) / n, v + 3);
    scm_vector(a, (double)(r + 1) / n, (double)(c + 0) / n, v + 6);
    scm_vector(a, (double)(r + 1) / n, (double)(c + 1) / n, v + 9);
}

// Calculate the center vector of page i. --------------------------------------

void scm_page_center(long long i, double *v)
{
    long long l = scm_page_level(i);
    long long a = scm_page_root(i);
    long long r = scm_page_row(i);
    long long c = scm_page_col(i);

    long long n = 1LL << l;

    scm_vector(a, (double)(r + 0.5) / n, (double)(c + 0.5) / n, v + 0);
}

//------------------------------------------------------------------------------

// Calculate grid of vertex positions and planet normals -----------------------

#include <vector>

static void scm_page_sample_entire_patch(std::vector<int> *patchIds, std::vector<double> *norms, long long i, long long pi, long long d, long long pd)
{
    if (d - pd == 8)
    {
        double *n = (double*)calloc(3, sizeof(double));
        scm_page_center(i, n);
        norms->push_back(n[0]);
        norms->push_back(n[1]);
        norms->push_back(n[2]);
        patchIds->push_back(pi);
    }
    else
    {
        for (int ci = 0; ci < 4; ci++)
        {
            scm_page_sample_entire_patch(patchIds, norms, scm_page_child(i, ci), pi, d + 1, pd);
        }
    }
}

static void scm_page_get_grid_digger(std::vector<int> *patchIds, std::vector<double> *norms, long long i, long long d, long long md)
{
    if (d == md)
    {
        scm_page_sample_entire_patch(patchIds, norms, i, i, md, md);
    }
    else
    {
        for (int ci = 0; ci < 4; ci++)
        {
            scm_page_get_grid_digger(patchIds, norms, scm_page_child(i, ci), d + 1, md);
        }
    }
}

page_grid scm_page_get_grid(long long i, int D)
{
    page_grid pg;

    // allocate holders
    std::vector<double> norms;
    std::vector<int> patchIds;

    // get info
    long long d = scm_page_level(i);
    scm_page_get_grid_digger(&patchIds, &norms, i, d, d + D);
    //for (int ci = 0; ci < 4; ci++) {
    //  scm_page_get_grid_digger(&patchIds, &norms, scm_page_child(i, ci), d + 1, d + D);
    //}

    // copy info
    pg.nv = norms.size() / 3;

    int j = 0;
    pg.norms = (double*)calloc(norms.size(), sizeof(double));
    for (auto iter = norms.cbegin(); iter != norms.cend(); iter++)
        pg.norms[j++] = *iter;

    j = 0;
    pg.patchIds = (int*)calloc(pg.nv, sizeof(int));
    for (auto iter = patchIds.cbegin(); iter != patchIds.cend(); iter++)
        pg.patchIds[j++] = *iter;

    // clear
    norms.clear();
    patchIds.clear();

    // return
    return pg;
}

double *scm_page_get_center(long long i)
{
    double *n = (double*)calloc(3, sizeof(double));
    scm_page_center(i, n);
    return n;
}
//------------------------------------------------------------------------------

