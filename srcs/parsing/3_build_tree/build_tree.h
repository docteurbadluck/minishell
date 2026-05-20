#ifndef BUILD_TREE_H
# define BUILD_TREE_H

# include "minishell.h"

typedef struct s_ast_node {
	t_parsed_command	*command;
	int					logical_operator;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

/* ===== PUBLIC API ===== */

t_ast_node	*from_group_to_tree(t_parsed_command **new_array);
void		set_associativity(t_parsed_command *new_array);
void		free_tree(t_ast_node *node);

/* ===== INTERNAL HELPERS ===== */

/* 1_from_group_to_polish_reverse.c */
t_list		*from_group_to_polish_reverse(t_parsed_command *new_array);
int			process_open_parenthesis(t_parsed_command *array, int *i, t_list **stack);

/* 2_to_polish_reverse_utils.c */
int			check_priority(t_parsed_command *new_array, int i, t_list *operator_stack);
void		send_element(t_list **operator_stack, t_list **output_list);
void		print_list(t_list *output_list);
void		free_list(t_list *output_list);
void		print_shunting_yard(t_list *output_list, t_list *operator_stack);

/* 3_from_polish_to_tree.c */
t_ast_node	*from_polish_to_tree(t_list *output_list);
void		init_logical_operator(t_list *input_of_s_ast_node);
t_list		*transform_parsed_in_ast(t_list *output_list);
void		pop_last(t_list **output_list);
void		process_operator_tree(t_ast_node *ptr_ast, t_list **output_stack);

/* 4_from_text_to_tree.c */
t_ast_node	*from_text_to_tree(char *str, t_parsed_command **new_array);

/* 5_print_tree.c */
void		print_tree(t_ast_node *node, int depth);
void		print_indentation(int depth);
void		print_arguments(char **arguments);
void		print_redirections(char **redirection_array);
void		print_iofiles(t_parsed_command *command);

#endif
