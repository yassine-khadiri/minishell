/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_rdr_std_appnd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 11:06:20 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/07/20 17:57:07 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec(t_data *data, t_command *cmd)
{
	int		pid;
	int		i;
	char	*path;

	i = 0;
	while (data->splitted_path[i])
	{
		path = ft_strjoin(data->splitted_path[i], "/");
		path = ft_strjoin(path, cmd->cmd_array[0]);
		if (!access(path, X_OK))
		{
			pid = fork();
			if (pid == 0)
				execve(path, cmd->cmd_array, data->env);
			else
				waitpid(pid, NULL, 0);
		}
		i++;
	}
}


void	output_rdr_std_appnd(t_data *data, t_command *cmd, int flag)
{
	int	fd;

	while (cmd->redirection)
	{
		if (flag == 0x0008)
			fd = open(cmd->redirection->file, O_CREAT | O_RDWR | O_APPEND, 0777);
		else
			fd = open(cmd->redirection->file, O_CREAT | O_RDWR | O_TRUNC, 0777);
		if (fd == -1)
		{
			printf(RED "minishell: %s: No such file or directory\n", cmd->redirection->file);
			return ;
		}
		cmd->redirection = cmd->redirection->next;
	}
	dup2(fd, 1);
	exec(data, cmd);
	dup2(data->g_std._stdout, 1);
	close(fd);
}
