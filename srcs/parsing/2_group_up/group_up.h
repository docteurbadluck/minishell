#ifndef GROUP_UP_H
# define GROUP_UP_H

# include "minishell.h"

typedef struct s_redir_state
{
	t_iofile	*infiles;
	t_iofile	*outfiles;
	int			x;
	int			z;
}	t_redir_state;

/* ===== PUBLIC API ===== */

t_parsed_command	*from_input_to_group(char *input);

/* ===== INTERNAL HELPERS ===== */

/* 1_set_logic_op.c */
int		set_logic_op(t_parsed_command *array);
int		arrow_check(t_parsed_command *array, int y);
int		parenthese_check(t_parsed_command *array, int y);
int		operator_check(t_parsed_command *array, int y);
void	word_value(t_parsed_command *array, int y);

/* 2_set_groupid_control_logic.c */
int		set_groupid_control_logic(t_parsed_command *array);
void	attribute_groupid(t_parsed_command *array);
int		control_logic(t_parsed_command *array);
int		control_parentheses(t_parsed_command *array);

/* 3_set_groupid_control_logic_utils.c */
void	give_value(t_parsed_command *array, int i);
int		control_border_logic(t_parsed_command *array);

/* 4_group_up.c */
t_parsed_command	*group_up(t_parsed_command **array);
int		set_up_arg(t_parsed_command *array);
void	create_new_array(t_parsed_command *array, t_parsed_command *new);

/* 5_group_up_utils.c */
int		allocate_and_fill_arguments(t_parsed_command *array, int save_pos, int count_arg, int *i);
void	fill_redirections(t_parsed_command *array, int save_pos, int *i, int *z);
void	fill_arguments(t_parsed_command *array, int save_pos, int *i, int *y);

/* 6_group_up_count.c */
int		count_new_array(t_parsed_command *array);
int		count_arguments_and_move(t_parsed_command *array, int *i);

/* 7_from_input_to_group.c */
void				set_associativity(t_parsed_command *new_array);
t_parsed_command	*from_new_to_group_up(char *developped_input);

/* 8_set_outfiles.c */
int		set_outfiles(t_parsed_command *grouped_array);

/* 9_set_outfiles_utils.c */
int		control_operator(char *redirection);
int		control_redirection_logique(t_parsed_command *grouped_array);
int		count_files_names(char **redirection_array);
int		which_symbole(char *redirection);

/* 10_process_filename.c */
char	*process_redirection_filename(const char *input);
char	*extract_valid_filename(const char *input, char quote_type);

#endif
