/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   F_set_groupid_control_logic.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:30:21 by tdeliot           #+#    #+#             */
/*   Updated: 2025/03/24 15:27:03 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


// attribute group number to each token to create block of command.
                // exemle "(" "ls" "-a" ">" "test.txt" "&&" "cat" "'\pwd'" ")" "||" "echo" "failed"
                //         -1    1    1   0       2      0     3       3   -2    0    4       4
            // check logical operation 
                // check if 0 are at the beginning or at the end.
                //check if two 0s are stuck together.
            // check for () 
                // for the parenthesis, a conter start to 0 and should finish on 0. and if it pass to -1 it break and show an error.
                    // each -1 that it pass -> +1 each -2 -> -1;
                    // if -1 is just before -2 erro
int	attribute_groupid()
{
	return 0;
}

/*
int main()
{
	t_parsed_command *ptr;
	int i = 0;
	ptr = tokenise("  && abcd | || > < >> ( )");

	printf("logic control : %d\n\n", typo_control_set_logic_op(ptr));
	i = 0;
	while (ptr[i].text)
	{
		printf("text : %s \nlo :%d\n\n",ptr[i].text, ptr[i].logical_operator);
		i++;
	}
	while (i > 0)
	{
		i--;
		free(ptr[i].text);
	}
	free(ptr);
}
*/