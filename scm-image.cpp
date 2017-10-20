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

#include "util3d/glsl.hpp"

#include "scm-system.hpp"
#include "scm-cache.hpp"
#include "scm-image.hpp"
#include "scm-index.hpp"
#include "scm-log.hpp"

//------------------------------------------------------------------------------

scm_image::scm_image(scm_system *sys) :
    sys(sys),
    channel(-1),
    height(false),
    k0(0),
    k1(1),
    uS(-1),
    ur(-1),
    uk0(-1),
    uk1(-1),
    index(-1)
{
}

scm_image::~scm_image()
{
    set_scm("");
}

//------------------------------------------------------------------------------

void scm_image::set_scm(const std::string& s)
{
    if (!scm.empty())
        index = sys->release_scm(scm);

    scm = s;

    if (!scm.empty())
        index = sys->acquire_scm(scm);

    cache = (index < 0) ? 0 : sys->get_cache(index);
}

void scm_image::set_name(const std::string& s)
{
    name = s;
    height = (name == "height");
}

//------------------------------------------------------------------------------

void scm_image::init_uniforms(GLuint program)
{
    scm_log("scm_image init_uniforms %s %s %d", scm.c_str(), name.c_str(), program);

    if (program && !name.empty())
    {
        uS = glsl_uniform(program, "%s_sampler", name.c_str());
        scm_log("set sampler '%s_sampler' found at %d", name.c_str(), uS);
        ur = glsl_uniform(program, "%s.r", name.c_str());
        uk0 = glsl_uniform(program, "%s.k0", name.c_str());
        uk1 = glsl_uniform(program, "%s.k1", name.c_str());

        for (int d = 0; d < 16; d++)
        {
            ua[d] = glsl_uniform(program, "%s.a[%d]", name.c_str(), d);
            ub[d] = glsl_uniform(program, "%s.b[%d]", name.c_str(), d);
        }
    }
}

void scm_image::bind(GLuint unit, GLuint program) const
{
    glUniform1i(uS, unit);
    glUniform1f(uk0, k0);
    glUniform1f(uk1, k1);

    if (cache)
    {
        const GLfloat r = GLfloat(cache->get_page_size())
            / GLfloat(cache->get_page_size() + 2)
            / GLfloat(cache->get_grid_size());

        glUniform2f(ur, r, r);
        glActiveTexture(GL_TEXTURE0 + unit);
        glBindTexture(GL_TEXTURE_2D, cache->get_texture());
    }
}

void scm_image::unbind(GLuint unit) const
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, 0);
}

//------------------------------------------------------------------------------

void scm_image::bind_page(GLuint program, int d, int t, long long i) const
{
    if (cache)
    {
        // Get the page index and the time of its loading.

        int u, l = cache->get_page(index, i, t, u);

        // Compute the page age.

        double a = l ? 1.0 : 0.0;

        if (l && sys->get_synchronous())
        {
            a = (t - u) / 60.0;
            a = std::min(a, 1.0);
            a = std::max(a, 0.0);
        }

        // Compute texture coordinate offsets and set the uniforms.

        const int s = cache->get_grid_size();
        const int n = cache->get_page_size();

        glUniform1f(ua[d], GLfloat(a));
        glUniform2f(ub[d], GLfloat((l % s) * (n + 2) + 1) / (s * (n + 2)),
            GLfloat((l / s) * (n + 2) + 1) / (s * (n + 2)));
    }
}

void scm_image::unbind_page(GLuint program, int d) const
{
    glUniform1f(ua[d], 0.f);
    glUniform2f(ub[d], 0.f, 0.f);
}

void scm_image::touch_page(int t, long long i) const
{
    if (cache)
    {
        int ignored;
        cache->get_page(index, i, t, ignored);
    }
}

//------------------------------------------------------------------------------

float scm_image::get_page_sample(const double *v) const
{
    if (index < 0)
        return k1;
    else
    {
        try
        {
            return sys->get_page_sample(index, v) * (k1 - k0) + k0;
        }
        catch (...)
        {
            return 9001.0;
        }
    }
}

float* scm_image::get_page_sample4v(const double *v) const
{
    float* result = (float*)calloc(4, sizeof(float));
    if (index < 0)
    {
        for (int i = 0; i < 4; i++)
            result[i] = k1;
    }
    else
    {
        try
        {
            float* page_sample = sys->get_page_sample4v(index, v);
            for (int i = 0; i < 4; i++)
                result[i] = page_sample[i] * (k1 - k0) + k0;
        }
        catch (...)
        {
            for (int i = 0; i < 4; i++)
                result[i] = 9001.f;
        }
    }
    return result;
}

void scm_image::get_page_bounds(long long i, float& r0, float& r1) const
{
    if (index < 0)
    {
        r0 = k0;
        r1 = k1;
    }
    else
    {
        sys->get_page_bounds(index, i, r0, r1);

        r0 = k0 + (k1 - k0) * r0;
        r1 = k0 + (k1 - k0) * r1;
    }
}

bool scm_image::get_page_status(long long i) const
{
    if (index < 0)
        return false;
    else
        return sys->get_page_status(index, i);
}

//------------------------------------------------------------------------------
