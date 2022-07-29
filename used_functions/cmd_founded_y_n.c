/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_founded_y_n.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:42:07 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/07/29 01:06:48 by ykhadiri         ###   ########.fr       */
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
	printf (WHT "minishell : %s: command not found\n" BLU,
		(*cmd)->cmd_array[0]);
	g_dollar_question = 127;
}

int	check_executable_files(t_data *data, t_command *cmd)
{
	int		pid;
	char	*path;
	if (cmd->cmd_array[0][0] == '.' && cmd->cmd_array[0][1] == '/')
	{
		path = NULL;
		path = getcwd(data->getpath, sizeof(data->getpath));
		path = ft_strjoin(path, "/");
		path = ft_strjoin(path, cmd->cmd_array[0]);
		if (!access(path, X_OK))
		{
			pid = fork();
			if (pid < 0)
				return (0);
			if (pid == 0)
			{
				execve(path, cmd->cmd_array, data->env);
				exit(1);
			}
			waitpid(pid, NULL, 0);
		}
		else
		{
			write(2, RED"minishell: ", 19);
			write(2, cmd->cmd_array[0], ft_strlen(cmd->cmd_array[0]));
			write(2, ": No such file or directory\n"BLU, 36);
		}
	}
	return (1);
}

int	cmd_founded_y_n(t_data *data, t_command *cmd)
{
	char	*path;
	int		result;
	int		i;

	path = NULL;
	result = -1;
	i = 0;
	while (data->splitted_path[i])
	{
		if (!ft_strcmp(cmd->cmd_array[0], "export")
			|| !ft_strcmp(cmd->cmd_array[0], "unset")
			|| !ft_strcmp(cmd->cmd_array[0], "exit")
			|| check_executable_files(data, cmd))
			return (0);
		path = ft_strjoin(data->splitted_path[i], "/");
		path = ft_strjoin(path, cmd->cmd_array[0]);
		if (access(path, X_OK) != -1)
		{
			result = 0;
			break ;
		}
		i++;
	}
	if (result == -1)
	{
		write(2, RED"minishell: ", 19);
		write(2, cmd->cmd_array[0], ft_strlen(cmd->cmd_array[0]));
		write(2, ": command not found\n"BLU, 28);
		g_dollar_question = 127;
	}
	return (free(path), result);
}
