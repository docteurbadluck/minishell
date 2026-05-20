/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 12:09:52 by tdeliot           #+#    #+#             */
/*   Updated: 2025/03/12 18:34:41 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

//tell the lenght of a string
int	ft_strlen_2(const char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (-1);
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

//find a char in a string and return a pointer on it. otherwise 0
char	*ft_strchr_2(const char *s, int c)
{
	int				i;
	unsigned char	ch;

	ch = (unsigned char) c;
	i = 0;
	if (s == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] == ch)
			return ((char *)&s[i]);
		i++;
	}
	if (ch == '\0')
	{
		return ((char *)&s[i]);
	}
	return (NULL);
}

//Join two string together, and then free str1
char	*ft_strjoin_2(char *str1, char *str2)
{
	char	*s;
	int		c;
	int		i;

	c = -1;
	i = -1;
	if (!str1)
	{
		str1 = malloc(1);
		str1[0] = '\0';
	}
	s = malloc(ft_strlen_2(str1)+ ft_strlen_2(str2) + 1);
	if (!s)
		return (NULL);
	while (str1[++c])
		s[c] = str1[c];
	while (str2[++i])
	{
		s[c] = str2[i];
		c++;
	}
	s[c] = '\0';
	free(str1);
	return (s);
}
