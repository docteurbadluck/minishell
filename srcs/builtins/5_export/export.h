#ifndef EXPORT_H
# define EXPORT_H

# include "minishell.h"
# include "../4_env/env.h"

/* ===== PUBLIC API ===== */

/* 1_exp_operations.c */
int		create_exp(t_env_exp *env_exp);
int		ft_export(t_env_exp *env_exp, char **arguments, int version);

/* ===== INTERNAL HELPERS ===== */

/* 1_exp_operations.c */
void	free_str(char **str);
void	replace_data(t_env *head, t_env *new_node);
int		ft_export_execution(t_env_exp *env_exp, char *content, int version);

/* 2_exp_operations_helper.c */
void	handle_existing_node(t_env_exp *env_exp, t_env *new_node);
void	handle_new_node(t_env_exp *env_exp, t_env *new_node);

#endif
