#ifndef VARIABLE_H
# define VARIABLE_H

# include "minishell.h"

/* ===== PUBLIC API ===== */

char	*variable_manager(char *input, t_env_exp *env_exp);

/* ===== INTERNAL HELPERS ===== */

/* 1_variable_manager.c */
int		is_space_or_doll(char c);
int		lenght_variable(char *str);
char	**cut_input(char *input, int i);
char	*assembling(char *variable, char **array_of_str);

/* 2_variable_manager_helper.c */
char	*handle_status_variable(char **array_of_str, t_env_exp *env_exp);
char	*handle_env_variable(char **array_of_str, t_env_exp *env_exp);
char	*process_final_result(char *final_result, t_env_exp *env_exp);
char	*handle_variable_expansion(char *input, int i, t_env_exp *env_exp);
int		should_expand_variable(char *input, int i, int flag);

#endif
