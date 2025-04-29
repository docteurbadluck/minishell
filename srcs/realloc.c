/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:30:21 by tdeliot           #+#    #+#             */
/*   Updated: 2025/04/08 17:01:11 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_realloc(void *old_ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	copy_size;

	if (old_size == new_size)
		return (old_ptr);
	if (new_size == 0)
	{
		free(old_ptr);
		return (NULL);
	}
	if (old_size < new_size) 
		copy_size = old_size;
	else 
		copy_size = new_size;
	if (old_ptr)
	{
		new_ptr = malloc(new_size);
		if (!new_ptr)
			return (NULL);
		ft_memcpy(new_ptr, old_ptr, copy_size);
		free(old_ptr);
	}
	else 
		new_ptr = malloc(new_size);
	return (new_ptr);
}
