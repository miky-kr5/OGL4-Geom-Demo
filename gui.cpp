#include "gui.hpp"

#include <iostream>

static void redraw_callback(void * arg) {
  GlGui * window = static_cast<GlGui *>(arg);
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
  return Fl_Gl_Window::handle(event);
}
