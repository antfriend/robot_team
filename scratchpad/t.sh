#!/usr/bin/env bash
# RETIRED 2026-09-30 (ACT-III.md Phase B5). Superseded by tests/run-all.
#
# This runner covered 11 of the 16 native tests and no Python suite, and its per-target
# source lists went stale twice — `perceptlearn` had been failing to LINK since the sid
# work landed 2026-08-09 while still printing its old success line. tests/run-all covers
# all 16 native targets plus all 16 `*_py.py` suites plus check_makefile.py, deletes
# binaries before building, and fails on zero targets.
#
# Kept as a shim rather than deleted, because runbooks and log entries name it.
exec bash "$(dirname "$0")/../tests/run-all" "$@"
