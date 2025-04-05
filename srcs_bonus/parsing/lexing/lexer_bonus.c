/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:59:08 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/05 13:16:06 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	add_token(t_data *data, t_token **tokens, char **s, int i)
{
	t_token		*token;

	if (ft_isemptystr(s[i]))
		return ;
	else if (!ft_strcmp(s[i], "||"))
		token = new_token(data, T_OR, i, s[i]);
	else if (!ft_strcmp(s[i], "|"))
		token = new_token(data, T_PIPE, i, s[i]);
	else if (!ft_strcmp(s[i], "<<"))
		token = new_token(data, T_REDIR_HEREDOC, i, s[i]);
	else if (!ft_strcmp(s[i], "<"))
		token = new_token(data, T_REDIR_IN, i, s[i]);
	else if (!ft_strcmp(s[i], ">>"))
		token = new_token(data, T_REDIR_APPEND, i, s[i]);
	else if (!ft_strcmp(s[i], ">"))
		token = new_token(data, T_REDIR_TRUNCATE, i, s[i]);
	else if (!ft_strcmp(s[i], "("))
		token = new_token(data, T_OPENING_PARENTHESIS, i, s[i]);
	else if (!ft_strcmp(s[i], ")"))
		token = new_token(data, T_CLOSING_PARENTHESIS, i, s[i]);
	else
		token = new_token(data, T_WORD, i, s[i]);
	check_alloc_token(data, token, s);
	add_token_back(tokens, token);
}

static int	add_commands(t_data *data, t_token **tokens)
{
	int	code;

	code = do_for_tokens(data, tokens, \
		update_command_from_extra_words_before_pipe);
	if (code != EXIT_SUCCESS)
		return (code);
	code = do_for_tokens(data, tokens, add_command_from_word);
	if (code != EXIT_SUCCESS)
		return (code);
	code = do_for_tokens_delete(data, tokens, add_command_from_redirop);
	if (code != EXIT_SUCCESS)
		return (code);
	if (PRINT == 1)
		ft_put_yellow("remove extra commands\n");
	code = do_for_tokens_delete(data, tokens, remove_extra_command);
	return (code);
}

static int	check_tokens(t_data *data, t_token **tokens)
{
	int	code;

	code = EXIT_SUCCESS;
	code = do_for_tokens(data, tokens, check_redirection);
	if (code != EXIT_SUCCESS)
		return (code);
	code = do_for_tokens(data, tokens, check_pipe);
	if (code != EXIT_SUCCESS)
		return (code);
	code = add_commands(data, tokens);
	if (code != EXIT_SUCCESS)
		return (code);
	code = do_for_tokens(data, tokens, handle_wilcard);
	if (code != EXIT_SUCCESS)
		return (code);
	if (PRINT == 1)
		ft_put_yellow("vars\n");
	code = do_for_tokens(data, tokens, expand_vars);
	code = do_for_tokens(data, tokens, handle_quotes);
	if (code != EXIT_SUCCESS)
		return (code);
	code = do_for_tokens(data, tokens, remove_empty_args);
	if (code != EXIT_SUCCESS)
		return (code);
	return (code);
}

int	tokenize(t_data *data, char *line)
{
	int			i;
	int			code;
	char		**splitted;
	char		**separators;
	t_delimiter	**delimiters;

	separators = init_separators_for_operators(data);
	delimiters = init_quote_delimiters(data);
	if (!delimiters)
		free(separators);
	check_alloc(data, delimiters);
	splitted = ft_split_skip(line, separators, delimiters);
	free(separators);
	free_delimiters(delimiters);
	check_alloc(data, splitted);
	data->tokens = ft_calloc(1, sizeof(t_token *));
	check_alloc_tokens(data, data->tokens, splitted);
	i = 0;
	while (splitted[i])
		add_token(data, data->tokens, splitted, i++);
	ft_free_2d_char_null_ended(splitted);
	if (PRINT == 1)
		print_tokens(data->tokens);
	code = check_tokens(data, data->tokens);
	return (code);
}
