#!/bin/bash

RED='\033[0;31m'
GRN='\033[0;32m'
NC='\033[0m'

pass() { echo -e "${GRN}✓ $1${NC}"; }
fail() { echo -e "${RED}✗ $1 FAILED:${NC}"; cat "$2"; }

# Build first — everything depends on it
make > /tmp/check_build.log 2>&1
if [ $? -ne 0 ]; then
    fail "Build" /tmp/check_build.log
    exit 1
fi
pass "Build"

echo "Running tests..."

# Tester
make tester > /tmp/check_tester.log 2>&1
STATUS_TESTER=$?

# Signals run after — expect is sensitive to concurrent minishell processes
make signals > /tmp/check_signals.log 2>&1
STATUS_SIGNALS=$?

echo ""
FAILED=0

[ $STATUS_TESTER  -eq 0 ] && pass "Tester"       || { fail "Tester"       /tmp/check_tester.log;  FAILED=1; }
[ $STATUS_SIGNALS -eq 0 ] && pass "Signal tests" || { fail "Signal tests" /tmp/check_signals.log; FAILED=1; }

echo ""
[ $FAILED -eq 0 ] && echo -e "${GRN}All tests passed${NC}" || echo -e "${RED}Some tests failed${NC}"
exit $FAILED
