#pragma once

#include <COG/cog.h>
#include <GLEW/glew.h>

typedef cog::basic_vector3<GLfloat> vec3;
typedef cog::basic_vector4<GLfloat> vec4;
typedef cog::basic_matrix3<GLfloat> mat3;
typedef cog::basic_matrix4<GLfloat> mat4;
typedef cog::basic_quaternion<GLfloat> quat;
typedef cog::basic_dualquat<GLfloat> dualquat;

void hud_resize(int w, int h);
void hud_begin();
void hud_puts(const char* s);
void hud_println(const char* fmt, ...);
void hud_end();

