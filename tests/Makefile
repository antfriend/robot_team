# Native tests for the portable firmware libraries (no Arduino, no hardware).
# Usage:  make        # build and run
#         make clean
CXX ?= g++
CXXFLAGS ?= -std=c++11 -Wall -Wextra -O2
LIB := ../firmware/libraries
INCLUDES := -I$(LIB)/Toot/src -I$(LIB)/TTDB/src -I$(LIB)/LinkPercept/src -I$(LIB)/EntityPercept/src -I$(LIB)/AcousticPercept/src -I$(LIB)/MotionPercept/src -I$(LIB)/PerceptLearn/src -I$(LIB)/Gps/src -I$(LIB)/Pulse/src -I$(LIB)/TraceField/src -I$(LIB)/TimeStream/src -I$(LIB)/Social/src -I$(LIB)/Semantic/src -I$(LIB)/Attention/src
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
# ⚠ Sid.cpp AND TtdbParse.cpp joined this list at RFC-0010 stage 2: @LAT91 is the first
# lane to write a stable id, so the belief builder calls sid::stampKey and the test reads
# it back with ttdbHeaderSid. Omitting either links NOTHING — the same trap as $(TS), and
# the THIRD instance of this defect in one day. It was missed here because the test was
# being built by hand with an explicit source list, which is precisely the habit that lets
# a Makefile rot unnoticed: if you build by hand, check `make` too before committing.
PL_SRCS := test_perceptlearn.cpp \
        $(LIB)/PerceptLearn/src/PerceptLearn.cpp $(TS) \
        $(LIB)/TTDB/src/Sid.cpp $(LIB)/TTDB/src/TtdbParse.cpp
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
TF_SRCS := test_tracefield.cpp \
        $(LIB)/TraceField/src/TraceField.cpp
# The default network, stage 1 (docs/design/default-network.md §6): capability advertisement, the
# three-level status, and the staleness instrument whose own falsifier is pre-registered.
# ⚠ Stage 3 (RFC-0010 §5, the @LAT101 field) added FOUR dependencies in one go — decay
# arithmetic (TraceField), the stamp (TS), the sid (Sid) and the header-sid reader
# (TtdbParse). Omitting ANY of them links NOTHING and `make test` re-runs a stale
# binary; that has happened four times in this file. check_makefile.py now catches it —
# run it before committing a Makefile change.
SOC_SRCS := test_social.cpp \
        $(LIB)/Social/src/Social.cpp \
        $(LIB)/TraceField/src/TraceField.cpp $(TS) \
        $(LIB)/TTDB/src/Sid.cpp $(LIB)/TTDB/src/TtdbParse.cpp
# Stable record identity (TTDB-RFC-0010 §4, decided 2026-08-09). Carries the CROSS-LANGUAGE
# vectors: the same eight values are computed by scripts/sid_probe.py, and a divergence
# between them is silent and total (every citation would resolve `stale` against a good
# record), so it is pinned on both sides.
SID_SRCS := test_sid.cpp \
        $(LIB)/TTDB/src/Sid.cpp
# RFC-0010 §7.2 stage 1: readers accept `#sid`. The laptop half is test_citation_py.py and
# the two MUST agree — a citation is resolved on whichever side is holding the file.
# ⚠ This variable was the FOURTH undefined-variable defect in this file in one day, added
# by the same session that fixed the first three. `check_makefile.py` now makes that
# impossible to miss; run it before committing a Makefile change.
CIT_SRCS := test_citation.cpp \
        $(LIB)/TTDB/src/TtdbParse.cpp
# The TTDB INDEX CAP (2026-08-11). The first native test to drive the REAL `Ttdb` —
# begin(), recordSpan() and removeLaneRange() TOGETHER — through tests/shim/, which
# stands in for <Arduino.h> and <FS.h>. That is the point: the defect lives in the
# interaction of those three (a prune walks the INDEX, and the last indexed record's span
# used to run to EOF, so pruning its lane deleted every record past the cap). A replica of
# any one of them — which is all test_rfc_ttdb.cpp can do — cannot reproduce it.
# ⚠ Needs its OWN flags: -I shim for the stand-ins, and a small cap so saturation is
# reachable in a fixture instead of needing 289 records.
IDX_SRCS := test_ttdb_index.cpp \
        $(LIB)/TTDB/src/TTDB.cpp $(LIB)/TTDB/src/TtdbParse.cpp
IDX_FLAGS := -I shim -DTTDB_MAX_RECORDS=16
# ACT-III Phase C: TTG-RFC-0003 §2 counting, streamed, with fold-before-forget. Holds C3's
# two pre-registered gates - belief lines byte-exact AND identical under reordered
# episodes, and identical after evicting the oldest with the fold. Self-contained (no
# TTDB, no stamp): the consolidator is a pure function of the percepts it is handed.
SEM_SRCS := test_semantic.cpp $(LIB)/Semantic/src/Semantic.cpp
# ACT-III Phase C, the EPISODE tier: writer, reader, fold checkpoint and ring, driven through
# the whole append -> fold -> commit -> cut -> reboot protocol with commits and cuts made to
# FAIL. TtdbParse.cpp is here so the rendered header is indexed by the firmware's own parser.
EPI_SRCS := test_episode.cpp $(LIB)/Semantic/src/Episode.cpp $(LIB)/Semantic/src/Semantic.cpp \
        $(LIB)/TTDB/src/TtdbParse.cpp $(LIB)/TimeStream/src/TimeStream.cpp \
        $(LIB)/EntityPercept/src/EntityPercept.cpp $(LIB)/AcousticPercept/src/AcousticPercept.cpp \
        $(LIB)/LinkPercept/src/LinkPercept.cpp $(LIB)/MotionPercept/src/MotionPercept.cpp
# ACT-III Phase C4: TTG-RFC-0004 §4 — bounded pulse stamps, partial order across agents,
# maximal facts, and the bar view two agents agree on without coordinating (§4.8 items 1-4).
FT_SRCS := test_fleettime.cpp $(LIB)/Semantic/src/FleetTime.cpp $(LIB)/Semantic/src/Semantic.cpp
# C4 stage 1 (docs/design/episode-order.md): per-agent seq, the vector clock and its wire
# form, the seq:/follows: block in a rendered episode, and order() over re-parsed text.
EO_SRCS := test_episode_order.cpp $(LIB)/Semantic/src/EpisodeOrder.cpp \
        $(LIB)/Semantic/src/Episode.cpp $(LIB)/Semantic/src/FleetTime.cpp \
        $(LIB)/Semantic/src/Semantic.cpp
# C4 stage 2 (docs/design/episode-order.md §7): WANT/DATA/DONE, reassembly, the held lane,
# and the bar view two agents agree on (TTG-RFC-0004 §4.8 item 4).
ED_SRCS := test_episode_delivery.cpp $(LIB)/Semantic/src/EpisodeDelivery.cpp \
        $(LIB)/Semantic/src/EpisodeOrder.cpp $(LIB)/Semantic/src/Episode.cpp \
        $(LIB)/Semantic/src/FleetTime.cpp $(LIB)/Semantic/src/Semantic.cpp
# Sensorium Phase S1: the EPS arbiter (decay, dwell, margin), neighbour novelty, motion
# salience, and S1's done-condition as four scenarios. Portable, self-contained.
ATT_SRCS := test_attention.cpp $(LIB)/Attention/src/Attention.cpp

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
	./test_tracefield
	./test_social
	./test_sid
	./test_citation
	./test_ttdb_index
	./test_semantic
	./test_episode
	./test_fleettime
	./test_episode_order
	./test_episode_delivery
	./test_attention

build: $(SRCS) $(LP_SRCS) $(EP_SRCS) $(MP_SRCS) $(PL_SRCS) $(RFC_SRCS) $(SYM_SRCS) $(NMEA_SRCS) $(PULSE_SRCS) $(TF_SRCS) $(TSTREAM_SRCS) $(SOC_SRCS) $(SID_SRCS) $(CIT_SRCS) $(IDX_SRCS) $(SEM_SRCS) $(EPI_SRCS) $(FT_SRCS) $(EO_SRCS) $(ED_SRCS) $(ATT_SRCS)
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
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(TF_SRCS) -o test_tracefield
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SOC_SRCS) -o test_social
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SID_SRCS) -o test_sid
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(CIT_SRCS) -o test_citation
	$(CXX) $(CXXFLAGS) $(IDX_FLAGS) $(INCLUDES) $(IDX_SRCS) -o test_ttdb_index
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SEM_SRCS) -o test_semantic
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(EPI_SRCS) -o test_episode
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(FT_SRCS) -o test_fleettime
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(EO_SRCS) -o test_episode_order
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(ED_SRCS) -o test_episode_delivery
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(ATT_SRCS) -o test_attention

clean:
	rm -f test_toot test_toot.exe test_linkpercept test_linkpercept.exe \
	      test_entitypercept test_entitypercept.exe \
	      test_motionpercept test_motionpercept.exe \
	      test_perceptlearn test_perceptlearn.exe \
	      test_rfc_ttdb test_rfc_ttdb.exe test_nmea test_nmea.exe \
	      test_symmetric_edges test_symmetric_edges.exe \
	      test_pulse test_pulse.exe \
	      test_timestream test_timestream.exe \
	      test_tracefield test_tracefield.exe \
	      test_social test_social.exe \
	      test_sid test_sid.exe \
	      test_citation test_citation.exe \
	      test_ttdb_index test_ttdb_index.exe \
	      test_semantic test_semantic.exe \
	      test_episode test_episode.exe test_fleettime test_fleettime.exe \
	      test_episode_order test_episode_order.exe \
	      test_episode_delivery test_episode_delivery.exe \n	      test_attention test_attention.exe

.PHONY: test build clean
