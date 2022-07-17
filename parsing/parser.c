/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 00:15:45 by hbouqssi          #+#    #+#             */
/*   Updated: 2022/07/17 23:41:03 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void            display_commands(t_command *comd)
{
    t_redirection *curr_redir;
    t_command *new_list;
    new_list = comd;
    printf("\e[1;33mall commands: \e[0m\n");
    while (new_list != NULL)
    {
		printf("command: ");
        while (new_list->cmdline != NULL)
        {
            
				printf("[%s]", new_list->cmdline->cmd);
				new_list->cmdline = new_list->cmdline->next;
        }
        printf("\n");
        curr_redir = new_list->redirection;
        while (curr_redir != NULL)
        {
			printf("type: {%d} file: {%s}\n",curr_redir->type, curr_redir->file);
            curr_redir = curr_redir->next;
        }
		printf("separator: {%d}\n", new_list->separator);
        new_list = new_list->next;
    }
}

t_cmdline *init_subcmd(char *cmd)
{ 
	t_cmdline *sub_cmd;
		sub_cmd = malloc(sizeof(t_cmdline));
	if(!sub_cmd)
		return (NULL);
	sub_cmd->cmd = cmd;
	sub_cmd->next = NULL;
	return(sub_cmd);	
}

void fill_subcmd(t_cmdline **head, t_cmdline *sub_cmd)
{
	t_cmdline  *_head;

	if (!head)
		return ;
	_head = *head;
	if (!_head)
	{
		*head = sub_cmd;
		return ;
	}
	while (_head->next) {
		_head = _head->next;
	}
	_head->next = sub_cmd;
}

t_command *ft_parse(t_token *tokens, t_env *lenv)
{
	t_token			*first_word;
	t_command		*cmd;
	t_redirection	*redirections;
	t_cmdline		*cmdline;

	first_word = tokens;
	cmd = NULL;
	while (first_word)
	{
		cmdline = NULL;
		redirections = NULL;
		while (first_word && first_word->type != N_line && first_word->type != PIPE)
		{
			if(first_word->type == HERDOC || first_word->type == APPEND
				|| first_word->type == REDIN || first_word->type == REDOUT)
			{
				// push redirections
				push_redirections (&redirections, initalize_redirections(first_word->type, first_word->next->value, lenv));
				first_word = first_word->next->next;
			}
			else if (first_word && (first_word->type == WORD || first_word->type == DBQUOTE
				|| first_word->type == QUOTE))
			{
				fill_subcmd(&cmdline, init_subcmd(first_word->value));
				first_word = first_word->next;
			}
			if (first_word->type == NONE)
				first_word = first_word->next;
		}
		if (first_word->type == PIPE || first_word->type == N_line)
			fill_command(&cmd, initialize_command(cmdline, redirections, first_word));
		first_word = first_word->next;
	}
	// display_commands(cmd);
	return (cmd);
}