#include <demo_common.h>
#include <demo_glut.h>
#include <stdio.h>

static mat3 rotateMat;
static vec3 translVec;

static void _OnDisplayGLUT(void)
{
  // Render Now!
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  
  // Set Model-View Matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  // 
  mat4 tmp = mat4(rotateMat, translVec);
  glMultMatrixf((float*)&tmp);
  
  // Set Wire-line mode
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  
  // Draw!
  glutSolidCube(1.5f);
  
  // Swap Display Buffer
  glutSwapBuffers();
}

static void _OnReshapeGLUT(int width, int height)
{
  glViewport(0, 0, width, height);
  
  // Prevent From Zero-Divisor Exception
  if(height==0)
    return;
  
  // Set Parameters
  const float near = 2.0f;
  const float far = 50.0f;
  const float fovy = 0.785f;
  const float f = cog::tan(fovy*0.5f);
  const float aspect = (float)width / (float)height;
  const float t = near * f;
  const float r = aspect * t;
  mat4 proj = cog::make_perspective(-r, r, -t, t, near, far);
  
  // Set Projection Matrix
  glMatrixMode(GL_PROJECTION);
  glLoadMatrixf((float*)&proj);
  
  // 
  rotateMat = cog::const_matrix3<float>::identity();
  translVec = vec3(0.0f, 0.0f, -4.0f);
}

static void _OnKeyDownGLUT(unsigned char key, int x, int y)
{
  switch(key){
    case 'w':
      translVec = translVec + vec3(0.0f, 0.1f, 0.0f);
      break;
    case 's':
      translVec = translVec - vec3(0.0f, 0.1f, 0.0f);
      break;
    case 'a':
      translVec = translVec - vec3(0.1f, 0.0f, 0.0f);
      break;
    case 'd':
      translVec = translVec + vec3(0.1f, 0.0f, 0.0f);
      break;
  }
  glutPostRedisplay();
}

static void _OnSpecialDownGLUT(int key, int x, int y)
{
  using namespace cog;
  
  switch(key){
    case GLUT_KEY_UP:
      break;
    case GLUT_KEY_DOWN:
      break;
    case GLUT_KEY_LEFT:
      rotateMat = rotateMat * make_rotate(-0.1f, vec3(0.0f, 1.0f, 0.0f));
      break;
    case GLUT_KEY_RIGHT:
      rotateMat = rotateMat * make_rotate(+0.1f, vec3(0.0f, 1.0f, 0.0f));
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
  
  // Install Special Event
  glutSpecialFunc(_OnSpecialDownGLUT);
  
  // Enter Main Loop (NEVER RETURN)
  glutMainLoop();
  
  return 0;
}

