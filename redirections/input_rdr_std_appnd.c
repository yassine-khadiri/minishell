/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_rdr_std_appnd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 10:33:56 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/08/05 01:40:57 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_herdoc(t_data *data, t_command *cmd, char *cmd_herdoc, char *delimiter)
{
	char	*path;
	char	*tmp;
	char	**executed_cmd;
	int		i;

	i = 0;
	// (void)cmd_herdoc;
	// (void)delimiter;
	executed_cmd = malloc(sizeof(char *) * 1000);
	if (!executed_cmd)
		return (0);
	while (cmd->cmd_array[i] && ft_strcmp(cmd->cmd_array[i], delimiter))
	{
		executed_cmd[i] = cmd->cmd_array[i];
		i++;
	}
	executed_cmd[i] = cmd_herdoc;
	executed_cmd[++i] = NULL;
	i = 0;
	while (data->splitted_path[i])
	{
		path = ft_strjoin(data->splitted_path[i], "/");
		tmp = path;
		free(path);
		path = ft_strjoin(tmp, cmd->cmd_array[0]);
		if (!access(path, X_OK))
		{
			data->pid1 = fork();
			if (data->pid1 == 0)
			{
				// execve(path, executed_cmd, data->env);
				execve(path, cmd->cmd_array, data->env);
				free(path);
				exit(1);
			}
			waitpid(data->pid1, &data->status, 0);
			g_dollar_question = WEXITSTATUS(data->status);
			break ;
		}
		i++;
	}
	free(path);
	return (1);
}

void	input_rdr_std_appnd(t_data *data, t_command *cmd, char *str)
{
	int				fd;
	char			*file_path;
	t_redirection	*red;

	red = cmd->redirection;
	while (red)
	{
		if (!ft_strcmp(str, "input"))
			fd = open(red->file, O_RDONLY, 0777);
		else
		{
			file_path = malloc(sizeof(char) * (ft_strlen(red->file) + 6));
			file_path = ft_strjoin("/tmp/", ".");
			file_path = ft_strjoin(file_path, red->file);
			fd = open(file_path, O_CREAT | O_RDWR | O_TRUNC, 0777);
			write(fd, data->buffer_herdoc, ft_strlen(data->buffer_herdoc));
			if (!ft_strcmp(cmd->cmd_array[0], "echo"))
				printf("\n");
			else
			{
				dup2(fd, 0);
				exec_herdoc(data, cmd, file_path, red->file);
				dup2(data->g_std._stdin, 0);
				close(fd);
			}
			return ;
		}
		if (fd == -1)
		{
			perror(ft_strjoin("minishell: ", red->file));
			return ;
		}
		red = red->next;
	}
	dup2(fd, 0);
	execution_other_builtins(data, cmd);
	dup2(data->g_std._stdin, 0);
	close(fd);
}
