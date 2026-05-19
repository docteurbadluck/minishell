#!/bin/bash

SESSION="minishell_signals"
LOG="/tmp/minishell_test_results.log"

tmux kill-session -t $SESSION 2>/dev/null
> $LOG

tmux new-session -d -s $SESSION -x 220 -y 50

# panneau gauche : expect qui pilote minishell, log les résultats
tmux send-keys -t $SESSION "cd /home/docteurbadluck/Desktop/minishell && expect test/test_signals.expect 2>&1 | tee $LOG" Enter

# panneau droit : affiche uniquement les résultats depuis le log
tmux split-window -h -t $SESSION
tmux send-keys -t $SESSION "tail -f $LOG | grep -E '(TEST|✓|✗|DONE)'" Enter

tmux attach -t $SESSION
