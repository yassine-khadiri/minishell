/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 16:42:37 by hbouqssi          #+#    #+#             */
/*   Updated: 2022/07/24 23:16:57 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include<stdio.h>

int	execution_pipe_cmd(t_data *data, t_command *cmd)
{
	char	*path;
	int		i;

	i = 0;
	if(rdr_execution(data, cmd))
		return (0);
	else
	{
		while (data->splitted_path[i])
		{
			path = ft_strjoin(data->splitted_path[i], "/");
			path = ft_strjoin(path, cmd->cmd_array[0]);
			if (!access(path, X_OK))
				execve(path, cmd->cmd_array, data->env);
			i++;
		}
	}
	return (0);
}

int	ft_pipe(t_data *data, t_command *cmd)
{
	int		fd[2];
	int		pid1;
	int		pid2;

	if (pipe(fd) == -1)
		return (0);
	pid1 = fork();
	if (pid1 < 0)
		return (0);
	if (pid1 == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execution_pipe_cmd(data, cmd);
	}
	pid2 = fork();
	if (pid2 < 0)
		return (0);
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execution_pipe_cmd(data, cmd->next);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(-1, NULL, 0);
	waitpid(-1, NULL, 0);
	return (1);
}
