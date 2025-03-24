/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   A_variable_manager.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:16:54 by tdeliot           #+#    #+#             */
/*   Updated: 2025/03/22 11:56:01 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		is_space_or_doll(char c);
int		lenght_variable(char *str);
char	**cut_input(char *input, int i);
char	*assembling(char *variable, char **array_of_str);
char	*handle_variable_expansion(char *input, int i);
char	*assembling(char *variable, char **array_of_str);

	// EXEMPLE : "ABCDEF $HOME ABCDEF" ->"ABCDEF /home/tdeliot ABCDEF"
	//the goal of this function is to transform $VARIABLE from the input 
	// into his value. We are doing it first to have a all elements before
	// starting to verify the input.not modify in quotation variable.

	// $$ ne fonctionne pas $? est remplacer par STATUS_LAST_PROCESS
	// TO MAKE IT WORK I ADD IN THE ENVIRONEMENT $status_process
	// so it's inportant to verify at the beggining that it is in the 
	//environnement and to know we have to verify that they are not in ""
char	*variable_manager(char *input)
{
	char	*return_input;
	int		i;
	int		flag;

	flag = 0;
	i = 0;
	if (!input)
		return (NULL);
	while (input[i])
	{
		if (input[i] == '"')
		{
			flag++;
			flag %= 2;
		}
		if (input[i] == '$' && input[i + 1] != ' '
			&& input[i + 1] != '\0' && !flag)
			return (handle_variable_expansion(input, i));
		i++;
	}
	return (ft_strdup(input));
}

char	*handle_variable_expansion(char *input, int i)
{
	char	**array_of_str;
	char	*return_input;
	char	*final_result;

	array_of_str = cut_input(input, i);
	if (input[i + 1] == '?')
	{
		free(array_of_str[1]);
		array_of_str[1] = ft_strdup("$status_process");
	}
	return_input = getenv(array_of_str[1] + 1);
	return_input = assembling(return_input, array_of_str);
	if (return_input)
	{
		final_result = variable_manager(return_input);
		free(return_input);
		return (final_result);
	}
	return (NULL);
}

int	lenght_variable(char *str)
{
	int	i;

	str++;
	i = 0;
	while (str[i] != '$' && str[i] != ' ' && str[i] != '\t'
		&& str[i] != '\n' && str[i])
	{
		i++;
	}
	i++;
	return (i);
}

char	**cut_input(char *input, int i)
{
	char	**array_of_str;
	int		compteur;

	array_of_str = ft_calloc(sizeof(char *), 4);
	array_of_str[0] = ft_calloc(sizeof(char), i + 1);
	ft_strlcpy(array_of_str[0], input, (i + 1));
	if (input[i + 1] == '$')
		compteur = 2;
	else 
		compteur = lenght_variable(&input[i]);
	array_of_str[1] = ft_calloc(sizeof(char), compteur + 1);
	ft_strlcpy(array_of_str[1], &input[i], compteur + 1);
	i += compteur;
	if (!input[i])
		return (array_of_str);
	array_of_str[2] = ft_calloc(sizeof(char), ft_strlen(&input[i]) + 1);
	ft_strlcpy(array_of_str[2], &input[i], ft_strlen(&input[i]) + 1);
	return (array_of_str);
}

char	*assembling(char *variable, char **array_of_str)
{
	char	*result;

	result = NULL;
	free(array_of_str[1]);
	if (array_of_str[0])
	{
		if (variable)
		{
			result = ft_strjoin(array_of_str[0], variable);
			free(array_of_str[0]);
		}
		else
		{
			result = ft_strdup(array_of_str[0]);
			free(array_of_str[0]);
		}
	}
	if (array_of_str[2])
	{
		result = ft_strjoin_2(result, array_of_str[2]);
		free(array_of_str[2]);
	}
	free(array_of_str);
	return (result);
}

/*
int main()
{
	
	char *test1 = variable_manager("$HOME");
	printf("%s", test1);
	printf("\n");
	free(test1);

	char *test2 = variable_manager("$HOME ABC");
	printf("%s", test2);
	printf("\n");
	free(test2);

	char *test7 = variable_manager("ABC $HOME");
	printf("%s", test7);
	printf("\n");
	free(test7);

	char *test3 = variable_manager("abc $HOME abc");
	printf("%s", test3);
	printf("\n");
	free(test3);
	
	char *test4 = variable_manager("abc $Z abc");
	printf("%s", test4);
	printf("\n");
	free(test4);

	char *test5 = variable_manager("abc $HOME abc $HOME");
	printf("%s", test5);
	printf("\n");
	free(test5);

	char *test6 = variable_manager("$Z");
	printf(".%s.", test6);
	printf("\n");
	free(test6);

	char *test8 = variable_manager(NULL);
	printf(".%s.", test8);
	printf("\n");

	char *test9 = variable_manager("abc $? abcd");
	printf(".%s.", test9);
	printf("\n");
	free(test9);

	char *test11 = variable_manager("abc\" $? \" abcd");
	printf(".%s.", test11);
	printf("\n");
	free(test11);

	char *test10 = variable_manager("abc\" $?  \" abcd $?");
	printf(".%s.", test10);
	printf("\n");
	free(test10);
	return 0;
}*/