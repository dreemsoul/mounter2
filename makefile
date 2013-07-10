
PROGRAM = mounter2

# list of dependencies
INCLUDEDIRS = \
  -I/usr/include/gtk-2.0 -I/usr/lib/gtk-2.0/include -I/usr/include/pango-1.0 -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/pixman-1 -I/usr/include/libdrm -I/usr/include/libpng16 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/libpng16 -I/usr/include/pango-1.0 -I/usr/include/harfbuzz -I/usr/include/pango-1.0 -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/include/freetype2



LIBS =  -lgtk-x11-2.0 -lgdk-x11-2.0 -lpangocairo-1.0 -latk-1.0 -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lpangoft2-1.0 -lpango-1.0 -lgobject-2.0 -lglib-2.0 -lfreetype -lfontconfig



CXXSOURCES = main.c       # list of source files
CXXOBJECTS = $(CXXSOURCES:.c=.o)  # expands to list of object files
CXXFLAGS = -pthread $(INCLUDEDIRS)
CXX = gcc

LDFLAGS = $(LIBDIRS) $(LIBS)


all: $(PROGRAM)


$(PROGRAM): $(CXXOBJECTS)
	$(CXX) -o $@ $(CXXOBJECTS) $(LDFLAGS)


main.o: main.c
	$(CXX) $(CXXFLAGS) -Wall -g -c main.c 


clean:
	$(RM) -f $(CXXOBJECTS) $(PROGRAM)



run:
	./$(PROGRAM) 
