/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   N_input.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:23:59 by tdeliot           #+#    #+#             */
/*   Updated: 2025/03/28 12:31:45 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	read_input(void)
{
	char	*input;
	char	*pos;
	t_parsed_command *ptr;
	while (1)
	{
		pos = ft_strjoin(getenv("PWD"), "> ");
		input = readline(pos);
		if (ft_strlen(input))
		{
			add_history(input);
		}
		free(pos);
		if (!ft_strncmp(input,"exit",4))
		{
			free(input);
			break;
		}
		if (ft_strlen(input))
		{
			ptr = from_input_to_group(input);
			//count how many << 
			//create temporary file temp1.txt
			
		}
		free(input);
	}
	rl_clear_history();
	return 0;
}

int main()
{
	read_input();
	return 0;
	
}