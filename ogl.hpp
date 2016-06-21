#pragma once

#ifndef OGL_HPP
#define OGL_HPP

#include <string>

namespace opengl
{
//globals
  extern const std::string sWindowTitle; //name of the window
  extern unsigned int iWidthWindow;
  extern unsigned int iHeightWindow;     //width & height of the viewport
  
  ///
  /// A function to create two triangles based on the quad definition
  ///
  /// @iIndex an integer to access into the vectors (color and points)
  /// @a definition of the 1st index into the </code>vec_position</code> variable
  /// @b definition of the 2nd index into the </code>vec_position</code> variable
  /// @c definition of the 3rd index into the </code>vec_position</code> variable
  /// @d definition of the 4th index into the </code>vec_position</code> variable
  void quad(int& iIndex, int a, int b, int c, int d );

  ///
  /// Simple function to construct <code>iNVertices</code> vertexes over the definition of 6 faces of a cube
  ///
  void colorcube();

  ///
  /// Function to initialize OGL variables + shader's loading + VAO + VBO
  ///
  void initialize();

  ///
  /// The display OGL function
  ///
  void display();

  ///
  /// A simple calling to the display function
  ///
  void idle();

  ///
  /// The classical resized function in GLUT, including the perspective matrox construction
  ///
  void reshape(int w, int h);

  ///
  /// This function can be used to delete or close instances previously created
  ///
  void terminate();

  ///
  ///The classical keyboard manager GLUT function, ESC key to exit
  ///
  void keyboard(unsigned char key, int x, int y);
}

#endif
