/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 01:09:55 by hbouqssi          #+#    #+#             */
/*   Updated: 2022/07/23 17:42:20 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_separator(t_command *cmd, t_token *tokens)
{
	if (tokens->type == PIPE)
	{
		cmd->separator = e_pipe;
	}
	else if (tokens->type == N_line)
	{
		cmd->separator = e_line;
	}
}

t_command	*initialize_command(t_cmdline *cmdline, t_redirection *redirections,
		t_token *tokens)
{
	t_command	*first_command;
	int			i;

	first_command = malloc(sizeof(t_command));
	i = 0;
	first_command->cmdline = cmdline;
	first_command->redirection = redirections;
	add_separator(first_command, tokens);
	first_command->next = NULL;
	return (first_command);
}

void	fill_command(t_command **head, t_command *command)
{
	t_command	*_head;

	if (!head || !command)
		return ;
	_head = *head;
	if (!_head)
	{
		*head = command;
		return ;
	}
	while (_head->next)
		_head = _head->next;
	_head->next = command;
}
