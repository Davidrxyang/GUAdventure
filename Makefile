
#this Makefile was created by user "bjj" on GitHub


program_NAME := GU
program_CXX_SRCS := $(wildcard *.cpp)
program_CXX_OBJS := ${program_CXX_SRCS:.cpp=.o}
progaram_CXX_INCLS := ${wildcard *.h}
program_OBJS := $(program_CXX_OBJS)
program_INCLUDE_DIRS := /usr/include/SDL2
program_LIBRARY_DIRS :=
program_LIBRARIES := SDL2

CPPFLAGS = $(foreach includedir,$(program_INCLUDE_DIRS),-I$(includedir))
LDFLAGS = $(foreach librarydir,$(program_LIBRARY_DIRS),-L$(librarydir))
LDLIBS = $(foreach library,$(program_LIBRARIES),-l$(library))

LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) $(TARGET_ARCH)

.PHONY: all clean distclean

all: $(program_NAME)

$(program_NAME): $(program_OBJS)
	$(LINK.cc) $(program_OBJS) -o $(program_NAME) $(LDLIBS)

clean:
	@- $(RM) $(program_NAME)
	@- $(RM) $(program_OBJS)

distclean: clean