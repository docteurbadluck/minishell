#include "unity.h"
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>

void	setUp(void) {}
void	tearDown(void) {}

void	test_signals(void)
{
	int pipefd[2];
	pipe(pipefd);
	char *argv[] = {"/home/docteurbadluck/Desktop/minishell/minishell", NULL};

	int pid = fork();
	if (pid == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[1]);
		execve("../minishell", argv, __environ);
		exit(1);
	}
	close(pipefd[0]);
	write(pipefd[1], "sleep 5\n", 8);
	int status;
	waitpid(pid, &status, 0);
	TEST_ASSERT_TRUE(WIFSIGNALED(status) || WIFEXITED(status));

	sleep(1);
	close(pipefd[1]);

}

int	main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_signals);
	return (UNITY_END());
}
