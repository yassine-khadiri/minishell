/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 16:42:37 by hbouqssi          #+#    #+#             */
/*   Updated: 2022/08/10 19:53:03 by ykhadiri         ###   ########.fr       */
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
		for (int fd = 3; fd < 20; ++fd)
		{
			close(fd);
		}
		execution_pipe_cmd(data, cmd);
		exit(1);
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

int	ft_pipe(t_data *data, t_command *cmd)
{
	t_command	*tmp;
	int			in;
	int			i;
	int			nb_cmds;

	i = 0;
	tmp = cmd;
	nb_cmds = get_nb_cmds(cmd);
	data->pids = malloc(sizeof(int) * nb_cmds);
	data->pipes = malloc(sizeof(int *) * nb_cmds);
	if (!data->pids || !data->pipes)
		return (0);
	add(&g_tools.garbage, data->pids);
	add(&g_tools.garbage, data->pipes);
	while (i < nb_cmds)
	{
		data->pipes[i] = malloc(sizeof(int) * 2);
		if (!data->pipes[i])
			return (0);
		add(&g_tools.garbage, data->pipes[i]);
		i++;
	}
	i = 0;
	while (cmd->next)
	{
		pipe(data->pipes[i]);
		cmd = cmd->next;
		++i;
	}
	i = 0;
	in = 0;
	cmd = tmp;
	while (cmd)
	{
		if (cmd->next != NULL)
			data->fd[1] = data->pipes[i][1];
		else
			data->fd[1] = 1;
		data->pid1 = fork();
		data->pids[i] = data->pid1;
		if (data->pid1 < 0)
			return (0);
		if (data->pid1 == 0)
			exec1(data, cmd, in);
		if (in != 0)
			close(in);
		if (data->fd[1] != 1)
			close(data->fd[1]);
		in = data->pipes[i][0];
		cmd = cmd->next;
		++i;
	}
	cmd = tmp;
	i = 0;
	while (cmd)
	{
		waitpid(data->pids[i], NULL, 0);
		cmd = cmd->next;
		++i;
	}
	return (1);
}
