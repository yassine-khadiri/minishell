/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 01:04:51 by hbouqssi          #+#    #+#             */
/*   Updated: 2022/07/18 15:32:55 by ykhadiri         ###   ########.fr       */
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

int	not_word(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (0);
		i++;
	}
	return (1);
}

int	db_quote(t_token **tokens, char *str)
{
	int	i;

	i = 1;
	if (!str)
		return (0);
	if (str[i])
	{
		while (str[i] && str[i] != '"')
			i++;
	}
	if (str[i] && str[i] == '"')
		add_back(tokens, create_token(DBQUOTE, ft_strndup(str + 1, i - 1)));
	else
		return (-1);
	return (i + 1);
}

int	quote(t_token **tokens, char *str)
{
	int	i;

	i = 1;
	if (!str)
		return (0);
	if (str[i])
	{
		while (str[i] && str[i] != '\'')
			i++;
	}
	if (str[i] && str[i] == '\'')
		add_back(tokens, create_token(DBQUOTE, ft_strndup(str + 1, i - 1)));
	else
		return (-1);
	return (i + 1);
}

int	word(t_token **tokens, char *str)
{
	static int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0' && not_word(str[i], " |\"'<>"))
		i++;
	if (i != 0)
		add_back(tokens, create_token(WORD, ft_strndup(str, i)));
	return (i);
}

// int dollar(t_token **tokens, char *str)
// {
//     int i;
//     i = 0;
//     if(!str)
//         return(0);
//     if (str[i] == '$')
//         add_back(tokens, create_token(DOLLAR, ft_strdup("$")));
//         return (1);
// }

int	semicolon(t_token **tokens, char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == ';')
		add_back(tokens, create_token(SEMICOLON, ft_strdup(";")));
	return (1);
}
