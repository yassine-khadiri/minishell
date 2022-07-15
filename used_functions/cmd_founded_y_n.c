/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_founded_y_n.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:42:07 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/07/15 15:42:06 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pipe_founded(t_data *data)
{
	int	i;

	i = 0;
	while (data->cmd->command[i])
	{
		if (!ft_strcmp(data->cmd->command[i], "|"))
			return (1);
		i++;
	}
	return (0);
}

int	quotes_count(char *cmd)
{
	int	quotes_start;
	int	quotes_end;

	quotes_start = 0;
	quotes_end = 0;
	while (cmd[quotes_start] && cmd[quotes_start] == '"')
		quotes_start++;
	while (cmd[ft_strlen(cmd) - quotes_end - 1] && (cmd[ft_strlen(cmd)
			- quotes_end - 1] == '"'))
		quotes_end++;
	if (quotes_start == quotes_end)
		return (1);
	return (0);
}

int	cmd_founded_y_n(t_data *data)
{
	char	*path;
	int		result;
	int		i;

	path = NULL;
	result = -1;
	i = 0;
	if (quotes_count(data->cmd->command[0]))
		data->cmd->command[0] = ft_strtrim(data->cmd->command[0], "\"");
	else
	{
		printf("Syntax Error\n");
		return (0);
	}
	while (data->splitted_path[i])
	{
		if (!ft_strcmp(data->cmd->command[0], "export")
			|| !ft_strcmp(data->cmd->command[0], "unset")
			|| !ft_strcmp(data->cmd->command[0], "exit"))
			return (0);
		path = ft_strjoin(data->splitted_path[i], "/");
		path = ft_strjoin(path, data->cmd->command[0]);
		if (access(path, X_OK) != -1)
		{
			result = 0;
			break ;
		}
		i++;
	}
	if (result == -1)
		printf(WHT "minishell : %s: command not found\n" BLU,
				data->cmd->command[0]);
	return (free(path), result);
}
