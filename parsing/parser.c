/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 00:15:45 by hbouqssi          #+#    #+#             */
/*   Updated: 2022/08/16 22:12:39 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmdline	*init_subcmd(char *cmd)
{
	t_cmdline	*sub_cmd;

	sub_cmd = malloc(sizeof(t_cmdline));
	if (!sub_cmd)
		return (NULL);
	add(&g_tools.garbage, sub_cmd);
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
		_head = _head->next;
	_head->next = sub_cmd;
}

void	push_cmd_and_redir(t_data *data, t_token **tokens, t_cmdline **cmdline,
		t_redirection **redirections)
{
	while (*tokens && (*tokens)->type != N_line && (*tokens)->type != PIPE)
	{
		if ((*tokens)->type == HERDOC || (*tokens)->type == APPEND
			|| (*tokens)->type == REDIN || (*tokens)->type == REDOUT)
		{
			push_redirections(&(*redirections),
				initalize_redirections(data, *cmdline, (*tokens)->type,
					(*tokens)->next->value));
			(*tokens) = (*tokens)->next;
		}
		else if ((*tokens) && ((*tokens)->type == WORD
				|| (*tokens)->type == WSPACE))
			fill_subcmd(&(*cmdline), init_subcmd((*tokens)->value));
		(*tokens) = (*tokens)->next;
	}
}

t_command	*ft_parse(t_data *data, t_token *tokens)
{
	t_command		*cmd;
	t_redirection	*redirections;
	t_cmdline		*cmdline;

	cmd = NULL;
	while (tokens)
	{
		cmdline = NULL;
		redirections = NULL;
		push_cmd_and_redir(data, &tokens, &cmdline, &redirections);
		if (tokens->type == PIPE || tokens->type == N_line)
		{
			fill_command(&cmd, initialize_command(cmdline, redirections,
					tokens));
		}
		tokens = tokens->next;
	}
	return (cmd);
}
