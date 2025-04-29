/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_env_insert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:44:45 by jholterh          #+#    #+#             */
/*   Updated: 2025/04/08 16:58:01 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// helper function
void	insert_at_head(t_env **exp, t_env *new_node)
{
	new_node->next = *exp;
	*exp = new_node;
}

// helper function
void	insert_at_position(t_env **exp, int steps, t_env *new_node)
{
	t_env	*current_exp;
	t_env	*safe;

	current_exp = *exp;
	while (steps > 1 && current_exp->next->type != NULL)
	{
		current_exp = current_exp->next;
		steps--;
	}
	safe = current_exp->next;
	current_exp->next = new_node;
	new_node->next = safe;
}
