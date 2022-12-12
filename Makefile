
debug ?= off
os ?= LINUX
subfolders = $(subst cminus,,$(subst cminus/,,$(shell find cminus -type d)))
cppargs = -std=c++17 -Icminus -Wall -Wextra
ifeq ($(debug),on)
	cppargs += -g
endif
buildfolders = $(addprefix build/,$(subfolders))
ccfiles = $(shell find cminus -name "*.cc")
hfiles = $(ccfiles:.cc=.h)
ofiles = $(subst cminus,build,$(ccfiles:.cc=.o))
dfiles = $(ofiles:.o=.d)
testfiles = $(shell find tests/*.cc)
# testbuilds = $(subst .cc,,$(addprefix build/,$(testfiles)))

ifeq ($(os),LINUX)
	cc = g++
	cppargs += -DOS_LINUX
else ifeq ($(os),WINDOWS)
	cc = x86_64-w64-mingw32-g++
	cppargs += -static
	cppargs += -DOS_WINDOWS
else
	exit 1
endif

# Makefile starting point
.PHONY: all
all: build $(buildfolders) build/main build/runtests

# Clean up build fodler and output datapack
clean: clean_build clean_dbg

# Clean up build folder
clean_build:
	rm -r -f build/*

# Clean up output datapack and debug files
clean_dbg:
	rm -f *.debug

# Create output C++ files and use them to build main.cc
build/main: $(ofiles)
	$(cc) $(cppargs) -o build/main $(ofiles)

# Dependency files
-include $(dfiles)

# Output C++ files
build/%.o: cminus/%.cc Makefile
	$(cc) $(cppargs) -MMD -MP -c $< -o $@

# Testing program
build/runtests: runtests.cc build/tmp
	$(cc) $(cppargs) -o $@ $<
build/tmp:
	mkdir build/tmp

# Create folders if neccessary
build:
	mkdir build
$(buildfolders):
	mkdir $@