/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 16:42:37 by hbouqssi          #+#    #+#             */
/*   Updated: 2022/08/10 00:30:49 by ykhadiri         ###   ########.fr       */
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
		// free(path);
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

int	ft_pipe(t_data *data, t_command *cmd)
{
	t_command	*tmp;
	int			in;
	int			pids[1024];
	int			pipes[1024][2];
	int			i;

	i = 0;
	tmp = cmd;
	while (cmd->next)
	{
		pipe(pipes[i]);
		cmd = cmd->next;
		++i;
	}
	i = 0;
	in = 0;
	cmd = tmp;
	while (cmd)
	{
		if (cmd->next != NULL)
			data->fd[1] = pipes[i][1];
		else
			data->fd[1] = 1;
		data->pid1 = fork();
		pids[i] = data->pid1;
		if (data->pid1 < 0)
			return (0);
		if (data->pid1 == 0)
			exec1(data, cmd, in);
		if (in != 0)
			close(in);
		if (data->fd[1] != 1)
			close(data->fd[1]);
		in = pipes[i][0];
		cmd = cmd->next;
		++i;
	}
	cmd = tmp;
	i = 0;
	while (cmd)
	{
		waitpid(pids[i], NULL, 0);
		cmd = cmd->next;
		++i;
	}
	return (1);
}

// int	execution_pipe_cmd(t_data *data, t_command *cmd)
// {
// 	char	*path;
// 	int		i;

// 	i = 0;
// 	// if(rdr_execution(data, cmd))
// 	// 	return (0);
// 	while (data->splitted_path[i])
// 	{
// 		path = ft_strjoin(data->splitted_path[i], "/");
// 		path = ft_strjoin(path, cmd->cmd_array[0]);
// 		if (!access(path, X_OK))
// 			execve(path, cmd->cmd_array, data->env);
// 		i++;
// 	}
// 	return (0);
// }

// int	exec1(t_data *data, t_command *cmd, int pid, int in)
// {
// 	if (pid == 0)
// 	{
// 		if (in != 0)
// 		{
// 			dup2(in, STDIN_FILENO);
// 			close(in);
// 		}
// 		if (data->fd[1] != 1)
// 		{
// 			dup2(data->fd[1], STDOUT_FILENO);
// 			close(data->fd[1]);
// 		}
// 		execution_pipe_cmd(data, cmd);
// 		exit(1);
// 	}
// 	if (pid > 0)
// 	{
// 		close(data->fd[1]);
// 		in = data->fd[0];
// 	}
// 	return (in);
// }

// int	ft_pipe(t_data *data, t_command *cmd)
// {
// 	t_command	*tmp;
// 	int			fd[2];
// 	int			pid1;
// 	int			pid2;
// 	int			in;

// 	in = 0;
// 	tmp = cmd;
// 	while (cmd->next)
// 	{
// 		pipe(fd);
// 		pid1 = fork();
// 		if (pid1 < 0)
// 			return (0);
// 		if (pid1 == 0)
// 		{
// 			if (in != 0)
// 			{
// 				dup2(in, STDIN_FILENO);
// 				close(in);
// 			}
// 			if (fd[1] != 1)
// 			{
// 				dup2(fd[1], STDOUT_FILENO);
// 				close(fd[1]);
// 			}
// 			execution_pipe_cmd(data, cmd);
// 			exit(1);
// 		}
// 		if (pid1 > 0)
// 		{
// 			close(fd[1]);
// 			in = fd[0];
// 		}
// 		// in = exec1(data, cmd, pid1, in);
// 		cmd = cmd->next;
// 	}
// 	pid2 = fork();
// 	if (pid2 < 0)
// 		return (0);
// 	if (pid2 == 0)
// 	{
// 		if (in != 0)
// 			dup2(in, STDIN_FILENO);
// 		execution_pipe_cmd(data, cmd);
// 		exit(1);
// 	}
// 	in = 3;
// 	if (pid2 > 0)
// 	{
// 		close(fd[0]);
// 		close(fd[1]);
// 		while (tmp)
// 		{
// 			close(in);
// 			wait(NULL);
// 			in++;
// 			tmp = tmp->next;
// 		}
// 	}
// 	return (1);
// }
