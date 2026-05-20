#ifndef FREE_H
# define FREE_H

# include "minishell.h"

/* ===== PUBLIC API ===== */

/* 1_free_new_array.c */
void	free_array(t_parsed_command **array);
void	free_new_array(t_parsed_command **new_array);

/* ===== INTERNAL HELPERS ===== */

/* 1_free_new_array.c */
void	free_arguments(char **arguments);
void	free_redirections(char **redirection_array);
void	free_parsed_command(t_parsed_command *command);

/* 2_free_new_array_utils.c */
void	free_iofiles(t_parsed_command *command);

#endif
