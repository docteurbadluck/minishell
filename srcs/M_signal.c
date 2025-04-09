/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   M_signal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:23:59 by tdeliot           #+#    #+#             */
/*   Updated: 2025/04/09 10:10:03 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


// creer une structure signals ctrl C ctrl D  ctrl / 
// creer les masques pour chaque etat. et les stocker dans un tableau de la structure. 
// creer une fonction qui permet de passer proprement d un etat a un autre et d ecouter.



void handler_C_menu(int signum)
{
	printf("ctrl C received\n");
	printf("( print ^C should change line)\n");

}

void handler_D_menu(int signum)
{
	printf("ctrl D received\n");
	printf("modif line to exit and execute\n");

}

void handler_Term_menu(int signum)
{
	printf("ctrl received\n");
	printf("should be ignored\n");
}

void handler_C_exec(int signum)
{
	printf("ctrl C received\n");
	printf("( print ^C ,close executing program )\n");
}

void handler_D_exec(int signum)
{
	printf("ctrl D received\n");
	printf("should be ignored\n");

}

void handler_Term_exec(int signum)
{
	printf("ctrl \\ received\n");
	printf("\\^ Quit (core dumped) is written. quit properlly. ");
}

void handler_C_heredoc(int signum)
{
	printf("ctrl C received\n");
	printf("( close writing executing program )\n");
}

void handler_D_heredoc(int signum)
{
	printf("ctrl D received\n");
	printf("auto complete\n");
	// or quit ? 

}

void handler_Term_heredoc(int signum)
{
	printf("ctrl \\ received\n");
	printf(" should be ignored");
}




typedef struct s_signals
{
	struct sigaction	sa_C;	//treat ctrl c
	struct sigaction	sa_D;	//treat ctrl d
	struct sigaction	sa_Term; //treat ctrl 
	void (*handler_C)(int);
	void (*handler_D)(int);
	void (*handler_Term)(int);
	int	actual_status;
}	t_signals;


typedef struct s_signal_manager
{
	t_signals signals_menu;
	t_signals	signals_heredoc;
	t_signals	signals_exec;
	int actual_mode;
}	t_signal_manager;




void listen_signal(t_signals *signals)
{
	sigaction(SIGINT, &signals->sa_C, NULL);
	sigaction(SIGQUIT, &signals->sa_D, NULL);
	sigaction(SIGTSTP, &signals->sa_Term, NULL);
}

void init_handlers(t_signal_manager *signals_man)
{
	signals_man->signals_menu.sa_C.sa_handler = &handler_C_menu;
	signals_man->signals_menu.sa_D.sa_handler = &handler_D_menu;
	signals_man->signals_menu.sa_Term.sa_handler = &handler_Term_menu;
/*
	signals_man->signals_exec.sa_C.sa_handler = &handler_C_exec;
	signals_man->signals_exec.sa_D.sa_handler = &handler_D_exec;
	signals_man->signals_exec.sa_Term.sa_handler = &handler_Term_exec;

	signals_man->signals_heredoc.sa_C.sa_handler = &handler_C_heredoc;
	signals_man->signals_heredoc.sa_D.sa_handler = &handler_D_heredoc;
	signals_man->signals_heredoc.sa_Term.sa_handler = &handler_Term_heredoc;*/
}

int main(void)
{

	t_signal_manager sa_manager;

	init_handlers(&sa_manager);
	listen_signal(&sa_manager.signals_menu);
	while(1)
	{
        pause();  // Using pause() instead of wait() to wait for signals
	}
	return 0;

}




