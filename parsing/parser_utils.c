/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 01:09:55 by hbouqssi          #+#    #+#             */
/*   Updated: 2022/07/18 15:33:42 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redirection	*initalize_redirections(int type, char *value, t_env *lenv)
{
	t_redirection	*redirection;

	redirection = malloc(sizeof(t_redirection));
	if (!redirection)
		return (NULL);
	if (type == HERDOC)
		value = treat_heredocs(value, lenv);
	redirection->type = type;
	redirection->file = value;
	redirection->next = NULL;
	return (redirection);
}

void	push_redirections(t_redirection **head, t_redirection *new_redirection)
{
	t_redirection	*_head;

	if (!head || !new_redirection)
		return ;
	_head = *head;
	if (!_head)
	{
		*head = new_redirection;
		return ;
	}
	while (_head->next)
		_head = _head->next;
	_head->next = new_redirection;
}

int	tab_size(char **cmd_args)
{
	int	i;

	i = 0;
	while (cmd_args[i] != NULL)
		i++;
	return (i);
}

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
