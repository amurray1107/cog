#include <demo_common.h>
#include <demo_glut.h>

static const float near = 2.0f;
static const float far = 50.0f;
static const float fovy = 0.785f;
static float aspectRatio = 0.0f;
static bool isOrtho = false;

static mat4 build_proj(float fovy, float ar, float zn, float zf, bool ort)
{
  float f = cog::tan(fovy*0.5f);
  float t = zn * f;
  float r = ar * t;
  
  if(ort)
    return cog::make_orthographic(-r, r, -t, t, zn, zf);
  
  return cog::make_perspective(-r, r, -t, t, zn, zf);;
}

static void _OnDisplayGLUT(void)
{
  // Render Now!
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  
  // Set Model-View Matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  // Translate!
  glTranslatef(0.0f, 0.0f, -3.0f);
  glRotatef(15.0f, 1.0f, 0.0f, 0.0f);
  glRotatef(30.0f, 0.0f, 1.0f, 0.0f);
  
  // Set Wire-line mode
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glLineWidth(3.0f);
  
  // Draw!
  glutSolidCube(1.0f);
  
  // Draw Text
  hud_begin();
  if(isOrtho)
    hud_puts("[ Orthographic Projection ]");
  else
    hud_puts("[ Perspective Projection ]");
  hud_end();
  
  // Swap Display Buffer
  glutSwapBuffers();
}

static void _OnReshapeGLUT(int width, int height)
{
  glViewport(0, 0, width, height);
  
  // Prevent From Zero-Divisor Exception
  if(height==0)
    return;
  
  // Update HUD
  hud_resize(width, height);
  
  // Set Parameters
  const float aspect = (float)width / (float)height;
  aspectRatio = aspect;
  
  mat4 proj = build_proj(fovy, aspect, near, far, isOrtho);
  
  // Set Projection Matrix
  glMatrixMode(GL_PROJECTION);
  glLoadMatrixf((float*)&proj);
}

static void _OnKeyDownGLUT(unsigned char key, int x, int y)
{
  switch(key){
    case ' ':
      isOrtho = !isOrtho;
    {
      mat4 proj = build_proj(fovy, aspectRatio, near, far, isOrtho);
      glMatrixMode(GL_PROJECTION);
      glLoadMatrixf((float*)&proj);
    }
      break;
  }
  glutPostRedisplay();
}

int main(int argc, char* argv[])
{
  glutInit(&argc, argv);
  
  glutInitWindowSize(1280, 720);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutCreateWindow(argv[0]);
  
  { // Initialize GLEW
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if(err!=GLEW_OK){
      fprintf(stderr, "main: GLEW initialization failed.\n");
      fprintf(stderr, "  Error: %s\n", glewGetErrorString(err));
      return 1;
    }
    printf("Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    printf("Status: OpenGL Version: %s\n", (char*)glGetString(GL_VERSION));
    printf("Status: OpenGL Vendor: %s\n", (char*)glGetString(GL_VENDOR));
    printf("Status: OpenGL Renderer: %s\n", (char*)glGetString(GL_RENDERER));
  }
  
  // Install Repaint Event
  glutDisplayFunc(_OnDisplayGLUT);
  
  // Install Resizing Event
  glutReshapeFunc(_OnReshapeGLUT);
  
  // Install Keyboard Event
  glutKeyboardFunc(_OnKeyDownGLUT);
  
  // Enter Main Loop (NEVER RETURN)
  glutMainLoop();
  
  return 0;
}

