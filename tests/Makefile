# Native tests for the portable firmware libraries (no Arduino, no hardware).
# Usage:  make        # build and run
#         make clean
CXX ?= g++
CXXFLAGS ?= -std=c++11 -Wall -Wextra -O2
LIB := ../firmware/libraries
INCLUDES := -I$(LIB)/Toot/src -I$(LIB)/TTDB/src -I$(LIB)/LinkPercept/src
SRCS := test_toot.cpp \
        $(LIB)/Toot/src/Toot.cpp \
        $(LIB)/Toot/src/TootCrypto.cpp \
        $(LIB)/TTDB/src/TtdbParse.cpp
LP_SRCS := test_linkpercept.cpp \
        $(LIB)/LinkPercept/src/LinkPercept.cpp
# Streams the real RFCs/rfc.ttdb.md through the firmware's TtdbParse.cpp to prove
# the compressed RFC corpus stays fleet-carryable as the RFCs evolve.
RFC_SRCS := test_rfc_ttdb.cpp \
        $(LIB)/TTDB/src/TtdbParse.cpp

test: build
	./test_toot
	./test_linkpercept
	./test_rfc_ttdb

build: $(SRCS) $(LP_SRCS) $(RFC_SRCS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRCS) -o test_toot
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(LP_SRCS) -o test_linkpercept
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(RFC_SRCS) -o test_rfc_ttdb

clean:
	rm -f test_toot test_toot.exe test_linkpercept test_linkpercept.exe \
	      test_rfc_ttdb test_rfc_ttdb.exe

.PHONY: test build clean
