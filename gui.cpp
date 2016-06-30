#include "gui.hpp"

#include <iostream>

static void redraw_callback(void * arg) {
  GlGui * window = static_cast<GlGui *>(arg);
  Fl::focus(window);
  window->redraw();
}

GlGui::GlGui(Fl_Window * parent, int x, int y, int w, int h, const char * l) : Fl_Gl_Window(x, y, w, h, l) {
  this->parent = parent;
  title += l;
  initialized = false;
  Fl::add_idle(redraw_callback, this);
  resizable(this);
}

void GlGui::draw() {
  if(!valid()) {
    if(!initialized) {
      opengl::initialize();

      if(parent != NULL) {
	title += " :: OpenGL Version ";
	title += (char*)glGetString(GL_VERSION);
	title += " :: OpenGL Vendor ";
	title += (char*)glGetString(GL_VENDOR);
	parent->label(title.c_str());
      }

      initialized = true;
    }
    opengl::reshape(w(), h());
  }

  opengl::display();
}

int GlGui::handle(int event) {
  switch(event) {
  case FL_FOCUS:
    return 1;
  case FL_KEYBOARD:
    switch(Fl::event_key()) {
    case ' ':
      opengl::toggle_tess();
      return 1;
    case 'l':
    case 'L':
      opengl::toggle_light();
      return 1;
    case 65470: // F1
      if(!parent->fullscreen_active()) {
	parent->fullscreen();
      } else {
	parent->fullscreen_off();
      }
      return 1;
    default:
      return Fl_Gl_Window::handle(event);
    }
  default:
    return Fl_Gl_Window::handle(event);
  }
}
