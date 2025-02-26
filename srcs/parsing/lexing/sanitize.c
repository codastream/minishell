#include "shell.h"

/*
 * splits next token string at split_index
 * appends a new token in between
 * ex : "<" "infile cat -e" becomes "<" "infile" "cat -e"
 */
void	split_append_token(t_data *data, t_token *token, int split_index, t_tokentype filetype)
{
	char	*filepath;
	char	*string2;
	t_token	*new;

	filepath = ft_substr(token->next->string, 0, split_index);
	check_alloc(data, filepath);
	new = new_token(data, filetype, token->index, "");
	check_alloc(data, new);
	free(new->string);
	new->string = filepath;
	string2 = ft_substr(token->next->string, split_index + 1, \
		ft_strlen(token->next->string));
	check_alloc(data, string2);
	free(token->next->string);
	token->next->string = string2;
	add_after(token, new);
}

t_token	*get_first_of_consecutive(t_token *token)
{
	t_token	*current;

	current = token;
	while (current->prev && current->prev->type == current->type)
	{
		current = current->prev;
	}
	return (current);
}

void	merge_word_with_next_words(t_data *data, t_token **tokens, t_token *token)
{
	while (token->type == T_WORD && token->next && token->next->type == T_WORD)
	{
		merge_with_next(data, tokens, token);
	}
}

int	merge_command_with_next_word(t_data *data, t_token **tokens, t_token *token)
{
	if (token->type != T_COMMAND)
		return (EXIT_IGNORE);
	while (token->type == T_COMMAND && token->next && token->next->type == T_WORD)
	{
		merge_with_next(data, tokens, token);
	}
	if (!token->command)
	{
		token->command = new_command(data, token->string);
		token->type = T_COMMAND;
	}
	update_command_from_string(data, token->command, token->string);
	return (EXIT_SUCCESS);
}

int	merge_word_with_next_literal(t_data *data, t_token **tokens, t_token *token)
{
	char	*trimmed;

	while (token->type == T_WORD && token->next && token->next->type == T_LITERAL_SINGLE)
	{
		trimmed = ft_strtrim(token->next->string, "'");
		check_alloc(data, trimmed);
		free(token->next->string);
		token->next->string = trimmed;
		merge_with_next(data, tokens, token);
	}
	return (EXIT_SUCCESS);
}
