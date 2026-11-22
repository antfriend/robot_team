"""PW-1 pre-registered constants (TTDB-RFC-0011 v0.1.2, section 8).

Committed BEFORE any code reads master/. Do not change after seeing data.
"""

# pe_span: full-scale of each channel's raw difference. pe = min(255, |d| * 255 // span).
PE_SPAN_ACOUSTIC = 32767   # int16 samples: firmware/libraries/AcousticPercept/src/AcousticPercept.h:76
                           # (addBlock(const int16_t*...)); rms_mean is bounded by int16 full scale.
PE_SPAN_MOTION = 16000     # mg; BMI270 +/-8 g range (datasheet default). The firmware sets no range
                           # (cardputer_console.ino ~3874 uses library defaults) so this is the
                           # datasheet value, confirmed by Dan Ray 2026-11-22.
PE_SPAN_LINK = 100         # dB; RSSI -120..-20 dBm (brief)
PE_SPAN_ENTITY = None      # Jaccard distance already 0..1; pe = round(dist * 255)

# Fold, RFC section 4.3
PI_ALPHA = 4
PI_SCALE = 8192
PI_SCALES_ROBUSTNESS = (4096, 8192, 16384)

# Decision rule
MIN_RESIDUALS = 30         # per series, and per half for the stability check
DRIFT_FLAG = 24            # |pi_ewma - pi_mean| above this flags the series as drifting
SEP_PASS, SEP_FALSIFIED = 32, 16          # range of per-channel median pi across nodes: pass >, falsified <=
STAB_TOL = 24                        # |pi1 - pi2| <=
STAB_PASS, STAB_FALSIFIED = 0.70, 0.50    # share of series: pass >=, falsified <

# Archive scope (decided 2026-11-22): all master/**/*.md, deduplicated on
# (node, lane, stream, t_ms, body digest); node = filename prefix up to first '_' ;
# lanes 94-97 only, never 101. RFC's "78" is stale (187 files at this date).
LANES = (94, 95, 96, 97)
