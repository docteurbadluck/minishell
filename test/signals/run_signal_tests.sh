#!/bin/bash

PROJECT_ROOT="${1:-$(cd "$(dirname "$0")/../.." && pwd)}"
MINISHELL="$PROJECT_ROOT/minishell"
EXPECT_SCRIPT="$PROJECT_ROOT/test/signals/test_signals.expect"

OUTPUT=$(expect "$EXPECT_SCRIPT" "$MINISHELL" 2>&1)
FAILURES=$(echo "$OUTPUT" | grep '✗')

if [ -n "$FAILURES" ]; then
    echo "$FAILURES"
    exit 1
fi

echo "Signals & heredoc Tested Successfully"
exit 0
