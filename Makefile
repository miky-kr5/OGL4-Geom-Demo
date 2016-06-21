CXX = g++
TARGET = glsl_prog
OBJECTS = main.o GLSLProgram.o
DEPENDS = $(OBJECTS:.o=.d)
CXXFLAGS = -ansi -pedantic -Wall
LDLIBS = -l GLEW -l glut -l GLU -l GL

all: CXXFLAGS += -O2 -D_NDEBUG
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
