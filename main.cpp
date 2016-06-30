#include <FL/Fl_Roller.H>

#include "gui.hpp"

#define ROLLER_HEIGHT 25

int main(int argc, char** argv)
{
  Fl_Window * window = new Fl_Window(20, 40, opengl::iWidthWindow, opengl::iHeightWindow + (ROLLER_HEIGHT * 3), opengl::sWindowTitle.c_str());
  new GlGui(window, 0, 0, opengl::iWidthWindow, opengl::iHeightWindow, opengl::sWindowTitle.c_str());
  Fl_Roller * roller_geom = new Fl_Roller(0, opengl::iHeightWindow, opengl::iWidthWindow, ROLLER_HEIGHT, NULL);
  roller_geom->type(FL_HORIZONTAL);
  roller_geom->minimum(0.0);
  roller_geom->maximum(1.0);
  roller_geom->step(0.001);
  roller_geom->value(0.0);
  roller_geom->callback(opengl::geom_callback, NULL);
  Fl_Roller * roller_tess_1 = new Fl_Roller(0, opengl::iHeightWindow + ROLLER_HEIGHT, opengl::iWidthWindow, ROLLER_HEIGHT, NULL);
  roller_tess_1->type(FL_HORIZONTAL);
  roller_tess_1->minimum(1.0);
  roller_tess_1->maximum(20.0);
  roller_tess_1->step(0.010);
  roller_tess_1->value(1.0);
  roller_tess_1->callback(opengl::tess_callback_inner, NULL);
  Fl_Roller * roller_tess_2 = new Fl_Roller(0, opengl::iHeightWindow + (ROLLER_HEIGHT * 2), opengl::iWidthWindow, ROLLER_HEIGHT, NULL);
  roller_tess_2->type(FL_HORIZONTAL);
  roller_tess_2->minimum(1.0);
  roller_tess_2->maximum(20.0);
  roller_tess_2->step(0.010);
  roller_tess_2->value(1.0);
  roller_tess_2->callback(opengl::tess_callback_outer, NULL);
  window->resizable(window);
  window->end();
  window->show(argc, argv);
  window->make_current();

  return Fl::run();
}
