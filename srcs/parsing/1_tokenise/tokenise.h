#ifndef TOKENISE_H
# define TOKENISE_H

# include "minishell.h"

/* ===== PUBLIC API ===== */

t_parsed_command	*tokenise(char *input);

/* ===== INTERNAL HELPERS ===== */

/* 1_count_word_valid_quote.c */
int		count_word_valid_quote(const char *input);
void	count_parentheses_or_op(int *i, const char *input, int *counter);

/* 2_count_word_utils.c */
void	count_op(int *i, const char *input, int *counter);
int		char_is(char c);
void	set_flag(const char *input, int i, int *flag, int *counter);

/* 3_cut.c */
int		skip_escaped_or_quoted(const char *input, int *i, int *counter, int *flag);

/* 4_tokenise.c */
void	split_quote(char *input, int *i, int *y, t_parsed_command *array);
void	split_words(char *input, int *i, int *y, t_parsed_command *array);

/* 5_tokenise_utils.c */
void	split_special_char(char *input, int *i, int *y, t_parsed_command *a);
void	split_arrow(char *input, int *i, int *y, t_parsed_command *array);
void	split_parenthesis(char *input, int *i, int *y, t_parsed_command *array);
void	split_double_quote(char *input, int *i, int *y, t_parsed_command *array);

/* 6_split_word.c */
void	split_word_unit(char *input, int *i, int *y, t_parsed_command *array);

/* 7_split_op_utils.c */
void	split_operator(char *input, int *i, int *y, t_parsed_command *array);

#endif
