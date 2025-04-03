/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   B_wildcard_manager.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:37:33 by tdeliot           #+#    #+#             */
/*   Updated: 2025/04/03 09:58:00 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*handle_wildcard_expansion(char *input, int i);
char	**cut_input_wildcard(char *input, int i);
char	*wildcard_generator(char *input);

//This function remplace the wildcard by their value if it's in the correct
// directory. it return null if the input was empty after an incorect wildcar
char	*wildcard_manager(char *input)
{
	int		i;
	int		flag;

	flag = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '"')
		{
			flag++;
			flag %= 2;
		}
		if (input[i] == '*' && !flag)
			return (handle_wildcard_expansion(input, i));
		i++;
	}
	return (ft_strdup(input));
}

//modifying to handle empty
char	*handle_wildcard_expansion(char *input, int i)
{
	char	**array_of_str;
	char	*return_input;
	char	*final_result;

	array_of_str = cut_input_wildcard(input, i);
	return_input = wildcard_generator(array_of_str[1]);
	return_input = assembling_wild(return_input, array_of_str);
	if (ft_strlen(return_input))
	{
		final_result = wildcard_manager(return_input);
		free(return_input);
		return (final_result);
	}
	free(return_input);
	return (NULL);
}

char	**cut_input_wildcard(char *input, int i)
{
	char	**array_of_str;
	int		compteur;
	int		save;

	compteur = 0;
	array_of_str = ft_calloc(sizeof(char *), 4);
	while ((input[i] != ' ') && (i > 0))
		i--;
	i++;
	if (i == 1 && input[0] != ' ')
		i--;
	array_of_str[0] = ft_calloc(sizeof(char), i + 1);
	ft_strlcpy(array_of_str[0], input, (i + 1));
	save = i;
	while (input[i] && input[i] != ' ')
	{
		compteur++;
		i++;
	}
	array_of_str[1] = ft_substr(input, save, compteur);
	array_of_str[2] = ft_strdup(&input[i]);
	return (array_of_str);
}

char	*get_filtered_wildcard_matches(char *pattern, char **names)
{
	char	*output_wild;
	int		i;

	output_wild = ft_strdup("\0");
	i = 0;
	while (names[i])
	{
		if (matching_name(pattern, names[i], 1) == 0)
		{
			output_wild = ft_strjoin_2(output_wild, names[i]);
			output_wild = ft_strjoin_2(output_wild, " ");
		}
		i++;
	}
	if (output_wild && ft_strlen(output_wild) > 0)
		output_wild[ft_strlen(output_wild) - 1] = '\0';
	return (output_wild);
}


char	*wildcard_generator(char *input)
{
	char	**names;
	char	*output_wild;
	char	*new_input;
	int		i;

	i = 0;
	if (check_current_dir_input(input) == 1)
	{
		printf("incorect directory wildcard\n");
		return (NULL);
	}
	if (check_current_dir_input(input) == 2)
		new_input = input + ft_strlen(getenv("PWD")) + 1;
	else
		new_input = input;
	names = name_array_generator();
	output_wild = get_filtered_wildcard_matches(new_input, names);
	while (names[i])
	{
		free(names[i]);
		i++;
	}
	free(names);
	return (output_wild);
}

/*

int main()
{
	
	char *new = wildcard_manager("*b.out");
	printf(".%s.\n\n", new);
	free(new);

	char *test1 = wildcard_manager("/home/tdeliot/Desktop/
	minishell_git/minishell.c/ *.out");
	printf(".%s.\n\n", test1);
	free(test1);

	char *test2 = wildcard_manager("*.out");
	printf(".%s.\n\n", test2);
	free(test2);

	char *test3 = wildcard_manager("*.*");
	printf(".%s.\n\n", test3);
	free(test3);

	char *test4 = wildcard_manager(" *.* *out");
	printf(".%s.\n\n", test4);
	free(test4);

	char *test5 = wildcard_manager("*out /home/tdeliot/Deskto
	p/minishell_git/minishell.c/ *.out *out");
	printf(".%s.\n\n", test5);
	free(test5);

	char *test6 = wildcard_manager(" abcde \".*  \" *out");
	printf(".%s.\n\n", test6);
	free(test6);
	
	return 0;
}*/