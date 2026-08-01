# Native tests for the portable firmware libraries (no Arduino, no hardware).
# Usage:  make        # build and run
#         make clean
CXX ?= g++
CXXFLAGS ?= -std=c++11 -Wall -Wextra -O2
LIB := ../firmware/libraries
INCLUDES := -I$(LIB)/Toot/src -I$(LIB)/TTDB/src -I$(LIB)/LinkPercept/src -I$(LIB)/EntityPercept/src -I$(LIB)/MotionPercept/src -I$(LIB)/Gps/src -I$(LIB)/Pulse/src
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
# SP0 motion tier (@LAT95) AND the transition form it emits (@LAT93): the
# @PERCEPT:before -> @PERCEPT:after pair TTDB-RFC-0006 §5 makes non-negotiable.
# Until 2026-08-01 this tier had only ever been verified on hardware.
MP_SRCS := test_motionpercept.cpp \
        $(LIB)/MotionPercept/src/MotionPercept.cpp
# TTDB-RFC-0003 v1.1 §7.1: symmetric types are written in BOTH directions by the
# author, never inferred by a parser — so a one-directional `opposes` is a defect a
# validator must report. Runs against the globes the handhelds actually carry.
SYM_SRCS := test_symmetric_edges.cpp \
        $(LIB)/TTDB/src/TtdbParse.cpp

test: build
	./test_toot
	./test_linkpercept
	./test_entitypercept
	./test_motionpercept
	./test_rfc_ttdb
	./test_symmetric_edges
	./test_nmea
	./test_pulse

build: $(SRCS) $(LP_SRCS) $(EP_SRCS) $(MP_SRCS) $(RFC_SRCS) $(SYM_SRCS) $(NMEA_SRCS) $(PULSE_SRCS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRCS) -o test_toot
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(LP_SRCS) -o test_linkpercept
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(EP_SRCS) -o test_entitypercept
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(MP_SRCS) -o test_motionpercept
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(RFC_SRCS) -o test_rfc_ttdb
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SYM_SRCS) -o test_symmetric_edges
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(NMEA_SRCS) -o test_nmea
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(PULSE_SRCS) -o test_pulse

clean:
	rm -f test_toot test_toot.exe test_linkpercept test_linkpercept.exe \
	      test_entitypercept test_entitypercept.exe \
	      test_motionpercept test_motionpercept.exe \
	      test_rfc_ttdb test_rfc_ttdb.exe test_nmea test_nmea.exe \
	      test_symmetric_edges test_symmetric_edges.exe \
	      test_pulse test_pulse.exe

.PHONY: test build clean
