/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   M_signal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:23:59 by tdeliot           #+#    #+#             */
/*   Updated: 2025/04/10 12:12:26 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


// creer une structure signals ctrl C ctrl D  ctrl / 
// creer les masques pour chaque etat. et les stocker dans un tableau de la structure. 
// creer une fonction qui permet de passer proprement d un etat a un autre et d ecouter.



void handler_C_menu(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

// show ^/ i don't know how to take it off.
void handler_Term_menu(int signum)
{
	if (signum)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void handler_C_exec(int signum)
{
	if (signum)
	{}
	printf("ctrl C received\n");
	printf("( print ^C ,close executing program )\n");
}


void handler_Term_exec(int signum)
{
	if (signum)
	{}
	printf("ctrl \\ received\n");
	printf("\\^ Quit (core dumped) is written. quit properlly. ");
}

void handler_C_heredoc(int signum)
{
    if (signum == SIGINT) {
        cancel_heredoc = 1;  // Set flag to indicate heredoc should be canceled
        rl_on_new_line();    // Move to a new line
        rl_redisplay();      // Redisplay the prompt
        printf("\nHeredoc canceled by Ctrl+C\n");
    }
}

void handler_Term_heredoc(int signum)
{
	if (signum)
	{}	
	if (signum)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}





void listen_signal(t_signals *signals)
{
	sigaction(SIGINT, &signals->sa_C, NULL);
	sigaction(SIGQUIT, &signals->sa_Term, NULL);
}

void init_handlers(t_signal_manager *signals_man)
{
	memset(&signals_man->signals_menu, 0, sizeof(signals_man->signals_menu));
    memset(&signals_man->signals_exec, 0, sizeof(signals_man->signals_exec));
    memset(&signals_man->signals_heredoc, 0, sizeof(signals_man->signals_heredoc));

	signals_man->signals_menu.sa_C.sa_handler = &handler_C_menu;
	signals_man->signals_menu.sa_Term.sa_handler = &handler_Term_menu;
	signals_man->signals_menu.sa_Term.sa_flags = SA_RESTART;

	signals_man->signals_exec.sa_C.sa_handler = &handler_C_exec;
	signals_man->signals_exec.sa_Term.sa_handler = &handler_Term_exec;

	signals_man->signals_heredoc.sa_C.sa_handler = &handler_C_heredoc;
	signals_man->signals_heredoc.sa_Term.sa_handler = &handler_Term_heredoc;
}

void init_mask(t_signal_manager *signals_man)
{
	// Menu mode
	sigemptyset(&signals_man->signals_menu.sa_C.sa_mask);
	sigaddset(&signals_man->signals_menu.sa_C.sa_mask, SIGINT);
	sigaddset(&signals_man->signals_menu.sa_C.sa_mask, SIGQUIT);

	sigemptyset(&signals_man->signals_menu.sa_Term.sa_mask);
	sigaddset(&signals_man->signals_menu.sa_Term.sa_mask, SIGINT);
	sigaddset(&signals_man->signals_menu.sa_Term.sa_mask, SIGQUIT);

	// Same for heredoc
	sigemptyset(&signals_man->signals_heredoc.sa_C.sa_mask);
	sigaddset(&signals_man->signals_heredoc.sa_C.sa_mask, SIGINT);
	sigaddset(&signals_man->signals_heredoc.sa_C.sa_mask, SIGQUIT);

	sigemptyset(&signals_man->signals_heredoc.sa_Term.sa_mask);
	sigaddset(&signals_man->signals_heredoc.sa_Term.sa_mask, SIGINT);
	sigaddset(&signals_man->signals_heredoc.sa_Term.sa_mask, SIGQUIT);

	// Same for exec
	sigemptyset(&signals_man->signals_exec.sa_C.sa_mask);
	sigaddset(&signals_man->signals_exec.sa_C.sa_mask, SIGINT);
	sigaddset(&signals_man->signals_exec.sa_C.sa_mask, SIGQUIT);

	sigemptyset(&signals_man->signals_exec.sa_Term.sa_mask);
	sigaddset(&signals_man->signals_exec.sa_Term.sa_mask, SIGINT);
	sigaddset(&signals_man->signals_exec.sa_Term.sa_mask, SIGQUIT);
}




/*
int main(void)
{
    printf("PID: %d\n", getpid());
    t_signal_manager sa_manager;

    init_handlers(&sa_manager);
    init_mask(&sa_manager);

    // Start with menu mode
    listen_signal(&sa_manager.signals_menu);

    return 0;
}

*/

