/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_cmd_founded_y_n.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 19:42:12 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/08/04 00:05:52 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	case_1(t_data *data, t_command *cmd, char *path)
{
	if (!access(cmd->cmd_array[0], X_OK))
	{
		path = extract_path(cmd);
		cmd->cmd_array[0] = (ft_strrchr(cmd->cmd_array[0], '/') + 1);
		cmd->cmd_array[1] = NULL;
		data->pid1 = fork();
		if (data->pid1 < 0)
			return (0);
		if (data->pid1 == 0)
		{
			execve(path, cmd->cmd_array, data->env);
			exit(1);
		}
		waitpid(data->pid1, NULL, 0);
	}
	return (1);
}

int	case_2(t_data *data, t_command *cmd, char *path)
{
	path = getcwd(data->getpath, sizeof(data->getpath));
	path = ft_strjoin(path, "/");
	path = ft_strjoin(path, cmd->cmd_array[0]);
	if (!access(path, X_OK))
	{
		data->pid1 = fork();
		if (data->pid1 < 0)
			return (0);
		if (data->pid1 == 0)
		{
			execve(path, cmd->cmd_array, data->env);
			exit(1);
		}
		waitpid(data->pid1, &data->status, 0);
		g_dollar_question = WEXITSTATUS(data->status);
	}
	else
	{
		write(2, RED "minishell: ", 19);
		write(2, cmd->cmd_array[0], ft_strlen(cmd->cmd_array[0]));
		write(2, ": No such file or directory\n" BLU, 36);
	}
	return (1);
}
