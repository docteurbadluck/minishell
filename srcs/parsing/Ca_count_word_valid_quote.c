/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ca_count_word_valid_quote.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 12:51:06 by tdeliot           #+#    #+#             */
/*   Updated: 2025/05/06 14:22:57 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		skip_quoted_section(const char *input, int i, char quote);
int		skip_escaped_or_quoted(const char *input, int *i, int *c, int *flag);
void	count_parentheses_or_op(int *i, const char *input, int *counter);

// This function count the number of word in the input, quoted part as one word
// it veryfy also that the quote are closed. it work with \" it work also with '
// which allow you to write quotationthe
int	count_word_valid_quote(const char *input)
{
	int	i;
	int	flag;
	int	counter;
	int	result;

	counter = 0;
	i = -1;
	flag = 0;
	while (input[++i])
	{
		result = skip_escaped_or_quoted(input, &i, &counter, &flag);
		if (result == -1)
			return (-1);
		if (result == 1)
		{
			if (!input[i])
				break ;
			continue ;
		}
		set_flag(input, i, &flag, &counter);
		count_parentheses_or_op(&i, input, &counter);
	}
	return (counter);
}

void	count_parentheses_or_op(int *i, const char *input, int *counter)
{
	if (input[*i] == '(' || input[*i] == ')')
	{
		(*counter)++;
	}
	count_op(i, input, counter);
}

/*
int main()
{
	
	char *test = " a ab|cd&&def > def ||  ";
	printf("\n test : %s  : %d\n", test ,count_word_valid_quote(test));

	char *test1 = " \" ab&&v \\\" abcd  \\\" \"def  ";
	printf("\n test : %s  :%d\n", test1, count_word_valid_quote(test1));

	char *test2 = "";
	printf("%d\n",count_word_valid_quote(test2));

	char *test3 = " '  abcd def ' abd";
	printf("%d\n",count_word_valid_quote(test3));
	
	char *test4 = " ' \" abcd \"def  abd'";
	printf("%d\n",count_word_valid_quote(test4));
	
	char *test5 = "''";
	printf("%d\n",count_word_valid_quote(test5));

	char *test6 = " 'abcd def'abd";
	printf("%d\n",count_word_valid_quote(test6));

	char *test7 = " \"abc\\\"d de\\\"fabd\" ";
	printf("%d\n",count_word_valid_quote(test7));

	char *test8 = " 'abc \\' |rd de \\' fabd ' ";
	printf("%d\n",count_word_valid_quote(test8));

	char *test9 = " ((abvde || abcd) && (abc && def )) ()";
	printf("%d\n",count_word_valid_quote(test9));

	return (0);
}*/