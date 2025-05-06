/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_exp_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:31:51 by jholterh          #+#    #+#             */
/*   Updated: 2025/04/28 13:08:14 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_str(char **str)
{
	int i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

// copies from env, puts it at the right spot
// exp doesn't have _=, thats why it just copies until current_env->next
int	create_exp(t_env_exp *env_exp)
{
	t_env	*current_env;
	int		steps;

	if (env_exp == NULL || env_exp->env == NULL)
	{
		ft_printf("Error: Invalid input to create_exp.\n");
		return (1);
	}
	current_env = env_exp->env;
	env_exp->exp = NULL;
	while (current_env->next != NULL)
	{
		steps = find_exp_spot(env_exp->exp, current_env->type);
		ft_insertnode(&env_exp->exp, steps,
			current_env->type, current_env->data);
		current_env = current_env->next;
	}
	return (0);
}

// when the type already exits it needs to be replaced
// finds out how many steps and replaces the data
void	replace_data(t_env *head, t_env *new_node)
{
	t_env	*current;
	int		steps;

	current = head;
	steps = find_envtype(current, new_node->type);
	while (steps > 0)
	{
		current = current->next;
		steps--;
	}
	if (current->data != NULL)
	{
		free(current->data);
		current->data = NULL;
	}
	current->data = ft_strdup(new_node->data);
}

// ft_export should do the same as export
// content = NULL --> print env but sorted
// content = LOGNAME=tdeliot --> find out wether the type already exists
//		 --> replace the data if it exists
//		 --> create a new node if it doesn't
// both linked lists need to be updated, exp needs to stay sorted
static void	handle_existing_node(t_env_exp *env_exp, t_env *new_node)
{
	replace_data(env_exp->env, new_node);
	replace_data(env_exp->exp, new_node);
	free_node(new_node);
}

static void	handle_new_node(t_env_exp *env_exp, t_env *new_node)
{
	int	steps;

	ft_envadd_back_minus_one(&env_exp->env, new_node);
	steps = find_exp_spot(env_exp->exp, new_node->type);
	ft_insertnode(&env_exp->exp, steps, new_node->type, new_node->data);
}

int	ft_export_execution(t_env_exp *env_exp, char *content, int version)
{
	t_env	*new_node;

	if (content == NULL)
	{
		ft_env(env_exp->exp, version);
		return (0);
	}
	new_node = create_node(content);
	if (!new_node)
		return (-1);
	
	if (ft_getenv(env_exp->env, new_node->type, NULL) != 1)
	{
		if (ft_strncmp(new_node->data, "\0", 1) != 0)
			handle_existing_node(env_exp, new_node);
		else
			free_node(new_node);

	}
	else
	{
		handle_new_node(env_exp, new_node);
	}
	free_str(env_exp->execute_env);
	env_exp->execute_env = create_env_from_linked_list(env_exp->env);
	return (0);
}


int	ft_export(t_env_exp *env_exp, char **arguments, int version)
{
	int i;
	int result;

	if (!arguments || !arguments[1])
		return (ft_export_execution(env_exp, NULL, version));

	i = 1;
	while (arguments[i])
	{

		result = ft_export_execution(env_exp, arguments[i], version);
		if (result != 0)
			return (1);
		
		i++;
	}
	return (0);
}
