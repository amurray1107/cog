#include <demo_common.h>
#include <demo_glut.h>
#include <stdarg.h>

static int hud_width, hud_height, hud_cursor;

void hud_resize(int w, int h)
{
  hud_width = w;
  hud_height = h;
}

void hud_begin()
{
  hud_cursor = hud_height;
  
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0.0, hud_width, 0.0, hud_height, -1.0f, 1.0f);
  
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  
  glPushAttrib(GL_ENABLE_BIT);
  glDisable(GL_DEPTH_TEST);
}

void hud_puts(const char* s)
{
  hud_cursor -= 20;
  
  int twidth = glutBitmapLength(GLUT_BITMAP_9_BY_15, (const GLubyte*)s);
  
  glColor4f(0.0, 0.0, 0.0, 0.7);
  glRecti(10, hud_cursor-5, twidth + 28, hud_cursor+15);
  
  glColor4f(1.0, 1.0, 1.0, 1.0);
  glRasterPos3i(18, hud_cursor, 0);
  for(const char* p=s; *p; p++)
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *p);
}

void hud_println(const char* fmt, ...)
{
  char buffer[1024] = {0};
  va_list vlist;
  va_start(vlist, fmt);
  vsprintf(buffer, fmt, vlist);
  va_end(vlist);
  hud_puts(buffer);
}

void hud_end()
{
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
}

