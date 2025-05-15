/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_exp_operations_helper.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:18:57 by jholterh          #+#    #+#             */
/*   Updated: 2025/05/13 16:23:01 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ft_export should do the same as export
// content = NULL --> print env but sorted
// content = LOGNAME=tdeliot --> find out wether the type already exists
//		 --> replace the data if it exists
//		 --> create a new node if it doesn't
// both linked lists need to be updated, exp needs to stay sorted
void	replace_data(t_env *head, t_env *new_node);

void	handle_existing_node(t_env_exp *env_exp, t_env *new_node)
{
	replace_data(env_exp->env, new_node);
	replace_data(env_exp->exp, new_node);
	free_node(new_node);
}

void	handle_new_node(t_env_exp *env_exp, t_env *new_node)
{
	int		steps;

	ft_envadd_back_minus_one(&env_exp->env, new_node);
	steps = find_exp_spot(env_exp->exp, new_node->type);
	ft_insertnode(&env_exp->exp, steps, new_node->type, new_node->data);
}
