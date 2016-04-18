noinst_HEADERS = Assignment2.h BaseApplication.h GameObject.h Map.h
bin_PROGRAMS = assignment2
assignment2_CPPFLAGS = -I$(top_srcdir)
assignment2_SOURCES = Assignment2.cpp BaseApplication.cpp GameObject.cpp Map.cpp
assignment2_CXXFLAGS = $(OGRE_CFLAGS) $(OIS_CFLAGS) $(bullet_CFLAGS)
assignment2_LDADD = $(OGRE_LIBS) $(OIS_LIBS) $(bullet_LIBS)
assignment2_LDFLAGS = -lOgreOverlay -lboost_system -lSDL -lSDL_net -lSDL_mixer

EXTRA_DIST = buildit makeit
AUTOMAKE_OPTIONS = foreign
