/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 01:08:26 by hbouqssi          #+#    #+#             */
/*   Updated: 2022/08/16 22:10:30 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	none_error(t_token *tokens, t_token *head)
{
	int	result;

	(void)head;
	result = 0;
	if (tokens->next->type == PIPE || tokens->next->type == SEMICOLON)
	{
		write(2, RED "minishell: syntax error near unexpected token `", 54);
		write(2, tokens->next->value, ft_strlen(tokens->next->value));
		write(2, "'\n", 2);
		g_tools.g_dollar_question = 258;
		result = 1;
	}
	else if (tokens->next->type == N_line)
		result = 1;
	return (result);
}

int	redir_error(t_token *tokens, t_token *head)
{
	int	result;

	(void)head;
	result = 0;
	if (tokens->next->type != WORD)
	{
		write(2, "minishell: syntax error '", 25);
		write(2, tokens->next->value, ft_strlen(tokens->next->value));
		write(2, "`\n", 2);
		g_tools.g_dollar_question = 258;
		result = 1;
	}
	return (result);
}

int	pipe_error(t_token *tokens, t_token *head)
{
	int	result;

	(void)head;
	result = 0;
	if (tokens->next->type == PIPE || tokens->next->type == SEMICOLON)
	{
		write(2, RED "minishell: syntax error near unexpected token `", 54);
		write(2, tokens->next->value, ft_strlen(tokens->next->value));
		write(2, "'\n", 2);
		g_tools.g_dollar_question = 258;
		result = 1;
	}
	else if (tokens->next->type == N_line)
	{
		write(2, RED "minishell: syntax error near unexpected token `", 54);
		write(2, tokens->next->value, ft_strlen(tokens->next->value));
		write(2, "'\n", 2);
		g_tools.g_dollar_question = 258;
		result = 1;
	}
	return (result);
}
