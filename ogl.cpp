#include <iostream>
#include <GL/glew.h>	//this line have to be before freeglut
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <FL/Fl_Valuator.H>

#include "ogl.hpp"
#include "GLSLProgram.hpp"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

namespace opengl
{
  //globals
  const std::string sWindowTitle = "OGL Cube";		//name of the window
  unsigned int iWidthWindow = 800, iHeightWindow = 600;	//width & height of the viewport
  
  //constants
  const float NCP = 0.1f;
  const float FCP = 150.0f;
  const float ANGLE = 75.f;
  float geom_param = 0.0;
  float tess_inner = 1.0;
  float tess_outer = 1.0;
  bool  tess = false;
  bool  light = true;
  bool  lines = true;

  //variables
  glm::mat4x4 mProjMatrix, mModelMatrix, mViewMatrix;
  CGLSLProgram m_program;
  GLuint m_iIndexVAO;
  float m_fAngle;	//this variable is just for spinning the cube

  //cube definition
  const int iNVertices = 36;
  glm::vec4 vec_points[iNVertices];
  glm::vec4 vec_colors[iNVertices];
  glm::vec4 vec_positions[8] = {
    glm::vec4( -0.5f, -0.5f,  0.5f, 1.0f ),
    glm::vec4( -0.5f,  0.5f,  0.5f, 1.0f ),
    glm::vec4(  0.5f,  0.5f,  0.5f, 1.0f ),
    glm::vec4(  0.5f, -0.5f,  0.5f, 1.0f ),
    glm::vec4( -0.5f, -0.5f, -0.5f, 1.0f ),
    glm::vec4( -0.5f,  0.5f, -0.5f, 1.0f ),
    glm::vec4(  0.5f,  0.5f, -0.5f, 1.0f ),
    glm::vec4(  0.5f, -0.5f, -0.5f, 1.0f )};
  glm::vec4 colors[8] = {
    glm::vec4( 0.f, 0.f, 0.f, 1.f ),  // black
    glm::vec4( 1.f, 0.f, 0.f, 1.f ),  // red
    glm::vec4( 1.f, 1.f, 0.f, 1.f ),  // yellow
    glm::vec4( 0.f, 1.f, 0.f, 1.f ),  // green
    glm::vec4( 0.f, 0.f, 1.f, 1.f ),  // blue
    glm::vec4( 1.f, 0.f, 1.f, 1.f ),  // magenta
    glm::vec4( 0.5f, 0.5f, 0.5f, 0.5f ),  // grey
    glm::vec4( 0.f, 1.f, 1.f, 1.f )   // cyan
  };
  
  void quad(int& iIndex, int a, int b, int c, int d )
  {
    vec_colors[iIndex] = colors[a]; vec_points[iIndex] = vec_positions[a]; iIndex++;
    vec_colors[iIndex] = colors[b]; vec_points[iIndex] = vec_positions[b]; iIndex++;
    vec_colors[iIndex] = colors[c]; vec_points[iIndex] = vec_positions[c]; iIndex++;
    vec_colors[iIndex] = colors[a]; vec_points[iIndex] = vec_positions[a]; iIndex++;
    vec_colors[iIndex] = colors[c]; vec_points[iIndex] = vec_positions[c]; iIndex++;
    vec_colors[iIndex] = colors[d]; vec_points[iIndex] = vec_positions[d]; iIndex++;
  }

  void colorcube()
  {
    int iIndex = 0;	
    quad(iIndex, 1, 0, 3, 2 );
    quad(iIndex, 2, 3, 7, 6 );
    quad(iIndex, 3, 0, 4, 7 );
    quad(iIndex, 6, 5, 1, 2 );
    quad(iIndex, 4, 5, 6, 7 );
    quad(iIndex, 5, 4, 0, 1 );
  }

  void initialize()
  {
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
		
    mModelMatrix = glm::mat4();
    mViewMatrix = glm::mat4();
    glewInit();	
    colorcube();

    m_program.loadShader("shaders/basic.vert", CGLSLProgram::VERTEX);
    m_program.loadShader("shaders/basic.tc", CGLSLProgram::TESSELLATION_CONTROL);
    m_program.loadShader("shaders/basic.te", CGLSLProgram::TESSELLATION_EVALUATION);
    m_program.loadShader("shaders/basic.geom", CGLSLProgram::GEOMETRY);
    m_program.loadShader("shaders/basic.frag", CGLSLProgram::FRAGMENT);
    m_program.create_link();
    m_program.enable();
    m_program.addAttribute("vVertex");
    m_program.addAttribute("vColor");
    m_program.addUniform("mView");
    m_program.addUniform("mProjection");
    m_program.addUniform("mModel");
    m_program.addUniform("fGeomParam");
    m_program.addUniform("TessLevelInner");
    m_program.addUniform("TessLevelOuter");
    m_program.addUniform("uNorm");
    m_program.addUniform("iLightsOn");
    m_program.addUniform("uDrawWireFrame");
    m_program.disable();

    //VAO
    glGenVertexArrays(1, &m_iIndexVAO);
    glBindVertexArray(m_iIndexVAO);
    //VBO - create and initialize a buffer object
    GLuint iIdBuffer;
    glGenBuffers(1, &iIdBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, iIdBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec_points) + sizeof(vec_colors), NULL, GL_STATIC_DRAW );
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vec_points), vec_points);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vec_points), sizeof(vec_colors), vec_colors);

    glEnableVertexAttribArray(m_program.getLocation("vVertex"));
    glVertexAttribPointer(m_program.getLocation("vVertex"), 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0)); //Vertex
    glEnableVertexAttribArray(m_program.getLocation("vColor"));
    glVertexAttribPointer(m_program.getLocation("vColor"), 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vec_points))); //Colors
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    m_fAngle = 0.f;
  }

  void display()
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.15f, 0.15f, 0.15f, 1.f);	//a grey color

    mViewMatrix = glm::translate(glm::mat4(), glm::vec3(0,0,-1.5));	//a little bit 
    mModelMatrix = glm::rotate(glm::mat4(), glm::radians(m_fAngle), glm::vec3(0,1,0));

    m_program.enable();
    glUniformMatrix4fv(m_program.getLocation("mView"), 1, GL_FALSE, glm::value_ptr(mViewMatrix));
    glUniformMatrix4fv(m_program.getLocation("mModel"), 1, GL_FALSE, glm::value_ptr(mModelMatrix));
    glUniformMatrix4fv(m_program.getLocation("mProjection"), 1, GL_FALSE, glm::value_ptr(mProjMatrix));
    glUniform1f(m_program.getLocation("fGeomParam"), geom_param);
    glUniform1f(m_program.getLocation("TessLevelInner"), tess_inner);
    glUniform1f(m_program.getLocation("TessLevelOuter"), tess_outer);
    glUniform1i(m_program.getLocation("uNorm"), tess);
    glUniform1i(m_program.getLocation("iLightsOn"), light);
    glUniform1i(m_program.getLocation("uDrawWireFrame"), lines);
    glBindVertexArray(m_iIndexVAO);
    glPatchParameteri(GL_PATCH_VERTICES, 3);
    glDrawArrays(GL_PATCHES, 0, iNVertices);
    glBindVertexArray(0);
    m_program.disable();

    m_fAngle += 0.5f;
    if (m_fAngle > 360.0f)
      m_fAngle -= 360.0f;	//for the spinning
  }

  void reshape(int w, int h)
  {
    if(h == 0)h = 1;
    float fRatio = float(w) / float(h);
    opengl::iWidthWindow = w;
    opengl::iHeightWindow = h;
    glViewport(0, 0, w, h);
    float k = 90;
    opengl::mProjMatrix = glm::perspective(glm::radians(k), fRatio, opengl::NCP, opengl::FCP);
  }

  void geom_callback(Fl_Widget * w, void * data) {
    geom_param = ((Fl_Valuator *)w)->value();
  }

  void tess_callback_inner(Fl_Widget * w, void * data) {
    tess_inner = ((Fl_Valuator *)w)->value();
  }

  void tess_callback_outer(Fl_Widget * w, void * data) {
    tess_outer = ((Fl_Valuator *)w)->value(); 
  }

  void toggle_tess() {
    tess = !tess;
  }

  void toggle_light() {
    light = !light;
  }

  void toggle_lines() {
    lines = !lines;
  }
}
