#
# 'make'        			build executable file 'matrix_driver'
# 'make COMPILE_ARM=true'   build executable file 'matrix_driver', cross compiling for ARM on a raspberry pi
#								On ARCH, use the `arm-none-linux-gnueabihf-toolchain-bin` AUR package to get the arm compiler toolchain
# 'make clean'  			removes all .o and executable files & clears the output directory
#

RGB_LIB_DISTRIBUTION=matrix
RGB_INCDIR	=$(RGB_LIB_DISTRIBUTION)/include
RGB_LIBDIR	=$(RGB_LIB_DISTRIBUTION)/lib
RGB_LIBRARY_NAME=rgbmatrix
RGB_LIBRARY	=$(RGB_LIBDIR)/lib$(RGB_LIBRARY_NAME).a
LDFLAGS		+=-L$(RGB_LIBDIR) -l$(RGB_LIBRARY_NAME) -lrt -lm -lpthread

RGB_SOURCES	:= $(wildcard $(patsubst %,%/*.cpp, $(RGB_LIBDIR)))
RGB_OBJECTS	:= $(RGB_SOURCES:.cpp=.o)

# define the Cpp compiler to use
CXX = g++
CC = gcc
CXX-rpi = arm-none-linux-gnueabihf-g++
CC-rpi = arm-none-linux-gnueabihf-gcc

ifdef COMPILE_ARM
CXX = $(CXX-rpi)
CC = $(CC-rpi)
endif

# define any compile-time flags
CXXFLAGS	:= -std=c++17 -Wall -Wextra -g

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
LFLAGS =

# define output directory
OUTPUT	:= output

# define source directory
SRC		:= src

# define include directory
INCLUDE	:= include

# define lib directory
LIB		:= lib

ifeq ($(OS),Windows_NT)
MAIN	:= matrix_driver.exe
SOURCEDIRS	:= $(SRC)
INCLUDEDIRS	:= $(INCLUDE)
LIBDIRS		:= $(LIB)
FIXPATH = $(subst /,\,$1)
RM			:= del /q /f
MD	:= mkdir
CP	:= cp
RECURSE = /s
BOOST_INCLUDES = ""
else
MAIN	:= matrix_driver
SOURCEDIRS	:= $(shell find $(SRC) -type d)
INCLUDEDIRS	:= $(shell find {$(INCLUDE),$(RGB_INCDIR)} -type d)
LIBDIRS		:= $(shell find $(LIB) -type d)
FIXPATH = $1
RM = rm -f
MD	:= mkdir -p
CP	:= cp -r
RECURSE = -R
BOOST_INCLUDES = -Iboost_1_83_0# -I/usr/include/libpng16
endif

# define any directories containing header files other than /usr/include
INCLUDES	:= $(patsubst %,-I%, $(INCLUDEDIRS:%/=%))

# define the C libs
LIBS		:= $(patsubst %,-L%, $(LIBDIRS:%/=%))

# define the C source files
SOURCES		:= $(wildcard $(patsubst %,%/*.cpp, $(SOURCEDIRS)))

# define the C object files
OBJECTS		:= $(SOURCES:.cpp=.o)

# define the dependency output files
DEPS		:= $(OBJECTS:.o=.d)

#
# The following part of the makefile is generic; it can be used to
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

OUTPUTMAIN	:= $(call FIXPATH,$(OUTPUT)/$(MAIN))

all: $(OUTPUT) $(MAIN) $(RGB_LIBRARY)
	@echo Executing 'all' complete!

$(OUTPUT):
	$(MD) $(OUTPUT)

$(MAIN): $(OBJECTS) $(RGB_LIBRARY)
	$(CXX) -static $(CXXFLAGS) $(INCLUDES) -o $(OUTPUTMAIN) $(OBJECTS) $(LFLAGS) $(LIBS) $(LDFLAGS) $(BOOST_INCLUDES)
	$(CP) assets $(call FIXPATH,$(OUTPUT)/assets)

$(RGB_LIBRARY):
	$(MAKE) USER_DEFINES=-static CC=$(CC) CXX=$(CXX) -C $(RGB_LIBDIR)

# include all .d files
-include $(DEPS)

# this is a suffix replacement rule for building .o's and .d's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file)
# -MMD generates dependency output files same name as the .o file
# (see the gnu make manual section about automatic variables)
.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(BOOST_INCLUDES) -c -MMD $<  -o $@ $(LDFLAGS)

.PHONY: clean
clean:
	$(RM) $(RECURSE) $(call FIXPATH,$(OUTPUT)/assets)
	$(RM) $(OUTPUTMAIN)
	$(RM) $(call FIXPATH,$(OBJECTS))
	$(RM) $(RGB_LIBDIR)/{*.{o,a,so.1},compiler-flags}
	$(RM) $(call FIXPATH,$(DEPS))
	@echo Cleanup complete!

run: all
	./$(OUTPUTMAIN)
	@echo Executing 'run: all' complete!
