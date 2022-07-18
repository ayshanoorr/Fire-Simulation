#INCFLAGS = -I /mit/6.837/public/include/vecmath
#INCFLAGS += -I /mit/glut/include
#LINKFLAGS = -L /mit/6.837/public/lib -l vecmath
#LINKFLAGS += -L /mit/galut/lib -lGL -lGLU -lglut -lX11 -lXi
INCFLAGS  = -I ./GL
INCFLAGS += -I ./lib
INCFLAGS += -I ./vecmath/include


#INCFLAGS += -I ~/vecmath/include

LINKFLAGS  = -lglut -lGL -lGLU -lglfw -lGLEW -lm -lX11 -lXrandr -ldl -lSDL2 -lSDL2_image
LINKFLAGS += -L /usr/lib -lvecmath
#LINKFLAGS += -L ~/vecmath/lib -lvecmath
#LINKFLAGS += -L /usr/lib/ -lfltk -lfltk_gl

CFLAGS    = -g
CC        = g++
SRCS      = Particle.cpp Window.cpp Main.cpp

SRCS += $(wildcard vecmath/src/*.cpp)
OBJS      = $(SRCS:.cpp=.o)
PROG      = game

all: $(SRCS) $(PROG)

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LINKFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -c -o $@ $(INCFLAGS)

depend:
	makedepend $(INCFLAGS) -Y $(SRCS)

clean:
	rm $(OBJS) $(PROG)
