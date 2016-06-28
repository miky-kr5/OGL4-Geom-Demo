CXX = g++
TARGET = glsl_prog
OBJECTS = main.o GLSLProgram.o gui.o ogl.o
DEPENDS = $(OBJECTS:.o=.d)
CXXFLAGS = -ansi -pedantic -Wall -DGLM_FORCE_RADIANS
LDLIBS = -l GLEW -l GLU -l GL -l fltk -l fltk_gl

all: CXXFLAGS += -O2 -DNDEBUG
all: $(TARGET)

debug: CXXFLAGS += -g
debug: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -o $(TARGET) $(OBJECTS) $(CXXFLAGS) $(LDLIBS)

-include $(DEPENDS)

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $*.cpp -o $*.o
	$(CXX) -MM $(CXXFLAGS) $*.cpp > $*.d

clean:
	$(RM) $(TARGET) $(OBJECTS) $(DEPENDS)
