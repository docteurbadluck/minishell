#ifndef INPUT_H
# define INPUT_H

# include "minishell.h"
# include "../../execution/execution.h"

/* ===== PUBLIC API ===== */

/* 2_input_count_heredoc.c */
int		count_heredoc(t_parsed_command *ptr);

/* 3_input_util.c */
t_free	init_free_all(t_env_exp *env_exp);
char	*get_input(void);

#endif
