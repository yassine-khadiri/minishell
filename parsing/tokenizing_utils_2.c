/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 01:04:51 by hbouqssi          #+#    #+#             */
/*   Updated: 2022/07/23 17:03:02 by ykhadiri         ###   ########.fr       */
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
		add_back(tokens, create_token(PIPE, ft_strdup("|")));
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
		add_back(tokens, create_token(HERDOC, ft_strdup("<<")));
		return (2);
	}
	else
		add_back(tokens, create_token(REDIN, ft_strdup("<")));
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
		add_back(tokens, create_token(APPEND, ft_strdup(">>")));
		return (2);
	}
	else
		add_back(tokens, create_token(REDOUT, ft_strdup(">")));
	return (1);
}
