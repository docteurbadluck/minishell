/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nb_input_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:23:59 by tdeliot           #+#    #+#             */
/*   Updated: 2025/05/06 14:02:02 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

t_free	init_free_all(t_env_exp *env_exp)
{
	t_free	free_all;

	free_all.new_array = NULL;
	free_all.tree = NULL;
	free_all.ast_helper = NULL;
	free_all.env_exp = env_exp;
	return (free_all);
}

char	*get_input(void)
{
	char	*input;
	char	*pos;

	pos = getcwd(NULL, 0);
	pos = ft_strjoin_2(pos, "> ");
	input = readline(pos);
	free(pos);
	return (input);
}
