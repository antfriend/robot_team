# Native tests for the portable firmware libraries (no Arduino, no hardware).
# Usage:  make        # build and run
#         make clean
CXX ?= g++
CXXFLAGS ?= -std=c++11 -Wall -Wextra -O2
LIB := ../firmware/libraries
INCLUDES := -I$(LIB)/Toot/src -I$(LIB)/TTDB/src
SRCS := test_toot.cpp \
        $(LIB)/Toot/src/Toot.cpp \
        $(LIB)/Toot/src/TootCrypto.cpp \
        $(LIB)/TTDB/src/TtdbParse.cpp

test: build
	./test_toot

build: $(SRCS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRCS) -o test_toot

clean:
	rm -f test_toot test_toot.exe

.PHONY: test build clean
