/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_linked_list_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:32:40 by jholterh          #+#    #+#             */
/*   Updated: 2025/04/24 16:30:27 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_envadd_front(t_env **lst, t_env *new)
{
	new->next = *lst;
	*lst = new;
}

void	ft_envadd_back(t_env **lst, t_env *new)
{
	if (!*lst)
		ft_envadd_front(lst, new);
	else
		ft_envlast(*lst)->next = new;
}

t_env	*ft_envlast(t_env *lst)
{
	t_env	*tmp;

	tmp = lst;
	if (!lst)
		return (NULL);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

t_env	*ft_envlast_minus_one(t_env *lst)
{
	t_env	*tmp;

	tmp = lst;
	if (!lst || !lst->next)
		return (NULL);
	while (tmp->next && tmp->next->next)
		tmp = tmp->next;
	return (tmp);
}

void	ft_envadd_back_minus_one(t_env **lst, t_env *new)
{
	t_env	*last_minus_one;

	if (!*lst || !(*lst)->next)
		ft_envadd_front(lst, new);
	else
	{
		last_minus_one = ft_envlast_minus_one(*lst);
		if (last_minus_one)
		{
			new->next = last_minus_one->next;
			last_minus_one->next = new;
		}
	}
}
