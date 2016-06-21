#include "gui.hpp"

#include <iostream>

static void redraw_callback(void * arg) {
  Fl_Gl_Window * window = static_cast<Fl_Gl_Window *>(arg);
  window->redraw();
  Fl::repeat_timeout(0.016, redraw_callback, window);
}

GlGui::GlGui(int x, int y, int w, int h, const char * l) : Fl_Gl_Window(x, y, w, h, l) {
  initialized = false;
  Fl::add_timeout(0.016, redraw_callback, this);
  resizable(this);
}

void GlGui::draw() {
  if(!valid()) {
    if(!initialized) {
      opengl::initialize();
      initialized = true;
    }
    opengl::reshape(w(), h());
  }

  opengl::display();
}

int GlGui::handle(int event) {
  if(event == FL_KEYBOARD) {
    if(Fl::event_key() == 27) {
      opengl::terminate();
      return 1;
    }
  }
  redraw();

  return Fl_Gl_Window::handle(event);
}
