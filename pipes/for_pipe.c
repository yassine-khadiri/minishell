/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 22:06:52 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/08/10 23:47:15 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	exec1(t_data *data, t_command *cmd, int in)
{
	int	fd_number;

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
		fd_number = 3;
		// while (fd_number <= (data->nb_cmds * 2))
		while (fd_number <= 1024)
		{
			close(fd_number);
			fd_number++;
		}
		// for (int fd = 3; fd < 20; ++fd)
		// {
		// 	printf("%d\n", fd);
		// 	close(fd);
		// }
		execution_pipe_cmd(data, cmd);
		exit(1);
	}
	return (0);
}
