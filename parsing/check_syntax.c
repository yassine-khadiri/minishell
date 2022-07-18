/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 20:47:34 by hbouqssi          #+#    #+#             */
/*   Updated: 2022/07/18 15:20:59 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_err(t_token *tokens, t_token *head)
{
	int	result;

	result = 0;
	if (tokens->type == NONE)
		result = none_error(tokens, head);
	else if (tokens->type == HERDOC || tokens->type == APPEND
		|| tokens->type == REDIN || tokens->type == REDOUT)
		result = redir_error(tokens, head);
	else if (tokens->type == PIPE)
		result = pipe_error(tokens, head);
	return (result);
}

int	syntax_errors(t_token *head)
{
	t_token	*tokens;
	int		result;

	tokens = head;
	result = 0;
	while (tokens->type != N_line)
	{
		result = check_err(tokens, head);
		if (result == 1)
			break ;
		tokens = tokens->next;
	}
	return (result);
}
