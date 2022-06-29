/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 16:42:37 by hbouqssi          #+#    #+#             */
/*   Updated: 2022/06/29 14:49:34 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_cmd(char *str)
{
	char	**splitted_cmd;

	splitted_cmd = ft_split(str, ' ');
	return (splitted_cmd);
}

void	execution_pipe_cmd(t_data *data)
{
	char	*path;
	char	**spllited_cmd;

	spllited_cmd = get_cmd(data->spllited_cmd_buf);
	while (*data->splitted_env)
	{
		path = ft_strjoin(*data->splitted_env, "/");
		path = ft_strjoin(path, spllited_cmd[0]);
		if (!access(path, X_OK))
			execve(path, data->spllited_cmd_buf, env);
		data->splitted_env++;
	}
}

char	**get_cmds(char *str)
{
	char	**get_cmds;

	get_cmds = ft_split(str, '|');
	return (get_cmds);
	return (NULL);
}

int	ft_pipe(t_data *data)
{
	char	**new_av;
	int		fd[2];
	int		pid1;
	int		pid2;

	new_av = get_cmds(data->spllited_cmd_buf);
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
		execution_pipe_cmd(new_av[0], data->env);
	}
	pid2 = fork();
	if (pid2 < 0)
		return (0);
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execution_pipe_cmd(new_av[1], data->env);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (1);
}
