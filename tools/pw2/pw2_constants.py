"""PW-2 / PW-4 pre-registered constants (TTDB-RFC-0011 v0.1.4, section 8).

Committed BEFORE any replay code exists or reads master/. Do not change after seeing data.
Protocol prose: PW2-PW4-PROTOCOL.md (same directory).
"""

# --- RFC section 9.1 reference values ------------------------------------------------
PREC_DEFAULT = 128
PI_ALPHA = 4
PI_SCALE = 8192
K_REVISE = 160
PE_AGREE = 48
THETA_IGN = 96
THETA_OFF = 64
WORKSPACE_W = 7
WORKSPACE_HALF_LIFE_MS = 120000

# --- Fixed-step baseline (what section 3.4 replaces) ---------------------------------
# TTDB-RFC-0005 section 3.4 leaves CONF_INCREMENT/DECREMENT symbolic. The fleet's values are
# firmware/libraries/PerceptLearn/src/PerceptLearn.h:386-390 (MET 2, VIOLATED 16).
CONF_INCREMENT = 2
CONF_DECREMENT = 16
CONF_BASELINE = 128          # PERCEPTLEARN_BASELINE_CONF
# Baseline rule (RFC-0005 section 3.4 loop): pe >= PE_AGREE -> body = observed, rev += 1,
# conf = max(conf - CONF_DECREMENT, 0); else conf = min(conf + CONF_INCREMENT, 255).

# --- Online precision for the replay --------------------------------------------------
# Each channel's pi is folded online per RFC 4.3 (same fold as PW-1). A channel uses
# PREC_DEFAULT until it has MIN_RESIDUALS residuals, then the folded value.
MIN_RESIDUALS = 30

# --- PW-2 design ----------------------------------------------------------------------
PW2_CHANNELS = ('acoustic', 'motion', 'link')   # scalar forms only; entity (set) excluded
PW2_INJECT_AT = 60            # noisy twin starts at this window index of each series
PW2_HIGH_CONF = 192           # cohort: belief conf >= this at INJECT_AT under BOTH rules
PW2_NOISE_SEED = 0x5EED0011   # xorshift32 seed, per (node, channel) stream: seed ^ fnv1a(name)
PW2_NOISE_FRACTION_NUM = 3    # noise magnitude uniform in [0, span * 3 / 5), random sign,
PW2_NOISE_FRACTION_DEN = 5    # observation clamped to the channel's valid range
# Verdict (flips = body rewrites counted as rev increments after INJECT_AT, summed over cohort):
PW2_PASS_RATIO = 0.5          # PASS if flips_gain <= 0.5 * flips_fixed
                              # FALSIFIED if flips_gain >= flips_fixed (RFC section 8)
PW2_MIN_COHORT = 5            # fewer cohort beliefs than this -> INCONCLUSIVE

# --- PW-4 design ----------------------------------------------------------------------
# Every replay (PW-2 both rules, plus a plain archive replay) is run twice: workspace
# disabled/empty vs enabled. Verdict key = SHA-256 of the final belief store (sorted).
# PASS iff every pair is byte-identical. FALSIFIED on any difference. A canary variant that
# deliberately reads the workspace in the update path MUST be detected as different, else
# the test is vacuous and the verdict is INCONCLUSIVE.
PW4_CANARY_REQUIRED = True
