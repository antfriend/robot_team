"""PW-3 pre-registered constants (TTDB-RFC-0011 v0.1.5, section 8, section 6.3).

Committed BEFORE any replay code exists. Do not change after seeing data.
Protocol prose: PW3-PROTOCOL.md (same directory). Reuses pw2_constants for the rule values.
"""
# RFC section 8 PW-3 thresholds (already pre-committed there)
DISAGREE_MAX = 0.05          # KILL if more than 5 % of beliefs disagree
AIRTIME_FALL_MIN = 0.30      # KILL if airtime falls by less than 30 %
MIN_SERIES = 20              # fewer beliefs than this -> INCONCLUSIVE

# Gate, RFC 6.3 / 9.1
THETA_TX = 96                # = theta_ign
THETA_TX_DESCRIPTIVE = (64, 96, 128)   # reported only, never used for the verdict

# Frame sizes, firmware/libraries/Toot/src/Toot.h:31-34 (HEADER_LEN, MAX_BODY, HMAC_LEN)
HEADER_LEN = 33
HMAC_LEN = 8
MAX_BODY = 208
SALIENT_PAYLOAD = 12         # RFC 6.3 table
SALIENT_FRAME = HEADER_LEN + SALIENT_PAYLOAD + HMAC_LEN      # 53
# PERCEPT toot: record body bytes, split into frames of at most MAX_BODY, each + HEADER + HMAC.

# Agreement between a gated and an ungated belief body: pe(gated, ungated) < PE_AGREE (48).
