/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_founded_y_n.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:42:07 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/08/07 01:14:38 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pipe_founded(t_token *tokens)
{
	while (tokens)
	{
		if (!ft_strcmp(tokens->value, "|"))
			return (1);
		tokens = tokens->next;
	}
	return (0);
}

void	print_not_found(t_command **cmd)
{
	printf(WHT "minishell : %s: command not found\n" BLU,
		(*cmd)->cmd_array[0]);
	g_dollar_question = 127;
}

char	*extract_path(t_command *cmd)
{
	char	*command;
	int		size;
	int		i;

	i = 0;
	command = malloc(sizeof(char *) * ft_strlen(cmd->cmd_array[0]));
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

int	cmd_founded_y_n(t_data *data, t_command *cmd)
{
	char	*path;
	char	*tmp;
	int		result;
	int		i;

	path = NULL;
	result = -1;
	i = 0;
	if (error_mssj(data, cmd))
		return (result);
	while (data->splitted_path[i])
	{
		if (!ft_strcmp(cmd->cmd_array[0], "export")
			|| !ft_strcmp(cmd->cmd_array[0], "unset")
			|| !ft_strcmp(cmd->cmd_array[0], "exit")
			|| check_executable_files(data, cmd))
			return (0);
		path = ft_strjoin(data->splitted_path[i], "/");
		tmp = path;
		path = ft_strjoin(tmp, cmd->cmd_array[0]);
		free(tmp);
		if (access(path, X_OK) != -1)
		{
			free(path);
			result = 0;
			break ;
		}
		free(path);
		i++;
	}
	if (result == -1)
	{
		write(2, RED "minishell: ", 19);
		write(2, cmd->cmd_array[0], ft_strlen(cmd->cmd_array[0]));
		write(2, ": command not found\n" BLU, 28);
		g_dollar_question = 127;
	}
	return (result);
}
