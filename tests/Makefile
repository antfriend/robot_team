# Native tests for the portable firmware libraries (no Arduino, no hardware).
# Usage:  make        # build and run
#         make clean
CXX ?= g++
CXXFLAGS ?= -std=c++11 -Wall -Wextra -O2
LIB := ../firmware/libraries
INCLUDES := -I$(LIB)/Toot/src -I$(LIB)/TTDB/src -I$(LIB)/LinkPercept/src -I$(LIB)/EntityPercept/src -I$(LIB)/Gps/src -I$(LIB)/Pulse/src
SRCS := test_toot.cpp \
        $(LIB)/Toot/src/Toot.cpp \
        $(LIB)/Toot/src/TootCrypto.cpp \
        $(LIB)/TTDB/src/TtdbParse.cpp
LP_SRCS := test_linkpercept.cpp \
        $(LIB)/LinkPercept/src/LinkPercept.cpp
# SP0 entity-co-occurrence tier: WiFi BSSID sightings -> @LAT96 ENTITY records.
EP_SRCS := test_entitypercept.cpp \
        $(LIB)/EntityPercept/src/EntityPercept.cpp
# NMEA GGA decode for the roaming GPS anchor (semantic positioning SP2).
NMEA_SRCS := test_nmea.cpp \
        $(LIB)/Gps/src/Nmea.cpp
# Streams the real replicate/RFCs/rfc.ttdb.md through the firmware's TtdbParse.cpp
# to prove the compressed RFC corpus stays fleet-carryable as the RFCs evolve.
# (The corpus moved from RFCs/ to replicate/RFCs/ on 2026-07-31.)
RFC_SRCS := test_rfc_ttdb.cpp \
        $(LIB)/TTDB/src/TtdbParse.cpp
# Fleet-pulse chart scene extension: wire compatibility both ways + the scene
# surviving conductor handoff (TTN-RFC-0010).
PULSE_SRCS := test_pulse.cpp \
        $(LIB)/Toot/src/Toot.cpp \
        $(LIB)/Toot/src/TootCrypto.cpp \
        $(LIB)/Pulse/src/Pulse.cpp

test: build
	./test_toot
	./test_linkpercept
	./test_entitypercept
	./test_rfc_ttdb
	./test_nmea
	./test_pulse

build: $(SRCS) $(LP_SRCS) $(EP_SRCS) $(RFC_SRCS) $(NMEA_SRCS) $(PULSE_SRCS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRCS) -o test_toot
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(LP_SRCS) -o test_linkpercept
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(EP_SRCS) -o test_entitypercept
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(RFC_SRCS) -o test_rfc_ttdb
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(NMEA_SRCS) -o test_nmea
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(PULSE_SRCS) -o test_pulse

clean:
	rm -f test_toot test_toot.exe test_linkpercept test_linkpercept.exe \
	      test_entitypercept test_entitypercept.exe \
	      test_rfc_ttdb test_rfc_ttdb.exe test_nmea test_nmea.exe \
	      test_pulse test_pulse.exe

.PHONY: test build clean
