/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 16:42:37 by hbouqssi          #+#    #+#             */
/*   Updated: 2022/07/14 16:20:05 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **get_cmd(char *str)
{
	char **splitted_cmd;

	splitted_cmd = ft_split(str, ' ');
	return (splitted_cmd);
}

void execution_pipe_cmd(t_data *data, char *cmd)
{
	char *path;
	char **spllited_cmd;
	int i;

	i = 0;
	printf("%s\n", cmd);
	cmd = ft_strtrim(cmd, " ");
	spllited_cmd = get_cmd(cmd);
	// printf("%s\n", spllited_cmd[0]);
	while (*data->splitted_path[i])
	{
		path = ft_strjoin(*data->splitted_path, "/");
		path = ft_strjoin(path, spllited_cmd[0]);
		if (!access(path, X_OK))
			execve(path, data->spllited_cmd_buf, data->env);
		i++;
	}
}

char **get_cmds(char **str)
{
	int i;
	char **get_cmds;
	char *cmds;

	i = 2;
	cmds = ft_strjoin_space(str[0], str[1]);
	while (str[i])
	{
		cmds = ft_strjoin_space(cmds, str[i]);
		i++;
	}
	get_cmds = ft_split(cmds, '|');
	return (get_cmds);
}

int ft_pipe(t_data *data)
{
	char **cmds_arr;
	int fd[2];
	int pid1;

	cmds_arr = get_cmds(data->spllited_cmd_buf);
	int pid2;

	// while (*cmds_arr)
	// 	printf("%s\n", *cmds_arr++);
	printf("%s\n", cmds_arr[0]);
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
		execution_pipe_cmd(data, cmds_arr[0]);
	}
	pid2 = fork();
	if (pid2 < 0)
		return (0);
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execution_pipe_cmd(data, cmds_arr[1]);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (1);
}
