#ifndef ORCHESTRATOR_H
# define ORCHESTRATOR_H

# include "minishell.h"
# include "../execution/execution.h"

typedef enum e_shell_state
{
	STATE_MENU,
	STATE_HEREDOC,
	STATE_EXECUTING,
}	t_shell_state;

typedef struct s_orchestrator
{
	t_shell_state	state;
	t_env_exp		*env_exp;
	char			*way_to_tmp;
}	t_orchestrator;

/* ===== PUBLIC API ===== */

int		run_shell(char *argv0, char **envp);

/* ===== INTERNAL HELPERS ===== */

/* 1_orchestrator.c */
int					shell_loop_body(t_orchestrator *orch);
int					get_validated_input(char **input);
t_parsed_command	*parse_input(char *input);

/* 2_orchestrator_utils.c */
int		init_orchestrator(t_orchestrator *orch, char *argv0, char **envp);
void	set_state(t_orchestrator *orch, t_shell_state new_state);
int		process_heredoc(t_orchestrator *orch, t_free *free_all);
void	execute_iteration(t_orchestrator *orch, t_free *free_all);
void	handle_input(t_orchestrator *orch, t_free *free_all, char *input);

#endif
