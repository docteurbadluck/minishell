#include "orchestrator.h"
#include "../signal_and_input/signal/signal.h"
#include "../signal_and_input/input/input.h"
#include "../signal_and_input/heredoc/heredoc.h"

int	init_orchestrator(t_orchestrator *orch, char *argv0, char **envp)
{
	orch->way_to_tmp = path_to_tmp(argv0);
	if (prepare_env_exp(&orch->env_exp, envp) != 0)
		return (ft_printf("error\n"), 1);
	set_state(orch, STATE_MENU);
	return (0);
}

void	set_state(t_orchestrator *orch, t_shell_state new_state)
{
	orch->state = new_state;
	if (new_state == STATE_MENU)
		set_menu_signals();
	else if (new_state == STATE_HEREDOC)
		set_heredoc_signals();
	else if (new_state == STATE_EXECUTING)
		set_ignore_signals();
}

int	process_heredoc(t_orchestrator *orch, t_free *free_all)
{
	int	n;

	n = count_heredoc(free_all->new_array);
	if (n == 0)
		return (0);
	set_state(orch, STATE_HEREDOC);
	if (create_heredoc_files(n, free_all->new_array, orch->way_to_tmp) == -1
		|| g_cancel_heredoc)
	{
		g_cancel_heredoc = 0;
		set_state(orch, STATE_MENU);
		cleanup(free_all);
		return (-1);
	}
	return (0);
}

void	execute_iteration(t_orchestrator *orch, t_free *free_all)
{
	set_state(orch, STATE_EXECUTING);
	if (create_ast_helper(&free_all->ast_helper) == 0)
		run_ast_pipeline(free_all->tree,
			free_all->env_exp, free_all->ast_helper, free_all);
	set_state(orch, STATE_MENU);
	cleanup(free_all);
}
