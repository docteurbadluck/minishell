/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   M_signal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:23:59 by tdeliot           #+#    #+#             */
/*   Updated: 2025/04/26 10:49:59 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_default_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	set_ignore_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	set_menu_signals(void)
{
	struct sigaction	sa_menu;

	sa_menu.sa_handler = &handler_menu;
	sa_menu.sa_flags = SA_RESTART;
	sigemptyset(&sa_menu.sa_mask);
	sigaction(SIGINT, &sa_menu, NULL);
	sigaction(SIGQUIT, &sa_menu, NULL);
}

void	set_heredoc_signals(void)
{
	struct sigaction	sa_ign;
	struct sigaction	sa_soft_quit;

	sa_ign.sa_handler = SIG_IGN;
	sa_ign.sa_flags = 0;
	sigemptyset(&sa_ign.sa_mask);
	sa_soft_quit.sa_handler = &soft_quit_handler;
	sa_soft_quit.sa_flags = 0;
	sigemptyset(&sa_soft_quit.sa_mask);
	sigaction(SIGQUIT, &sa_ign, NULL);
	sigaction(SIGINT, &sa_soft_quit, NULL);
}

/*
int main()
{
	struct sigaction sa_term_orig;
	struct sigaction sa_term_ign;
	struct sigaction sa_term_menu;
	int status;
	sigemptyset(&sa_term_menu.sa_mask);
	sigaddset(&sa_term_menu.sa_mask, SIGINT);
	sigaddset(&sa_term_menu.sa_mask, SIGTERM);

	sa_term_menu.sa_flags = 0;
	sa_term_menu.sa_handler = &handler_menu;

	sigemptyset(&sa_term_orig.sa_mask);
	sa_term_orig.sa_flags = 0;
	sa_term_orig.sa_handler = SIG_DFL;
	
	sa_term_ign.sa_flags = 0;
	sigemptyset(&sa_term_ign.sa_mask);
	sa_term_ign.sa_handler = SIG_IGN;


	sigaction(SIGQUIT, &sa_term_menu, NULL);
	sigaction(SIGINT, &sa_term_menu, NULL);

	
	printf("first read : \n");
	char *str = get_next_line(0);
	printf("readline :%s", str);
		//avant exec;
	sigaction(SIGQUIT, &sa_term_ign, &sa_term_menu);
	sigaction(SIGINT, &sa_term_ign, &sa_term_menu);


	int pid = fork();
	if (!pid)
	{
		sigaction(SIGQUIT, &sa_term_orig, NULL);
		sigaction(SIGINT, &sa_term_orig, NULL);


		printf("sleep\n");
		sleep(3);
		exit(0);
	}
	waitpid(pid, &status, 0);

	if (WIFEXITED(status))
	{
		printf("status exit with : %d\n", WEXITSTATUS(status));
	}
	if (WIFSIGNALED(status))
	{
		printf("process finished by signal numbr : %d\n", WTERMSIG(status));
	}
	sigaction(SIGQUIT, &sa_term_menu, &sa_term_ign);
	sigaction(SIGINT, &sa_term_menu, &sa_term_ign);

	printf("return to normal : \n");
	return 0;
	}*/