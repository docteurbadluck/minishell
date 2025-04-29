/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   A_Amain.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 12:42:07 by tdeliot           #+#    #+#             */
/*   Updated: 2025/04/26 16:19:23 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
int main(int argc, char **argv, char **envp)
{
    t_free free_all = {NULL, NULL, NULL, NULL};

    // Create the abstract syntax tree
    free_all.tree = from_text_to_tree("ls -l | wc -c", &free_all.new_array);
    if (!free_all.tree)
    {
        cleanup(&free_all);
        return (1); // Exit if tree creation fails
    }

    // Prepare the environment and AST helper
    if (prepare_env_exp(&free_all.env_exp, envp) == 0 &&
    create_ast_helper(&free_all.ast_helper) == 0)
    {
        prepare_execution_ast(free_all.tree, free_all.env_exp,
        free_all.ast_helper, &free_all);
    }

    // Cleanup allocated resources
    cleanup(&free_all);

    return (0);
}*/

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	read_input(argv[0], envp);
	return (0);
}

// pwd && unset HOME && cd || echo yes
//  ls -l && echo <hello | ls -l 
// cat < input.txt | sort | tee | grep a > output.txt