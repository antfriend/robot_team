"""PW-1b pre-registered constants (TTDB-RFC-0011 open question 6). See PW1B-PROTOCOL.md.

Committed BEFORE any PW-1b code reads master/. Do not change after seeing data.
Everything not listed here is PW-1's, imported unchanged from tools/pw1/pw1_constants.py.
"""

# pe_span by rule R1/R2 (PW1B-PROTOCOL.md section 2). pe = min(255, |d| * 255 // span).
PE_SPAN_ACOUSTIC = 900   # R1. ACOUSTICPERCEPT_TRANSIENT_FLOOR, AcousticPercept.h:45 (bddb399,
                         # 2026-07-27): the smallest block RMS (int16 units) the firmware
                         # ever counts as a transient. Not derived from archive records.
PE_SPAN_MOTION = 60      # R1. MOTIONPERCEPT_MOVING_MG, MotionPercept.h:209: |a| - 1 g above
                         # which a sample counts as moving. Value from published figures
                         # (tremor 20-40 mg, stride hundreds); a later 48-window check did
                         # not change it. Shared by the K10 (scaled to 1000 mg at rest).
PE_SPAN_LINK = 90        # R2. LinkPercept.h:35-37, RSSI clamped to [-100, -10] dBm. The R1
                         # candidate PERCEPTLEARN_RSSI_BAND 6 is EXCLUDED: it is the p90 of
                         # consecutive-window |delta rssi_med| on
                         # master/preflash-2026-08-02/cardputer_ttdb.md, i.e. PW-1's own link
                         # residual measured on the archive.
# entity: unchanged (Jaccard distance x 255, no span)

# Open question 6, per channel (acoustic, motion, link)
SATURATED_AT = 247       # median pi >= 255 - prec_write_delta (8): stage 3 could not tell it
                         # from the ceiling by its own rewrite rule
DISTINCT_BY = 24         # two channels' medians "distinguishable" if they differ by more
                         # than this (= PW-1 STAB_TOL); descriptive only
