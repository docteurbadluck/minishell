#ifndef SIGNAL_H
# define SIGNAL_H

# include "minishell.h"

/* ===== PUBLIC API ===== */

void	set_default_signals(void);
void	set_ignore_signals(void);
void	set_menu_signals(void);
void	set_heredoc_signals(void);

/* ===== INTERNAL HELPERS ===== */

/* 2_signal_handler.c */
void	handler_menu(int signum);
void	soft_quit_handler(int signum);

#endif
