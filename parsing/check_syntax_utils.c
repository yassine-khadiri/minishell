/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouqssi <hbouqssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 01:08:26 by hbouqssi          #+#    #+#             */
/*   Updated: 2022/07/30 04:18:44 by hbouqssi         ###   ########.fr       */
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
		printf(RED "minishell: syntax error near unexpected token `%s'\n" WHT,
			tokens->next->value);
		g_dollar_question = 258;
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
		printf("%s\n", tokens->next->value);
		printf("minishell: syntax error\n");
		g_dollar_question = 258;
		result = 1;
	}
	return (result);
}

int	pipe_error(t_token *tokens, t_token *head)
{
	int	result;

	(void)head;
	result = 0;
	if (tokens->next->type == PIPE
		|| tokens->next->type == SEMICOLON
		|| tokens->next->type == N_line)
	{
		printf(RED "minishell: syntax error near unexpected token `%s'\n" WHT,
			tokens->next->value);
		g_dollar_question = 258;
		result = 1;
	}
	return (result);
}
