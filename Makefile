CXX = clang++
CXXFLAGS = -std=c++20 -O0 -framework CoreGraphics

IS_APPLE_SILICON = $(shell lipo /bin/zsh -verify_arch arm64e && echo 1 || echo 0)

WIM_SRCS = src/wim.cc src/pid_observer.mm src/display_manager.mm
WIM_OBJS = $(subst \.cc\|\.mm,.o,$(WIM_SRCS))

all: wim

.PHONY: clean
clean:
	rm -f obj/*.o

obj/pid_observer.o: src/pid_observer.mm src/pid_observer.h
	$(CXX) $(CXXFLAGS) -c src/pid_observer.mm -o $@

obj/display_manager.o: src/display_manager.mm src/display_manager.h
	$(CXX) $(CXXFLAGS) -c src/display_manager.mm -o $@

obj/wim.o: src/wim.cc src/pid_observer.h src/display_manager.h
	$(CXX) $(CXXFLAGS) -c src/wim.cc -o $@

wim: $(WIM_OBJS)
	$(CXX) $(CXXFLAGS) -o bin/wim $(WIM_OBJS)

