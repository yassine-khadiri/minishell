/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 22:06:52 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/08/13 03:20:50 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pipe_founded(t_token *tokens)
{
	while (tokens)
	{
		if (!ft_strcmp(tokens->value, "|"))
			return (1);
		tokens = tokens->next;
	}
	return (0);
}

int	execution_pipe_cmd(t_data *data, t_command *cmd)
{
	char	*path;
	char	*tmp;
	int		i;

	i = 0;
	if (!ft_strcmp(cmd->cmd_array[0], "export"))
	{
		ft_export(data, cmd);
		return (0);
	}
	if (rdr_execution(data, cmd))
		return (0);
	while (data->splitted_path[i])
	{
		path = ft_strjoin(data->splitted_path[i], "/");
		tmp = path;
		path = ft_strjoin(tmp, cmd->cmd_array[0]);
		if (!access(path, X_OK))
			execve(path, cmd->cmd_array, data->env);
		i++;
	}
	return (0);
}

int	get_nb_cmds(t_command *cmd)
{
	int	nb_cmds;

	nb_cmds = 0;
	if (!cmd)
		return (0);
	while (cmd)
	{
		cmd = cmd->next;
		nb_cmds++;
	}
	return (nb_cmds);
}

void	close_fds(void)
{
	int	fd_number;

	fd_number = 3;
	while (fd_number <= 1024)
	{
		close(fd_number);
		fd_number++;
	}
}

int	exec1(t_data *data, t_command *cmd, int in)
{
	if (data->pid1 == 0)
	{
		if (in != 0)
		{
			if (dup2(in, STDIN_FILENO) == -1)
			{
				perror("error");
				exit(1);
			}
			close(in);
		}
		if (data->fd[1] != 1)
		{
			if (dup2(data->fd[1], STDOUT_FILENO) == -1)
			{
				perror("error");
				exit(1);
			}
			close(data->fd[1]);
		}
		close_fds();
		execution_pipe_cmd(data, cmd);
		exit(1);
	}
	return (0);
}
