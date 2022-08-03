/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouqssi <hbouqssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 01:04:51 by hbouqssi          #+#    #+#             */
/*   Updated: 2022/08/01 21:58:07 by hbouqssi         ###   ########.fr       */
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

int	is_space(t_token **tokens, char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] == ' ')
		i++;
	add_back(tokens, create_token(WSPACE, ft_strdup(" ")));
	return (i);
}
