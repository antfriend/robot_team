#!/usr/bin/env bash
# item5_check.sh <node> <port>: pull, then one line per bar: grammar, same, split (+ who).
N=$1; P=$2; F=scratchpad/${N}_item5_pull.md
python orchestrator/fleet.py pull --port "$P" --node "$N" --out "$F" --timeout 60 2>&1 | tail -1
awk '/^\*\*BAR\*\*/{bar=$3} /^\*\*GRAMMAR\*\*/{printf "%s %s %s %s", bar, $2, $3, $4; nl=1} /^\*\*SPLIT\*\*/{printf "  <- %s %s", $2, $3} /^\*\*BAR\*\*/ && nl {print ""; nl=0} END{print ""}' "$F" | grep -v "^$" | grep "bar:" | tail -8
