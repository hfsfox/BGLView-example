NAME = GLView
TYPE = APP
SRCS = \
	Sources/App.cpp \
	Sources/GLWindow.cpp\

RDEFS = GLView.rdef
LIBS = be game localestub GL $(STDCPPLIBS)
SYSTEM_INCLUDE_PATHS =
WARNINGS = ALL
DEVEL_DIRECTORY := \
	$(shell findpaths -r "makefile_engine" B_FIND_PATH_DEVELOP_DIRECTORY)
include $(DEVEL_DIRECTORY)/etc/makefile-engine
