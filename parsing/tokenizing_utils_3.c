/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing_utils_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 20:01:46 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/08/11 20:04:32 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sub_tokens(t_token **tokens, int *i, char *str)
{
	if (str[*i] == '|')
		*i += is_pipe(tokens, &str[*i]);
	else if (str[*i] == ' ')
		*i += is_space(tokens, &str[*i]);
	else if (str[*i] == '<')
		*i += is_redin(tokens, &str[*i]);
	else if (str[*i] == '>')
		*i += is_redout(tokens, &str[*i]);
	else if (str[*i] == ';')
		*i += semicolon(tokens, &str[*i]);
}

int	for_squotes(t_token **tokens, int *i, char *str, int *temp)
{
	if (str[*i] == 39)
	{
		*temp = quote(tokens, &str[*i]);
		if (*temp == -1)
			return (1337);
		*i += *temp;
		return (0);
	}
	return (0);
}

int	for_dbquotes(t_token **tokens, int *i, char *str, int *temp)
{
	if (str[*i] == 34)
	{
		*temp = db_quote(tokens, &str[*i]);
		if (*temp == -1)
			return (42);
		*i += *temp;
		return (0);
	}
	return (0);
}

int	c_q_word(t_token *token)
{
	t_token	*tmp;
	int		len;

	tmp = token;
	len = 0;
	while (tmp && tmp->type == DBQUOTE)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}
