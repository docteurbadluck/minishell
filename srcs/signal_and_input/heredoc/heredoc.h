#ifndef HEREDOC_H
# define HEREDOC_H

# include "minishell.h"

/* ===== PUBLIC API ===== */

int		create_heredoc_files(int nbr_of_heredoc,
			t_parsed_command *array_of_cmd, char *way_to_tmp);
void	unlink_tempo_files(char *way_to_tmp);
char	*path_to_tmp(char *argv0);
void	heredoc_dollar(t_parsed_command *command, t_env_exp *env_exp);

/* ===== INTERNAL HELPERS ===== */

/* 1_heredoc.c */
void	modif_in_struct(t_heredoc_manip *heredoc, int y);
void	transform_heredoc_variable(char *filename, t_env_exp *env_exp);
void	free_heredoc(t_heredoc_manip *heredoc, int nbr_of_heredoc);

/* 2_heredoc_utils.c */
int		alloc_heredoc(int nbr_heredoc, t_heredoc_manip *heredoc);
int		init_eof_and_to_modif(int nbr_heredoc,
			t_parsed_command *array_of_cmd, t_heredoc_manip *heredoc);
void	names_tempo_files(t_heredoc_manip *heredoc, char *way_to_tmp);
void	write_into_temp(t_heredoc_manip *heredoc, int y);

#endif
