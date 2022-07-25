/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouqssi <hbouqssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 16:42:37 by hbouqssi          #+#    #+#             */
/*   Updated: 2022/07/25 21:58:31 by hbouqssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include<stdio.h>

int	execution_pipe_cmd(t_data *data, t_command *cmd)
{
	char	*path;
	int		i;

	i = 0;
	while (data->splitted_path[i])
	{
		path = ft_strjoin(data->splitted_path[i], "/");
		path = ft_strjoin(path, cmd->cmd_array[0]);
		if (!access(path, X_OK))
			execve(path, cmd->cmd_array, data->env);
		i++;
	}
	return (0);
}

int	exec1(t_data *data, t_command *cmd, int in)
{
	if (data->pid1 == 0)
	{
		if (in != 0)
		{
			dup2(in, STDIN_FILENO);
			close(in);
		}
		if (data->fd[1] != 1)
		{
			dup2(data->fd[1], STDOUT_FILENO);
			close(data->fd[1]);
		}
		execution_pipe_cmd(data, cmd);
		exit(1);
	}
	if (data->pid1 > 0)
	{
		close(data->fd[1]);
		in = data->fd[0];
	}
	return (in);
}

void	exec2(t_data *data, t_command *cmd, t_command *tmp, int in)
{
	if (data->pid2 == 0)
	{
		if (in != 0)
			dup2(in, STDIN_FILENO);
		execution_pipe_cmd(data, cmd);
		exit(1);
	}
	in = 3;
	if (data->pid2 > 0)
	{
		close(data->fd[0]);
		close(data->fd[1]);
		while (tmp)
		{
			close(in);
			wait(NULL);
			in++;
			tmp = tmp->next;
		}
	}
}

int	ft_pipe(t_data *data, t_command *cmd)
{
	t_command	*tmp;
	int			in;

	in = 0;
	tmp = cmd;
	while (cmd->next)
	{
		pipe(data->fd);
		data->pid1 = fork();
		if (data->pid1 < 0)
			return (0);
		in = exec1(data, cmd, in);
		cmd = cmd->next;
	}
	data->pid2 = fork();
	if (data->pid2 < 0)
		return (0);
	exec2(data, cmd, tmp, in);
	return (1);
}
