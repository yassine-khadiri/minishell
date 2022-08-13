/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_founded_y_n.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:42:07 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/08/13 03:17:25 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*extract_path(t_command *cmd)
{
	char	*command;
	int		size;
	int		i;

	i = 0;
	command = malloc(sizeof(char *) * ft_strlen(cmd->cmd_array[0]));
	add(&g_tools.garbage, command);
	if (!command)
		return (NULL);
	size = ft_strlen(cmd->cmd_array[0])
		- ft_strlen(ft_strrchr(cmd->cmd_array[0], '/'));
	while (cmd->cmd_array[0][i] && i < size)
	{
		command[i] = cmd->cmd_array[0][i];
		i++;
	}
	command[i] = '\0';
	return (command);
}

int	check_executable_files(t_data *data, t_command *cmd)
{
	char	*path;

	path = NULL;
	if (cmd->cmd_array[0][0] == '/')
		return (case_1(data, cmd, path));
	else if (cmd->cmd_array[0][0] == '.' && cmd->cmd_array[0][1] == '/')
		return (case_2(data, cmd, path));
	return (0);
}

int	cmd_found_checker(char *path, t_command *cmd, t_data *data, int i)
{
	if (!ft_strcmp(cmd->cmd_array[0], "export")
		|| !ft_strcmp(cmd->cmd_array[0], "unset")
		|| !ft_strcmp(cmd->cmd_array[0], "exit")
		|| check_executable_files(data, cmd))
		return (1);
	path = ft_strjoin(data->splitted_path[i], "/");
	path = ft_strjoin(path, cmd->cmd_array[0]);
	if (access(path, X_OK) != -1)
		return (1);
	return (0);
}

int	check_unset_path(t_data *data, t_command *tmp)
{
	int	i;

	if (pipe_founded(data->tokens) && check_builts(tmp->cmd_array[0]))
	{
		while (tmp)
		{
			i = 0;
			while (tmp->cmd_array[i])
			{
				if (!check_builts(tmp->cmd_array[i]))
				{
					error_mssj(data, tmp->cmd_array[i]);
					return (-1);
				}
				i++;
			}
			tmp = tmp->next;
		}
	}
	else if (check_builts(tmp->cmd_array[0]))
		return (1);
	error_mssj(data, tmp->cmd_array[0]);
	return (-1);
}

int	cmd_founded_y_n(t_data *data, t_command *cmd)
{
	char		*path;
	int			result;
	int			i;

	path = NULL;
	result = -1;
	i = 0;
	if (!data->splitted_path)
	{
		check_unset_path(data, cmd);
		return (result);
	}
	while (data->splitted_path[i])
	{
		if (cmd_found_checker(path, cmd, data, i))
		{
			result = 1;
			break ;
		}
		i++;
	}
	if (result == -1)
		show_err_msg(cmd);
	return (result);
}
