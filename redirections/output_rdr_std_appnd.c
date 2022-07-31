/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_rdr_std_appnd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouqssi <hbouqssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 11:06:20 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/07/30 23:46:56 by hbouqssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec(t_data *data, t_command *cmd)
{
	char	*path;
	char	*tmp;
	int		pid;
	int		i;

	i = 0;
	while (data->splitted_path[i])
	{
		path = ft_strjoin(data->splitted_path[i], "/");
		tmp = path;
		free(path);
		path = ft_strjoin(tmp, cmd->cmd_array[0]);
		if (!access(path, X_OK))
		{
			pid = fork();
			if (pid == 0)
			{
				execve(path, cmd->cmd_array, data->env);
				free(path);
				exit(1);
			}
			waitpid(pid, &data->status, 0);
			g_dollar_question = WEXITSTATUS(data->status);
			break ;
		}
		i++;
	}
	free(path);
}

void	output_rdr_std_appnd(t_data *data, t_command *cmd, int flag)
{
	int	fd;
	t_redirection *red;

	red = cmd->redirection;
	while (red)
	{
		if (flag == 0x0008)
			fd = open(red->file,
					O_CREAT | O_RDWR | O_APPEND, 0777);
		else
			fd = open(red->file, O_CREAT | O_RDWR | O_TRUNC, 0777);
		if (fd == -1)
		{
			printf(RED "minishell: %s: No such file or directory\n",
				red->file);
			return ;
		}
		red = red->next;
	}
	dup2(fd, 1);
	exec(data, cmd);
	dup2(data->g_std._stdout, 1);
	close(fd);
}
