#include <demo_common.h>
#include <demo_glut.h>

static mat4 viewMat;
static vec3 viewPos;
static mat3 viewRot;

static void _OnDisplayGLUT(void)
{
  // Render Now!
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  
  // Set Model-View Matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  // Apply View Matrix
  glMultMatrixf((float*)&viewMat);
  
  // Draw!
  glLineWidth(4.0f);
  glColor3f(1.0f, 0.0f, 0.0f);
  glutWireCube(1.5f);
  glColor3f(1.0f, 1.0f, 1.0f);
  glutSolidCube(1.5f);
  glLineWidth(1.0f);
  glutWireSphere(10.0f, 16, 16);
  
  
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
  viewRot = cog::ConstMatrix3<float>::identity();
  viewPos = vec3(0.0f, 0.0f, 4.0f);
  viewMat = mat4(viewRot, -viewPos);
}

static void _OnSpecialDownGLUT(int key, int x, int y)
{
  using namespace cog;
  
  const vec3 d = -normalize(transpose(viewRot).getColumn2());
  
  switch(key){
    case GLUT_KEY_UP:
      viewPos = viewPos + d * 0.1f;
      break;
    case GLUT_KEY_DOWN:
      viewPos = viewPos - d * 0.1f;
      break;
    case GLUT_KEY_LEFT:
      viewRot = viewRot * make_rotate(-0.1f, vec3(0.0f, 1.0f, 0.0f));
      break;
    case GLUT_KEY_RIGHT:
      viewRot = viewRot * make_rotate(+0.1f, vec3(0.0f, 1.0f, 0.0f));
      break;
  }
  viewMat = mat4(viewRot, viewRot * -viewPos);
  
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
  
  // Install Special Event
  glutSpecialFunc(_OnSpecialDownGLUT);
  
  // Enter Main Loop (NEVER RETURN)
  glutMainLoop();
  
  return 0;
}

