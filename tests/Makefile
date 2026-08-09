# Native tests for the portable firmware libraries (no Arduino, no hardware).
# Usage:  make        # build and run
#         make clean
CXX ?= g++
CXXFLAGS ?= -std=c++11 -Wall -Wextra -O2
LIB := ../firmware/libraries
INCLUDES := -I$(LIB)/Toot/src -I$(LIB)/TTDB/src -I$(LIB)/LinkPercept/src -I$(LIB)/EntityPercept/src -I$(LIB)/MotionPercept/src -I$(LIB)/PerceptLearn/src -I$(LIB)/Gps/src -I$(LIB)/Pulse/src -I$(LIB)/TraceField/src -I$(LIB)/TimeStream/src -I$(LIB)/LaneGen/src -I$(LIB)/Social/src
SRCS := test_toot.cpp \
        $(LIB)/Toot/src/Toot.cpp \
        $(LIB)/Toot/src/TootCrypto.cpp \
        $(LIB)/TTDB/src/TtdbParse.cpp
# ⚠ TS is needed by every percept tier: they all stamp records through
# timestream::buildStamp. Omitting it links NOTHING — and because the recipe leaves the
# previous session's binary in place, `make test` then RUNS A STALE .exe and reports PASS
# for code that was never compiled. Found 2026-08-07 by building the suite by hand.
TS := $(LIB)/TimeStream/src/TimeStream.cpp
LP_SRCS := test_linkpercept.cpp \
        $(LIB)/LinkPercept/src/LinkPercept.cpp $(TS)
# SP0 entity-co-occurrence tier: WiFi BSSID sightings -> @LAT96 ENTITY records.
EP_SRCS := test_entitypercept.cpp \
        $(LIB)/EntityPercept/src/EntityPercept.cpp $(TS)
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
        $(LIB)/MotionPercept/src/MotionPercept.cpp $(TS)
# Stages B/C/D of Learning from Action: the armed expectation, the @LAT92 outcome
# testimony, and Rule 3's fold into an @LAT91 belief. This variable was MISSING — the
# recipe below referenced an undefined $(PL_SRCS), so `make` invoked the compiler with
# no input files and test_perceptlearn could never have been built by it.
PL_SRCS := test_perceptlearn.cpp \
        $(LIB)/PerceptLearn/src/PerceptLearn.cpp $(TS)
# TTDB-RFC-0003 v1.1 §7.1: symmetric types are written in BOTH directions by the
# author, never inferred by a parser — so a one-directional `opposes` is a defect a
# validator must report. Runs against the globes the handhelds actually carry.
SYM_SRCS := test_symmetric_edges.cpp \
        $(LIB)/TTDB/src/TtdbParse.cpp
# ⚠ THESE THREE WERE MISSING (fixed 2026-08-09) — the same defect the PL_SRCS comment
# above describes, in three more places. `build` referenced $(TSTREAM_SRCS), $(LG_SRCS)
# and $(TF_SRCS), make expanded them to nothing, and the compiler was invoked with no
# input files. Because the recipe leaves the previous session's binary in place, `make
# test` then RAN THE STALE .exe and reported PASS for code it had never compiled. The
# suite's own report of "12/12" was therefore true of three binaries nobody had built.
TSTREAM_SRCS := test_timestream.cpp \
        $(LIB)/TimeStream/src/TimeStream.cpp
# ⚠ LaneGen needs $(TS) for the same reason every percept tier does — it stamps boundary
# records through timestream::buildStamp. Defining LG_SRCS without it linked NOTHING and
# `make test` re-ran the stale test_lanegen.exe, which passed. Two defects of the same
# shape, stacked: the missing variable hid the missing dependency.
LG_SRCS := test_lanegen.cpp \
        $(LIB)/LaneGen/src/LaneGen.cpp $(TS)
TF_SRCS := test_tracefield.cpp \
        $(LIB)/TraceField/src/TraceField.cpp
# The default network, stage 1 (default-network.md §6): capability advertisement, the
# three-level status, and the staleness instrument whose own falsifier is pre-registered.
SOC_SRCS := test_social.cpp \
        $(LIB)/Social/src/Social.cpp
# Stable record identity (TTDB-RFC-0010 §4, decided 2026-08-09). Carries the CROSS-LANGUAGE
# vectors: the same eight values are computed by scripts/sid_probe.py, and a divergence
# between them is silent and total (every citation would resolve `stale` against a good
# record), so it is pinned on both sides.
SID_SRCS := test_sid.cpp \
        $(LIB)/TTDB/src/Sid.cpp

test: build
	./test_toot
	./test_linkpercept
	./test_entitypercept
	./test_motionpercept
	./test_perceptlearn
	./test_rfc_ttdb
	./test_symmetric_edges
	./test_nmea
	./test_pulse
	./test_timestream
	./test_lanegen
	./test_tracefield
	./test_social
	./test_sid

build: $(SRCS) $(LP_SRCS) $(EP_SRCS) $(MP_SRCS) $(PL_SRCS) $(RFC_SRCS) $(SYM_SRCS) $(NMEA_SRCS) $(PULSE_SRCS) $(TF_SRCS) $(TSTREAM_SRCS) $(LG_SRCS) $(SOC_SRCS) $(SID_SRCS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRCS) -o test_toot
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(LP_SRCS) -o test_linkpercept
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(EP_SRCS) -o test_entitypercept
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(MP_SRCS) -o test_motionpercept
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(PL_SRCS) -o test_perceptlearn
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(RFC_SRCS) -o test_rfc_ttdb
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SYM_SRCS) -o test_symmetric_edges
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(NMEA_SRCS) -o test_nmea
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(PULSE_SRCS) -o test_pulse
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(TSTREAM_SRCS) -o test_timestream
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(LG_SRCS) -o test_lanegen
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(TF_SRCS) -o test_tracefield
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SOC_SRCS) -o test_social
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SID_SRCS) -o test_sid

clean:
	rm -f test_toot test_toot.exe test_linkpercept test_linkpercept.exe \
	      test_entitypercept test_entitypercept.exe \
	      test_motionpercept test_motionpercept.exe \
	      test_perceptlearn test_perceptlearn.exe \
	      test_rfc_ttdb test_rfc_ttdb.exe test_nmea test_nmea.exe \
	      test_symmetric_edges test_symmetric_edges.exe \
	      test_pulse test_pulse.exe \
	      test_timestream test_timestream.exe test_lanegen test_lanegen.exe \
	      test_tracefield test_tracefield.exe \
	      test_social test_social.exe \
	      test_sid test_sid.exe

.PHONY: test build clean
