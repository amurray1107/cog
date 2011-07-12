#include <demo_common.h>
#include <demo_glut.h>
#include <stdio.h>

static const int mesh_vsplits = 8;
static const int mesh_hsplits = 32;
static const float mesh_vsize = 1.0f;
static const float mesh_hsize = 4.0f;

static const int mesh_vertexnum = (mesh_hsplits+1)*(mesh_vsplits+1);
static const int mesh_priminum = mesh_vsplits*mesh_hsplits;

static GLfloat mesh_vertices[mesh_vertexnum][3];
static GLushort mesh_indices[mesh_priminum][4];
static GLenum mesh_mode = GL_QUADS;

static const int mesh_nedges = (mesh_hsplits+mesh_vsplits)*2;
static GLushort mesh_edindcs[mesh_nedges];

static GLubyte mesh_blendindexs[mesh_vertexnum][2];
static GLubyte mesh_blendweights[mesh_vertexnum][2];
static GLfloat mesh_blendedvertices[mesh_vertexnum][3];

static quat mesh_blend_rotation[2];
static vec3 mesh_blend_displacement[2];

static int mesh_blend_mode = 0;
static quat viewRotateQua = quat(vec3(0.0f), 1.0f);

static void _generate_mesh()
{
  for(int i=0; i<=mesh_hsplits; i++){
    float x = mesh_hsize * float(i)/float(mesh_hsplits) - mesh_hsize*0.5f;
    for(int j=0; j<=mesh_vsplits; j++){
      float y = mesh_vsize * float(j)/float(mesh_vsplits) - mesh_vsize*0.5f;
      int index = j + i * (mesh_vsplits+1);
      
      mesh_vertices[index][0] = x;
      mesh_vertices[index][1] = y;
      mesh_vertices[index][2] = 0.0f;
      
      mesh_blendindexs[index][0] = 0;
      mesh_blendindexs[index][1] = 1;
      
      float w = float(i) / float(mesh_hsplits);
      mesh_blendweights[index][0] = GLubyte((1.0f-w) * 255.0f);
      mesh_blendweights[index][1] = GLubyte((w) * 255.0f);
    }
  }
  
  {
    int k=0;
    for(int i=0; i<mesh_hsplits; i++)
      mesh_edindcs[k++] = 0 + i * (mesh_vsplits+1);
    for(int j=0; j<mesh_vsplits; j++)
      mesh_edindcs[k++] = j + mesh_hsplits * (mesh_vsplits+1);
    for(int i=mesh_hsplits; i>0; i--)
      mesh_edindcs[k++] = mesh_vsplits + i * (mesh_vsplits+1);
    for(int j=mesh_vsplits; j>0; j--)
      mesh_edindcs[k++] = j + 0 * (mesh_vsplits+1);
  }
  
  for(int i=0; i<mesh_hsplits; i++){
    for(int j=0; j<mesh_vsplits; j++){
      int vtx_leftbottom = j + i * (mesh_vsplits+1);
      int index = j + i * mesh_vsplits;
      
      mesh_indices[index][0] = vtx_leftbottom;
      mesh_indices[index][1] = vtx_leftbottom + mesh_vsplits + 1;
      mesh_indices[index][2] = vtx_leftbottom + mesh_vsplits + 2;
      mesh_indices[index][3] = vtx_leftbottom + 1;
    }
  }
}

static void _blend_mesh_mat()
{
  for(int i=0; i<mesh_vertexnum; i++){
    const float *vtx = mesh_vertices[i];
    const GLubyte* bidx = mesh_blendindexs[i];
    const GLubyte* bwei = mesh_blendweights[i];
    float *outvtx = mesh_blendedvertices[i];
    
    const vec3 old = vec3(vtx[0], vtx[1], vtx[2]);
    
    mat3 rot(0.0f);
    vec3 dis(0.0f);
    float sum = 0.0f;
    
    for(int i=0; i<2; i++){
      float w = float(bwei[i]) / 255.0f;
      rot = rot + make_rotate(mesh_blend_rotation[bidx[i]]) * w;
      dis = dis + mesh_blend_displacement[bidx[i]] * w;
      sum += w;
    }
    sum = cog::recip(sum);
    rot = rot * sum;
    dis = dis * sum;
    
    vec3 v = rot * old + dis;
    
    outvtx[0] = v.getX();
    outvtx[1] = v.getY();
    outvtx[2] = v.getZ();
  }
}

static void _blend_mesh_quat()
{
  for(int i=0; i<mesh_vertexnum; i++){
    const float *vtx = mesh_vertices[i];
    const GLubyte* bidx = mesh_blendindexs[i];
    const GLubyte* bwei = mesh_blendweights[i];
    float *outvtx = mesh_blendedvertices[i];
    
    const vec3 old = vec3(vtx[0], vtx[1], vtx[2]);
    
    quat rot(vec3(0.0f), 0.0f);
    vec3 dis(0.0f);
    float sum = 0.0f;
    
    for(int i=0; i<2; i++){
      float w = float(bwei[i]) / 255.0f;
      rot = rot + mesh_blend_rotation[bidx[i]] * w;
      dis = dis + mesh_blend_displacement[bidx[i]] * w;
      sum += w;
    }
    sum = cog::recip(sum);
    rot = rot * sum;
    dis = dis * sum;
    rot = normalize(rot);
    
    vec3 v = rot * old + dis;
    
    outvtx[0] = v.getX();
    outvtx[1] = v.getY();
    outvtx[2] = v.getZ();
  }
}

static void _blend_mesh_dualquat()
{
  for(int i=0; i<mesh_vertexnum; i++){
    const float *vtx = mesh_vertices[i];
    const GLubyte* bidx = mesh_blendindexs[i];
    const GLubyte* bwei = mesh_blendweights[i];
    float *outvtx = mesh_blendedvertices[i];
    
    const vec3 old = vec3(vtx[0], vtx[1], vtx[2]);
    
    dualquat tfm(quat(vec3(0.0f), 0.0f), quat(vec3(0.0f), 0.0f));
    float sum = 0.0f;
    
    for(int i=0; i<2; i++){
      float w = float(bwei[i]) / 255.0f;
      const quat& rq = mesh_blend_rotation[bidx[i]];
      const vec3& dv = mesh_blend_displacement[bidx[i]];
      tfm = tfm + dualquat(rq, dv) * w;
      sum += w;
    }
    tfm = normalize(tfm * cog::recip(sum));
    
    vec3 vt = tfm.getDisplacement();
    vec3 vr = tfm.getRotation() * old;
    vr = vr + vt;
    
    outvtx[0] = vr.getX();
    outvtx[1] = vr.getY();
    outvtx[2] = vr.getZ();
  }
}

static void _OnDisplayGLUT(void)
{
  // Render Now!
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  
  // Set Model-View Matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  // 
  glTranslatef(0.0f, 0.0f, -4.0f);
  mat3 rotmat = make_rotate(viewRotateQua);
  mat4 tmp = mat4(rotmat, vec3(0.0f));
  glMultMatrixf((float*)&tmp);
  
  glEnable(GL_DEPTH_TEST);
  
  // Draw!
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, sizeof(GLfloat)*3, mesh_blendedvertices);
  
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glColor3f(0.0f, 0.0f, 1.0f);
  glLineWidth(5.0f);
  glDrawElements(GL_LINE_LOOP, mesh_nedges, GL_UNSIGNED_SHORT, mesh_edindcs);
  
  glColor3f(1.0f, 1.0f, 1.0f);
  glLineWidth(2.0f);
  glDrawElements(mesh_mode, mesh_priminum*4, GL_UNSIGNED_SHORT, mesh_indices);
  
  glColor3f(0.5f, 0.0f, 0.0f);
  glLineWidth(1.0f);
  glVertexPointer(3, GL_FLOAT, sizeof(GLfloat)*3, mesh_vertices);
  glDrawElements(mesh_mode, mesh_priminum*4, GL_UNSIGNED_SHORT, mesh_indices);
  
  // Draw Text
  hud_begin();
  switch(mesh_blend_mode){
    case 0:
      hud_puts("[ Matrix Blending ]");
      break;
    case 1:
      hud_puts("[ Quaternion Blending ]");
      break;
    case 2:
      hud_puts("[ Dual Quaternion Blending ]");
      break;
  }
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
}

static void _OnKeyDownGLUT(unsigned char key, int x, int y)
{
  switch(key){
    case ' ':
      mesh_blend_mode = (mesh_blend_mode+1)%3;
      switch(mesh_blend_mode){
        case 0:
          _blend_mesh_mat();
          break;
        case 1:
          _blend_mesh_quat();
          break;
        case 2:
          _blend_mesh_dualquat();
          break;
      }
      break;
    case 'z':
      viewRotateQua = quat(vec3(0.0f), 1.0f);
      break;
  }
  glutPostRedisplay();
}

static void _OnSpecialDownGLUT(int key, int x, int y)
{
  const float PI = 3.141592653589793f;
  const float f = PI/30.0f;
  switch(key){
    case GLUT_KEY_UP:
      viewRotateQua = make_quat(f, vec3(-1.0f, 0.0f, 0.0f)) * viewRotateQua;
      break;
    case GLUT_KEY_DOWN:
      viewRotateQua = make_quat(f, vec3(1.0f, 0.0f, 0.0f)) * viewRotateQua;
      break;
    case GLUT_KEY_LEFT:
      viewRotateQua = make_quat(f, vec3(0.0f, -1.0f, 0.0f)) * viewRotateQua;
      break;
    case GLUT_KEY_RIGHT:
      viewRotateQua = make_quat(f, vec3(0.0f, 1.0f, 0.0f)) * viewRotateQua;
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
  
  // 
  _generate_mesh();
  
  //
  mesh_blend_displacement[0] = vec3(0.0f);
  mesh_blend_displacement[1] = vec3(0.0f, 0.0f, 1.5f);
  mesh_blend_rotation[0] = quat(vec3(0.0f), 1.0f);
  //mesh_blend_rotation[1] = cog::make_quat(-3.14f, vec3(1.0f, 0.0f, 0.0f));
  mesh_blend_rotation[1] = cog::make_quat(3.14f, vec3(1.0f, 0.0f, 0.0f));
  
  //
  _blend_mesh_mat();
  
  // Enter Main Loop (NEVER RETURN)
  glutMainLoop();
  
  return 0;
}

