/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_rdr_std_appnd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 11:06:20 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/07/15 17:03:00 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_size_splited_cmd(char **data)
{
	int	len;

	len = 0;
	if (!data)
		return (0);
	while (data[len])
	{
		if (!ft_strcmp(data[len], ">") || !ft_strcmp(data[len], ">>")
			|| !ft_strcmp(data[len], "<"))
			break ;
		len++;
	}
	return (len);
}

char	**get_splitted_cmd(char **data)
{
	char	**splitted_cmd;
	int		i;

	i = 0;
	splitted_cmd = malloc(get_size_splited_cmd(data) * sizeof(char *));
	if (!splitted_cmd)
		return (NULL);
	while (data[i])
	{
		if (!ft_strcmp(data[i], ">") || !ft_strcmp(data[i], ">>")
			|| !ft_strcmp(data[i], "<"))
		{
			splitted_cmd[i] = NULL;
			break ;
		}
		splitted_cmd[i] = data[i];
		i++;
	}
	return (splitted_cmd);
}

void	exec(t_data *data)
{
	int		pid;
	int		i;
	char	*path;

	i = 0;
	while (data->splitted_path[i])
	{
		path = ft_strjoin(data->splitted_path[i], "/");
		path = ft_strjoin(path, data->cmd->command[0]);
		if (!access(path, X_OK))
		{
			pid = fork();
			if (pid == 0)
				execve(path, get_splitted_cmd(data->cmd->command),
					data->env);
			else
				waitpid(pid, NULL, 0);
		}
		i++;
	}
}

const char	*get_file_name(t_data *data)
{
	int	i;

	i = 0;
	while (data->cmd->command[i])
	{
		if (!ft_strcmp(data->cmd->command[i], ">")
			|| !ft_strcmp(data->cmd->command[i], ">>")
			|| !ft_strcmp(data->cmd->command[i], "<"))
		{
			data->fd_name = data->cmd->command[++i];
			return (data->fd_name);
		}
		i++;
	}
	return (NULL);
}

void	output_rdr_std_appnd(t_data *data, int flag)
{
	int	fd;

	get_file_name(data);
	if (flag == 0x0008)
		fd = open(data->fd_name, O_CREAT | O_RDWR | O_APPEND, 0777);
	else
		fd = open(data->fd_name, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd == -1)
	{
		printf(RED "minishell: %s: No such file or directory\n", data->fd_name);
		return ;
	}
	dup2(fd, 1);
	exec(data);
	dup2(data->g_std._stdout, 1);
	close(fd);
}
