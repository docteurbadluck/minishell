/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fa_set_groupid_control_logic.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:30:21 by tdeliot           #+#    #+#             */
/*   Updated: 2025/04/08 16:59:23 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	give_value(t_parsed_command *array, int i)
{
	array[i].group_id = 0;
	if (array[i].logical_operator == -1)
		array[i].group_id = -1;
	if (array[i].logical_operator == -2)
		array[i].group_id = -2;
	if (array[i].logical_operator == 4)
		array[i].group_id = -3;
}

int	control_border_logic(t_parsed_command *array)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (array[i + 1].text)
		i++;
	while (array[i].group_id == -1 || array[i].group_id == -2)
		i--;
	while (array[y].group_id == -1 || array[y].group_id == -2)
		y++;
	if (array[y].group_id == 0 || array[i].group_id == 0)
	{
		printf("error control logic\n");
		return (-1);
	}
	return (0);
}
