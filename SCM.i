/* File : SCM.i */
//------------------------
%module SCM
//------------------------

/* References */
//------------------------
%{
  #include "scm-cache.hpp"
  #include "scm-fifo.hpp"
  #include "scm-file.hpp"
  #include "scm-frame.hpp"
  #include "scm-guard.hpp"
  #include "scm-image.hpp"
  #include "scm-index.hpp"
  #include "scm-item.hpp"
  #include "scm-label.hpp"
  #include "scm-log.hpp"
  #include "scm-path.hpp"
  #include "scm-queue.hpp"
  #include "scm-render.hpp"
  #include "scm-sample.hpp"
  #include "scm-scene.hpp"
  #include "scm-set.hpp"
  #include "scm-sphere.hpp"
  #include "scm-step.hpp"
  #include "scm-system.hpp"
  #include "scm-task.hpp"
  #include "scm-transfb.hpp"
  #include "util3d/cube.h"
  #include "util3d/demo.h"
  #include "util3d/glsl.hpp"
  #include "util3d/image.h"
  #include "util3d/math3d.h"
  #include "util3d/noise.h"
  #include "util3d/obj-sphere.h"
  #include "util3d/obj.h"
  #include "util3d/plane.h"
  #include "util3d/systime.h"
  #include "util3d/type.h"
  #include "util3d/read-tiff-results.h"
%}
//------------------------

/* Code to convert */
//------------------------
// type definitions
typedef unsigned int GLenum;
typedef unsigned int GLuint;
typedef int GLint;
typedef int GLsizei;
typedef unsigned char GLboolean;
typedef signed char GLbyte;
typedef short GLshort;
typedef unsigned char GLubyte;
typedef unsigned short GLushort;
typedef unsigned long GLulong;
typedef float GLfloat;
typedef double GLdouble;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

// input to render_sphere
%include "std_string.i"
%include "arrays_csharp.i"
%apply double INPUT[] {const double *P}
%apply double INPUT[] {const double *M}
%apply double INPUT[] {const double *v}
%apply float INPUT[] {float *p}
%apply float[] {GLfloat *}

// modules to convert
%include "scm-cache.hpp"
%include "scm-fifo.hpp"
%include "scm-file.hpp"
%include "scm-frame.hpp"
%include "scm-guard.hpp"
%include "scm-image.hpp"
%include "scm-index.hpp"
%include "scm-item.hpp"
%include "scm-label.hpp"
%include "scm-log.hpp"
%include "scm-path.hpp"
%include "scm-queue.hpp"
%include "scm-render.hpp"
%include "scm-sample.hpp"
%include "scm-scene.hpp"
%include "scm-set.hpp"
%include "scm-sphere.hpp"
%include "scm-step.hpp"
%include "scm-system.hpp"
%include "scm-task.hpp"
%include "scm-transfb.hpp"
%include "util3d/image.h"
%include "util3d/read-tiff-results.h"
//------------------------
