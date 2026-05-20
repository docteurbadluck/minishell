CC = cc
BUILD_DIR = build
TEST_SRC = $(wildcard test_*.c)
TEST_BINS = $(TEST_SRC:test_%.c=$(BUILD_DIR)/run_%)

TESTER_DIR = ../minishell_tester
TESTER_URL = https://github.com/LucasKuhn/minishell_tester.git

$(BUILD_DIR)/run_%: test_%.c unity.c
	@mkdir -p $(BUILD_DIR)
	$(CC) -g -I../includes -I. unity.c $< -o $@ -L../libft- -lft

test: $(TEST_BINS)
	@for t in $(TEST_BINS); do echo "\n--- $$t ---"; ./$$t; done

tester-install:
	@if [ ! -d "$(TESTER_DIR)" ]; then \
		git clone $(TESTER_URL) $(TESTER_DIR); \
	else \
		echo "$(TESTER_DIR) already exists, skipping clone."; \
	fi

tester: tester-install
	@make -C .. > /dev/null 2>&1
	@cd $(TESTER_DIR) && bash tester

clean:
	rm -f $(TEST_BINS)

tclean-tester:
	rm -rf $(TESTER_DIR)

SIGNALS_DIR = signals
PROJECT_ROOT = $(shell cd .. && pwd)

check-deps-signals:
	@which expect > /dev/null 2>&1 || (echo "installing expect..." && sudo apt-get install -y expect)

check-deps-signals-view: check-deps-signals
	@which tmux > /dev/null 2>&1 || (echo "installing tmux..." && sudo apt-get install -y tmux)

signals: check-deps-signals
	@make -C .. > /dev/null 2>&1
	@bash $(SIGNALS_DIR)/run_signal_tests.sh $(PROJECT_ROOT)

signals-view: check-deps-signals-view
	@make -C .. > /dev/null 2>&1
	@tmux kill-session -t minishell_signals 2>/dev/null; \
	tmux new-session -d -s minishell_signals -x 220 -y 50; \
	tmux send-keys -t minishell_signals \
		"expect $(PROJECT_ROOT)/test/signals/test_signals.expect $(PROJECT_ROOT)/minishell" Enter; \
	tmux attach -t minishell_signals

.PHONY: test tester-install tester clean tclean-tester check-deps-signals check-deps-signals-view signals signals-view
