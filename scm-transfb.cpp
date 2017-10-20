#include <GL/glew.h>
#include <cstdlib>
#include <cstring>

#include "util3d/glsl.hpp"
#include "scm-transfb.hpp"

int scm_transfb::sizePerVertex = 0;
char** scm_transfb::vars = NULL;
int scm_transfb::numVars = 0;

scm_transfb::scm_transfb()
{
    data = NULL;
    vbo = 0;
    countVerts = 0;
    state = TFB_IDLE;
}

void scm_transfb::set_num_verts(unsigned long long numverts)
{
    this->numverts = numverts;
    if (vbo > 0)
    {
        glDeleteBuffers(1, &vbo);
    }

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, numverts * scm_transfb::sizePerVertex, nullptr, GL_STATIC_READ);
}

void scm_transfb::capture_frame()
{
    state = TFB_CAPTURE_NEXT_FRAME;
}

int scm_transfb::will_capture_frame()
{
    return (state == TFB_CAPTURE_NEXT_FRAME ? 1 : 0);
}

void scm_transfb::begin()
{
    if (state == TFB_CAPTURE_NEXT_FRAME)
    {
        glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, vbo);
        glBeginTransformFeedback(GL_TRIANGLES);
        state = TFB_CAPTURING;
    }
    else if (state == TFB_COUNT)
    {
        countVerts = 0;
    }
}

void scm_transfb::pause()
{
    if (state == TFB_CAPTURING)
    {
        glPauseTransformFeedback();
        state = TFB_PAUSED;
    }
}

void scm_transfb::resume()
{
    if (state == TFB_PAUSED)
    {
        glResumeTransformFeedback();
        state = TFB_CAPTURING;
    }
}

void scm_transfb::add_to_count(int amount)
{
    if (state == TFB_COUNT)
        countVerts += amount;
}

void scm_transfb::end()
{
    if (state == TFB_CAPTURING || state == TFB_PAUSED)
    {
        glEndTransformFeedback();
        glFlush();

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, vbo);

        destroy_data();
        data = (unsigned char*)calloc(numverts * scm_transfb::sizePerVertex, sizeof(unsigned char));
        glGetBufferSubData(GL_TRANSFORM_FEEDBACK_BUFFER, 0, numverts * scm_transfb::sizePerVertex, data);

        glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        state = TFB_IDLE;
    }
    else if (state == TFB_COUNT)
    {
        state = TFB_IDLE;
    }
}

void scm_transfb::count_verts()
{
    state = TFB_COUNT;
    countVerts = 0;
}

void scm_transfb::set_size_per_vertex(int size)
{
    scm_transfb::sizePerVertex = size;
}

void scm_transfb::set_num_vars(int numVars)
{
    scm_transfb::numVars = numVars;
    scm_transfb::vars = (char **)calloc(numVars, sizeof(char*));
}

void scm_transfb::set_var(int len, char *var)
{
    static int i = 0;
    scm_transfb::vars[i] = (char*)calloc(len, sizeof(char));
    strcpy(scm_transfb::vars[i], (const char *)var);
    i++;
}

int scm_transfb::num_data()
{
    return numverts * scm_transfb::sizePerVertex;
}

unsigned char* scm_transfb::get_data()
{
    return data;
}

unsigned char scm_transfb::get_data_at(int index)
{
    return data[index];
}

void scm_transfb::destroy_data()
{
    if (data != NULL)
    {
        free(data);
        data = NULL;
    }
}
