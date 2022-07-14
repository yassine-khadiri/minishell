/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 00:15:45 by hbouqssi          #+#    #+#             */
/*   Updated: 2022/07/14 16:37:58 by ykhadiri         ###   ########.fr       */
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

t_command	*ft_parse(t_token *tokens, t_env *lenv)
{
	t_token *current_token;
	t_token *first_word;
	t_command *cmd = NULL;
	t_redirection *redirections = NULL;
	char **cmd_args = NULL;
	int i;
	int size;
	current_token = tokens;
	size = 0;
	while (current_token && current_token->type != N_line
		&& current_token->type != PIPE)
	{
		if ((current_token->type == HERDOC || current_token->type == APPEND
				|| current_token->type == REDIN
				|| current_token->type == REDOUT)
			&& current_token->next->type == WORD)
		{
			current_token = current_token->next->next;
		}

		if (current_token && (current_token->type == WORD
				|| current_token->type == DBQUOTE
				|| current_token->type == QUOTE))
		{
			size++;
			current_token = current_token->next;
		}
		if (current_token->type == NONE)
			current_token = current_token->next;
	}
	cmd_args = (char **)malloc(sizeof(char *) * (size + 1));
	if (!cmd_args)
		return (NULL);
	i = 0;
	first_word = tokens;
	while (first_word)
	{
		while (first_word && first_word->type != N_line
			&& first_word->type != PIPE)
		{
			if (first_word->type == HERDOC || first_word->type == APPEND
				|| first_word->type == REDIN || first_word->type == REDOUT)
			{
				// push redirections
				push_redirections(&redirections,
						initalize_redirections(first_word->type,
							first_word->next->value, lenv));
				first_word = first_word->next->next;
			}
			else if (first_word && (first_word->type == WORD
						|| first_word->type == DBQUOTE
						|| first_word->type == QUOTE))
			{
				cmd_args[i++] = ft_strdup(first_word->value);
				first_word = first_word->next;
			}
			if (first_word->type == NONE)
				first_word = first_word->next;
		}
		cmd_args[i] = NULL;
		if (first_word->type == PIPE || first_word->type == N_line)
			fill_command(&cmd, initialize_command(cmd_args, redirections,
						first_word));
		first_word = first_word->next;
	}
	display_commands(cmd);
	return (NULL);
}