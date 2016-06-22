#include <FL/Fl_Roller.H>

#include "gui.hpp"

#define ROLLER_HEIGHT 25

int main(int argc, char** argv)
{
  Fl_Window * window = new Fl_Window(20, 40, opengl::iWidthWindow, opengl::iHeightWindow + ROLLER_HEIGHT, opengl::sWindowTitle.c_str());
  new GlGui(window, 0, 0, opengl::iWidthWindow, opengl::iHeightWindow, opengl::sWindowTitle.c_str());
  Fl_Roller * roller = new Fl_Roller(0, opengl::iHeightWindow, opengl::iWidthWindow, ROLLER_HEIGHT, NULL);
  roller->type(FL_HORIZONTAL);
  roller->minimum(0.0);
  roller->maximum(1.0);
  roller->step(0.001);
  roller->value(0.0);
  roller->callback(opengl::geom_callback, NULL);
  window->resizable(window);
  window->end();
  window->show(argc, argv);
  window->make_current();

  return Fl::run();
}
