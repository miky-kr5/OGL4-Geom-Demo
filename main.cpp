#include "gui.hpp"

int main(int argc, char** argv)
{
  Fl_Gl_Window * window = new GlGui(20, 40, opengl::iWidthWindow, opengl::iHeightWindow, opengl::sWindowTitle.c_str());
  window->end();
  window->show(argc, argv);
  window->make_current();
  return Fl::run();
}
