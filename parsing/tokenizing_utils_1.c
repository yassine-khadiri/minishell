/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing_utils_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 01:04:51 by hbouqssi          #+#    #+#             */
/*   Updated: 2022/08/08 02:23:52 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	word(t_token **tokens, char *str)
{
	static int	i;
	char		*tmp;
	tmp = NULL;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0' && not_word(str[i], " |\"'<>"))
		i++;
	
	if (i != 0)
	{
		tmp = ft_strndup(str, i);
		add_back(tokens, create_token(WORD, tmp));
	}
	if (tmp)
		free(tmp);
	return (i);
}

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
		add_back(tokens, create_token(QUOTE, ft_strndup(str + 1, i - 1)));
	else
		return (-1);
	return (i + 1);
}
