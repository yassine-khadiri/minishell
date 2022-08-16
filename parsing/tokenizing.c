/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 10:18:25 by hbouqssi          #+#    #+#             */
/*   Updated: 2022/08/16 19:35:13 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*ft_tokenizer(t_token **tokens, char *str)
{
	int	i;
	int	temp;

	i = 0;
	temp = 0;
	*tokens = initialize_list();
	while (str[i])
	{
		sub_tokens (tokens, &i, str);
		if (for_dbquotes (tokens, &i, str, &temp) == 42)
			return (printf("minishell: syntax error, Missing Db_Quotes\n"),
				NULL);
		else if (for_squotes (tokens, &i, str, &temp) == 1337)
			return (printf("minishell: syntax error, Missing S_Quotes\n"),
				NULL);
		else if (not_word(str[i], " |\"<'>;"))
			i += word(tokens, &str[i]);
	}
	add_back(tokens, create_token(N_line, "NEWLINE"));
	return (*tokens);
}

t_token	*filling_arrays(t_token *tokens, t_data *data)
{
	while (tokens && (tokens->type == DBQUOTE || tokens->type == WORD
			|| tokens->type == QUOTE))
	{
		if (tokens->type == WORD)
		{
			if (!ft_strcmp(tokens->value, "$?"))
			{
				printf("%d", g_tools.g_dollar_question);
				g_tools.g_dollar_question = 0;
			}
			if (!ft_strcmp(tokens->value, "$")
				&& (tokens->next->type == DBQUOTE
					|| tokens->next->type == QUOTE))
				tokens->value = ft_strtrim(tokens->value, "$");
			else
				tokens->value = check_remove_dollars(data, tokens->value);
		}
		else if (tokens->type == DBQUOTE)
			tokens->value = check_remove_dollars(data, tokens->value);
		data->tmp = ft_strjoin(data->tmp, tokens->value);
		tokens = tokens->next;
	}
	return (tokens);
}

char	**final_tokens(t_data *data, t_token **token)
{
	t_token	*tokens;
	t_token	*new_tokens;

	tokens = *token;
	new_tokens = NULL;
	while (tokens)
	{
		if (tokens->type == DBQUOTE || tokens->type == WORD
			|| tokens->type == QUOTE)
		{
			data->tmp = malloc(sizeof(char) * c_q_word(tokens));
			if (!data->tmp)
				return (0);
			add(&g_tools.garbage, data->tmp);
			tokens = filling_arrays(tokens, data);
			add_back(&new_tokens, create_token(WORD, data->tmp));
		}
		if (tokens->type != WSPACE)
			add_back(&new_tokens, create_token(tokens->type, tokens->value));
		if (tokens)
			tokens = tokens->next;
	}
	*token = new_tokens;
	return (NULL);
}
