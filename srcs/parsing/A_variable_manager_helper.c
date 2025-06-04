/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   A_variable_manager_helper.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:25:17 by jholterh          #+#    #+#             */
/*   Updated: 2025/06/03 09:07:53 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_status_variable(char **array_of_str, t_env_exp *env_exp)
{
	char	*status_str;

	status_str = ft_itoa(env_exp->dollar_question);
	free(array_of_str[1]);
	array_of_str[1] = status_str;
	return (ft_strdup(status_str));
}

char	*handle_env_variable(char **array_of_str, t_env_exp *env_exp)
{
	char	*env_var;

	if (ft_getenv(env_exp->env, array_of_str[1] + 1, &env_var) != 0 || !env_var)
		return (ft_strdup(""));
	return (ft_strdup(env_var));
}

char	*process_final_result(char *final_result, t_env_exp *env_exp)
{
	char	*recursive_result;

	recursive_result = variable_manager(final_result, env_exp);
	free(final_result);
	return (recursive_result);
}

char	*handle_variable_expansion(char *input, int i, t_env_exp *env_exp)
{
	char	**array_of_str;
	char	*return_input;
	char	*final_result;

	array_of_str = cut_input(input, i);
	if (!array_of_str)
		return (NULL);
	if (input[i + 1] == '?')
		return_input = handle_status_variable(array_of_str, env_exp);
	else
		return_input = handle_env_variable(array_of_str, env_exp);
	final_result = assembling(return_input, array_of_str);
	free(return_input);
	if (final_result)
		return (process_final_result(final_result, env_exp));
	return (NULL);
}

int	should_expand_variable(char *input, int i, int flag)
{
	if (input[i] == '$' && input[i + 1] != ' ' && input[i + 1] != '"'
		&& input[i + 1] != '\0' && !flag)
		return (1);
	return (0);
}
