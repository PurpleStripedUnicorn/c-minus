
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
all: build $(buildfolders) build/main build/runtests build/combined_compile

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
build/%.o: cminus/%.cc Makefile $(buildfolders)
	$(cc) $(cppargs) -MMD -MP -c $< -o $@

# Testing program and useful tools
build/runtests: runtests.cc build/tmp $(buildfolders)
	$(cc) $(cppargs) -o $@ $<
build/combined_compile: combined_compile.cc build/tmp $(buildfolders)
	$(cc) $(cppargs) -o $@ $<
build/tmp: $(buildfolders)
	mkdir build/tmp

# Create folders if neccessary
build:
	mkdir build
$(buildfolders):
	mkdir -p $@