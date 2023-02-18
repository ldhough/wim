CXX = clang++
CXXFLAGS = -std=c++20 -O0 -Wall -g

UNAME = $(shell uname -s)
ifeq ($(UNAME),Darwin)
CXXFLAGS += -framework CoreGraphics -framework Foundation -framework ApplicationServices -ObjC++
CXXFLAGS += -I/opt/homebrew/opt/libev/include -L/opt/homebrew/opt/libev/lib -lev
IS_APPLE_SILICON = $(shell lipo /bin/zsh -verify_arch arm64e && echo 1 || echo 0)
ifeq ($(IS_APPLE_SILICON),1)
CXXFLAGS += -arch arm64
endif
endif

WIM_SRCS = src/wim.cc src/utils.cc src/pid_observer.mm src/display_manager.mm src/key_interceptor.mm src/window_transformer.mm
WIM_OBJS = $(subst \.cc\|\.mm,.o,$(WIM_SRCS))

all: wim

.PHONY: clean
clean:
	rm -f obj/*.o

obj/utils.o: src/utils.cc src/utils.h
	$(CXX) $(CXXFLAGS) -c src/utils.cc -o $@

obj/pid_observer.o: src/pid_observer.mm src/pid_observer.h
	$(CXX) $(CXXFLAGS) -c src/pid_observer.mm -o $@

obj/display_manager.o: src/display_manager.mm src/display_manager.h
	$(CXX) $(CXXFLAGS) -c src/display_manager.mm -o $@

obj/key_interceptor.o: src/key_interceptor.mm src/key_interceptor.h src/keycodes.h
	$(CXX) $(CXXFLAGS) -c src/key_interceptor.mm -o $@

obj/window_transformer.o: src/window_transformer.mm src/window_transformer.h
	$(CXX) $(CXXFLAGS) -c src/window_transformer.mm -o $@

obj/wim.o: src/wim.cc src/pid_observer.h src/display_manager.h src/key_interceptor.h
	$(CXX) $(CXXFLAGS) -c src/wim.cc -o $@

wim: $(WIM_OBJS)
	$(CXX) $(CXXFLAGS) -o bin/wim $(WIM_OBJS)

