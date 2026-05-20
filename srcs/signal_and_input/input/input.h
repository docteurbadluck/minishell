#ifndef INPUT_H
# define INPUT_H

# include "minishell.h"

/* ===== PUBLIC API ===== */

int		read_input(char *argv0, char **envp);

/* ===== INTERNAL HELPERS ===== */

/* 1_input.c */
void	execute_input(t_free *free_all);
int		process_input(char *argv0, t_free *free_all);
int		handle_single_input(char *way_to_tmp, t_free *free_all);

/* 2_input_count_heredoc.c */
int		count_heredoc(t_parsed_command *ptr);

/* 3_input_util.c */
t_free	init_free_all(void);
char	*get_input(void);

#endif
