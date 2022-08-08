/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 01:04:51 by hbouqssi          #+#    #+#             */
/*   Updated: 2022/08/08 01:14:24 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_pipe(t_token **tokens, char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '|')
		add_back(tokens, create_token(PIPE, "|"));
	return (1);
}

int	is_redin(t_token **tokens, char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i + 1] == '<')
	{
		add_back(tokens, create_token(HERDOC, "<"));
		return (2);
	}
	else
		add_back(tokens, create_token(REDIN, "<"));
	return (1);
}

int	is_redout(t_token **tokens, char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i + 1] == '>')
	{
		add_back(tokens, create_token(APPEND, ">>"));
		return (2);
	}
	else
		add_back(tokens, create_token(REDOUT, ">"));
	return (1);
}

int	is_space(t_token **tokens, char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] == ' ')
		i++;
	add_back(tokens, create_token(WSPACE, " "));
	return (i);
}
