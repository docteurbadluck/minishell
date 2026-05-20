#ifndef WILDCARD_H
# define WILDCARD_H

# include "minishell.h"

/* ===== PUBLIC API ===== */

int		set_wildcard(t_parsed_command *grouped_array);

/* ===== INTERNAL HELPERS ===== */

/* 1_wildcard_manager.c */
char	*wildcard_manager(char *input);
char	*wildcard_generator(char *input);
char	*handle_wildcard_expansion(char *input, int i);
char	**cut_input_wildcard(char *input, int i);
char	*get_filtered_wildcard_matches(char *pattern, char **names);

/* 2_wildcard_util.c */
int		compte_name(void);
char	**name_array_generator(void);
int		check_current_dir_input(char *input);
int		matching_name(char *pattern, char *name, int first_call);
char	*assembling_wild(char *variable, char **array_of_str);

/* 3_set_wildcard.c */
t_list	*find_wildcars(t_parsed_command *grouped_array);
void	find_wildcard_in_arg(t_parsed_command *grouped_array, int i, t_list **list_of_tracker);
void	find_wildcard_in_redirection(t_parsed_command *grouped_array, int i, t_list **list_of_tracker);
void	process_wildcard_tracker(t_tracker *ptr_tracker, int *flag);

/* 4_set_wildcard_utils.c */
void	copy_matched_names(t_tracker *ptr_tracker, t_list **list_of_str, int *z);
void	copy_after_wildcard(t_tracker *ptr_tracker, t_list **list_of_str, int *i);
void	free_old_arguments(t_tracker *ptr_tracker);
void	replace_with_new_arguments(t_tracker *ptr_tracker, t_list *list_of_str);
void	modify_arg(t_tracker *ptr_tracker);

/* 5_free.c */
void	free_wildcard_list(void *content);
void	free_str_list(void *content);
void	copy_before_wildcard(t_tracker *ptr_tracker, t_list **list_of_str, int *i);
char	*prepare_input_for_wildcard(char *input, char **pwd);

#endif
