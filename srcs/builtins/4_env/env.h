#ifndef ENV_H
# define ENV_H

# include "minishell.h"

typedef struct s_env
{
	char			*type;
	char			*data;
	struct s_env	*next;
}	t_env;

/* ===== PUBLIC API ===== */

/* 1_env_insert.c */
t_env	*create_node(char *env_var, int version);

/* 2_env_operations.c */
int		find_envtype(t_env *head, char *name);
int		ft_getenv(t_env *head, char *name, char **result);
void	ft_env(t_env *head, int version);
int		find_exp_spot(t_env *exp, char *name);
void	ft_insertnode(t_env **exp, int steps, char *type, char *data);

/* 3_env_utils.c */
t_env	*safe_env(char **envp, int version);

/* 4_linked_list_utils.c */
void	ft_envadd_back_minus_one(t_env **lst, t_env *new);
void	ft_envadd_back(t_env **lst, t_env *new);
t_env	*ft_envlast(t_env *lst);

/* 5_memory_management.c */
void	free_node(t_env *node);
void	free_env_exp_all(t_env_exp *env_exp);
void	free_ast_helper(t_ast_helper *ast_helper);
void	delete_node(t_env **head, int steps);

/* ===== INTERNAL HELPERS ===== */

/* 1_env_insert.c */
char	*allocate_memory(char *env_var, int start, int end);
t_env	*ft_envnew(void);
void	insert_at_head(t_env **exp, t_env *new_node);
void	insert_at_position(t_env **exp, int steps, t_env *new_node);

/* 3_env_utils.c */
t_env	*initialize_node(char *env_var, int j, int k);
t_env	*create_node_helper(char *env_var, int *j, int *k, int version);

/* 4_linked_list_utils.c */
void	ft_envadd_front(t_env **lst, t_env *new);
t_env	*ft_envlast_minus_one(t_env *lst);

/* 5_memory_management.c */
void	free_env_exp(t_env *head);

#endif
