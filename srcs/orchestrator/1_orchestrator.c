#include "orchestrator.h"
#include "../signal_and_input/input/input.h"
#include "../signal_and_input/heredoc/heredoc.h"
#include "../parsing/2_group_up/group_up.h"
#include "../builtins/4_env/env.h"

int	get_validated_input(char **input)
{
	*input = get_input();
	if (!(*input))
		return (ft_printf("exit\n"), -1);
	if (ft_strchr(*input, '\n'))
		return (ft_printf("error multiple line\n"), free(*input), 1);
	return (0);
}

t_parsed_command	*parse_input(char *input)
{
	t_parsed_command	*result;

	add_history(input);
	result = from_input_to_group(input);
	free(input);
	return (result);
}

void	handle_input(t_orchestrator *orch, t_free *free_all, char *input)
{
	free_all->new_array = parse_input(input);
	if (free_all->new_array && process_heredoc(orch, free_all) == 0)
	{
		free_all->tree = from_group_to_tree(&free_all->new_array);
		execute_iteration(orch, free_all);
	}
}

int	shell_loop_body(t_orchestrator *orch)
{
	t_free	free_all;
	char	*input;
	int		res;

	unlink_tempo_files(orch->way_to_tmp);
	res = get_validated_input(&input);
	if (res == -1)
		return (-1);
	if (res)
		return (0);
	free_all = init_free_all(orch->env_exp);
	if (ft_strlen(input))
		handle_input(orch, &free_all, input);
	else
		free(input);
	return (0);
}

int	run_shell(char *argv0, char **envp)
{
	t_orchestrator	orch;

	if (init_orchestrator(&orch, argv0, envp))
		return (1);
	while (shell_loop_body(&orch) == 0)
		;
	free_env_exp_all(orch.env_exp);
	free(orch.way_to_tmp);
	rl_clear_history();
	return (0);
}
