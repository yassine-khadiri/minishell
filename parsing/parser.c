/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 00:15:45 by hbouqssi          #+#    #+#             */
/*   Updated: 2022/07/30 00:45:04 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmdline	*init_subcmd(char *cmd)
{ 
	t_cmdline	*sub_cmd;
	sub_cmd = malloc(sizeof(t_cmdline));
	if (!sub_cmd)
		return (NULL);
	sub_cmd->cmd = cmd;
	sub_cmd->next = NULL;
	return (sub_cmd);
}

void	fill_subcmd(t_cmdline **head, t_cmdline *sub_cmd)
{
	t_cmdline	*_head;

	if (!head)
		return ;
	_head = *head;
	if (!_head)
	{
		*head = sub_cmd;
		return ;
	}
	while (_head->next)
	{
		_head = _head->next;
	}
	_head->next = sub_cmd;
}

void	push_cmd_and_redir(t_token **tokens, t_env *lenv, t_cmdline **cmdline,
		t_redirection **redirections)
{
	while (*tokens && (*tokens)->type != N_line
		&& (*tokens)->type != PIPE)
	{
		if ((*tokens)->type == HERDOC || (*tokens)->type == APPEND
			|| (*tokens)->type == REDIN || (*tokens)->type == REDOUT)
		{
			push_redirections(&(*redirections),
				initalize_redirections((*tokens)->type, (*tokens)->next->value, lenv));
			(*tokens) = (*tokens)->next->next;
		}
		else if ((*tokens) && (*tokens)->type == WORD)
		{
			fill_subcmd(&(*cmdline), init_subcmd((*tokens)->value));
				(*tokens) = (*tokens)->next;
		}
		if ((*tokens)->type == NONE)
			(*tokens) = (*tokens)->next;
	}
}

t_command	*ft_parse(t_token *tokens, t_env *lenv)
{
	t_command		*cmd;
	t_redirection	*redirections;
	t_cmdline		*cmdline;

	cmd = NULL;
	while (tokens)
	{
		cmdline = NULL;
		redirections = NULL;
		push_cmd_and_redir(&tokens, lenv, &cmdline, &redirections);
		if (tokens->type == PIPE || tokens->type == N_line)
		{
			fill_command(&cmd, initialize_command(cmdline, redirections,
					tokens));
		}
		tokens = tokens->next;
	}
	return (cmd);
}
