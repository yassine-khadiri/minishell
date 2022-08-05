/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 01:09:55 by hbouqssi          #+#    #+#             */
/*   Updated: 2022/08/05 05:31:08 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*exec_herdoc(t_data *data, t_cmdline *cmd, t_redirection *redir)
{
	t_redirection	*red;

	red = redir;
	while (red)
	{
		data->file_path = malloc(sizeof(char) * (ft_strlen(red->file) + 7));
		data->file_path = ft_strjoin("/tmp/", ".");
		data->file_path = ft_strjoin(data->file_path, red->file);
		data->fd_h = open(data->file_path, O_CREAT | O_RDWR | O_TRUNC, 0777);
		write(data->fd_h, data->buffer_herdoc, ft_strlen(data->buffer_herdoc));
		if (!ft_strcmp(cmd->cmd, "echo"))
			printf("\n");
		if (data->fd_h == -1)
		{
			perror(ft_strjoin("minishell: ", red->file));
			return (0);
		}
		red = red->next;
	}
	return (data->file_path);
}

t_redirection	*initalize_redirections(t_data *data, t_cmdline *cmd, int type, char *value)
{
	t_redirection	*redirection;

	redirection = malloc(sizeof(t_redirection));
	if (!redirection)
		return (NULL);
	if (type == HERDOC)
	{
		type = REDIN;
		value = treat_heredocs(data, value);
		redirection->file = value;
		value = exec_herdoc(data, cmd, redirection);
	}
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
