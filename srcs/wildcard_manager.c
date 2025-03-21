/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:37:33 by tdeliot           #+#    #+#             */
/*   Updated: 2025/03/21 18:24:38 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int compte_name(void);
char **name_array_generator(void);
int check_current_dir_input(char *input);
int	matching_name(char *pattern, char *name);
char	*handle_wildcard_expansion(char *input, int i);
char	**cut_input_wildcard(char *input, int i);
char	*wildcard_generator(char *input);




char	*wildcard_manager(char *input)
{
	char	*return_input;
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
		if (input[i] == '*')
			return (handle_wildcard_expansion(input, i));
		i++;
	}
	return (ft_strdup(input));

}

char	*handle_wildcard_expansion(char *input, int i)
{
	char	**array_of_str;
	char	*return_input;
	char	*final_result;

	array_of_str = cut_input_wildcard(input, i);
	
	return_input =  wildcard_generator(array_of_str[1]);

	return_input = assembling(return_input, array_of_str);
	if (return_input)
	{
		final_result = wildcard_manager(return_input);
		free(return_input);
		return (final_result);
	}
	return (NULL);
}

char	**cut_input_wildcard(char *input, int i)
{
	char	**array_of_str;
	int		compteur;
	int		save;
	
	compteur = 0;
	array_of_str = ft_calloc(sizeof(char *), 4);
	if (i != 0)
	{
		while((input[i] != ' ') && (i > 0))
		{
			i--;
		}
		i++;
	}
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
	/*i = 0;
	while (array_of_str[i])
	{
		printf("\n.%s.\n", array_of_str[i]);
		i++;
	}*/
	return (array_of_str);
}

char	*wildcard_generator(char *input)
{
	char	**names;
	int		i;
	char	*output_wild;
	char	*new_input;
	
	output_wild = ft_strdup("\0");
	i = 0;
	if (check_current_dir_input(input) == 1)
	{
		printf("incorect\n");
		return (NULL);
	}
	if (check_current_dir_input(input) == 2)
		new_input = input + ft_strlen(getenv("PWD")) + 1;
	else
		new_input = input;
	names = name_array_generator();
	printf("input : %s\n", new_input);
	while (names[i])
	{
		if (matching_name(new_input, names[i]) == 0)
		{
			output_wild = ft_strjoin_2(output_wild, names[i]);
			output_wild = ft_strjoin_2(output_wild, " ");
		}
		i++;
	}
	output_wild[ft_strlen(output_wild) - 1] = '\0';
	i = 0;
	while (names[i])
	{
		free(names[i]);
		i++;
	}
	free(names);

	return (output_wild);
}

int compte_name(void)
{
	DIR				*one_dir;
	struct dirent	*entry;
	char *pwd;
	int nbr_of_name;
	nbr_of_name = 0;	
	pwd = getenv("PWD");
	one_dir = opendir(pwd);
	while ((entry = readdir(one_dir)) != NULL)
	{
		nbr_of_name++;
	}
	closedir(one_dir);
	return (nbr_of_name);
}

char **name_array_generator(void)
{
	DIR				*my_dir;
	struct dirent	*entry;
	char			**list_of_name;
	int				i;

	i = 0;
	list_of_name = ft_calloc((compte_name() + 1), sizeof(char *));
	my_dir = opendir(getenv("PWD"));
	entry = readdir(my_dir);
	while ((entry = readdir(my_dir)) != NULL)
	{
		list_of_name[i] = ft_strdup(entry->d_name);
		i++;
	}
	closedir(my_dir);
	return (list_of_name);
}

int check_current_dir_input(char *input)
{
	char *pwd; 
	int		len_pwd;

	pwd = getenv("PWD");
	len_pwd = ft_strlen(pwd);
	if (ft_strchr(input, '/'))
	{
		if (ft_strncmp(pwd, input, len_pwd) == 0 &&
			input[len_pwd] == '/')
			return (2);
		return (1);
	}
	else 
	{
	//	printf("no path\n");
		return (0);
	}
}


int	matching_name(char *pattern, char *name)
{
	if (*pattern == '\0' && *name == '\0')
		return (0);
	if (*pattern == '\0')
		return (1); 

	if (*pattern == '*')
	{
		if (matching_name(pattern + 1, name) == 0)
			return (0);
		if (*name != '\0' && matching_name(pattern, name + 1) == 0)
			return (0);
		return 1;
	}
	if (*pattern == *name)
		return (matching_name(pattern + 1, name + 1));
	return (1);
}

int main()
{
	char *new = wildcard_manager("/home/tdeliot/Desktop/minishell_git/minishell/srcs/*.* *.out");
	int i = 0;

	printf(".%s.", new);
	free(new);



	
	return 0;
}