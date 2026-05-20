#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include "4_env/env.h"
# include "5_export/export.h"

/* ===== PUBLIC API ===== */

/* 1_ft_echo.c */
int		ft_echo(char **str);

/* 2_ft_cd.c */
int		ft_cd(t_env_exp *env_exp, char **str, int version);

/* 3_ft_pwd.c */
int		ft_pwd(void);

/* 5_export/1_exp_operations.c */
int		ft_export(t_env_exp *env_exp, char **arguments, int version);

/* 6_ft_unset.c */
int		ft_unset(t_env_exp *env_exp, char *content);

/* 7_ft_exit.c */
void	ft_exit(char **args, int version);

#endif
