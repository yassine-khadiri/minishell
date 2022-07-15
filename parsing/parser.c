/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 00:15:45 by hbouqssi          #+#    #+#             */
/*   Updated: 2022/07/15 15:38:12 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	display_commands(t_command *comd)
{
	t_redirection	*curr_redir;
	t_command		*new_list;
	int				j;

	new_list = comd;
	printf("\e[1;33mall commands: \e[0m");
	while (new_list != NULL)
	{
		printf("command: ");
		if (new_list->command != NULL)
		{
			j = 0;
			while (new_list->command[j] != NULL)
			{
				printf("[%s]", new_list->command[j]);
				j++;
			}
		}
		printf("\n");
		curr_redir = new_list->redirection;
		while (curr_redir != NULL)
		{
			printf("type: {%d} file: {%s}\n", curr_redir->type,
				curr_redir->file);
			curr_redir = curr_redir->next;
		}
		printf("separator: {%d}\n", new_list->separator);
		new_list = new_list->next;
	}
}

t_command	*ft_parse(t_data *data)
{
	t_token	*curr_token;
	t_token	*f1_word;
	int		i;
	int		size;

	curr_token = data->tokens;
	size = 0;
	while (curr_token && curr_token->type != N_line
		&& curr_token->type != PIPE)
	{
		if ((curr_token->type == HERDOC || curr_token->type == APPEND
				|| curr_token->type == REDIN
				|| curr_token->type == REDOUT)
			&& curr_token->next->type == WORD)
			curr_token = curr_token->next->next;
		if (curr_token && (curr_token->type == WORD
				|| curr_token->type == DBQUOTE
				|| curr_token->type == QUOTE))
		{
			size++;
			curr_token = curr_token->next;
		}
		if (curr_token->type == NONE)
			curr_token = curr_token->next;
	}
	data->cmd = malloc(sizeof(t_command));
	data->cmd->command = malloc(sizeof(char *) * (size + 1));
	if (!data->cmd || !data->cmd->command)
		return (NULL);
	i = 0;
	f1_word = data->tokens;
	while (f1_word)
	{
		while (f1_word && f1_word->type != N_line
			&& f1_word->type != PIPE)
		{
			if (f1_word->type == HERDOC || f1_word->type == APPEND
				|| f1_word->type == REDIN || f1_word->type == REDOUT)
			{
				// push redirections
				push_rdr(&data->rdr,
					init_rdr(f1_word->type,
						f1_word->next->value,
						data->lenv));
				f1_word = f1_word->next->next;
			}
			else if (f1_word && (f1_word->type == WORD
					|| f1_word->type == DBQUOTE
					|| f1_word->type == QUOTE))
			{
				data->cmd->command[i++] = ft_strdup(f1_word->value);
				f1_word = f1_word->next;
			}
			if (f1_word->type == NONE)
				f1_word = f1_word->next;
		}
		data->cmd->command[i] = NULL;
		if (f1_word->type == PIPE || f1_word->type == N_line)
			fill_cmd(&data->cmd, init_cmd(data->cmd->command,
					data->rdr, f1_word));
		f1_word = f1_word->next;
	}
	display_commands(data->cmd);
	return (NULL);
}
