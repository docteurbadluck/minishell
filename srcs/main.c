#include "minishell.h"
#include "orchestrator/orchestrator.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	return (run_shell(argv[0], envp));
}
