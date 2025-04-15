/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   M_signal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:23:59 by tdeliot           #+#    #+#             */
/*   Updated: 2025/04/15 11:07:02 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


// creer une structure signals ctrl C ctrl D  ctrl / 
// creer les masques pour chaque etat. et les stocker dans un tableau de la structure. 
// creer une fonction qui permet de passer proprement d un etat a un autre et d ecouter.


volatile sig_atomic_t cancel_heredoc = 0;  // Initializing the variable

void handler_menu(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signum == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	soft_quit_handler(int signum)
{
	if (signum == SIGINT)
	{
		cancel_heredoc = 1;
		printf("should quit writing\n");
	}
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