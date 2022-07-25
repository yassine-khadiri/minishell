/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_founded_y_n.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:42:07 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/07/25 22:49:29 by ykhadiri         ###   ########.fr       */
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

int	check_qtes_between_cmd(char *cmd)
{
	int	i;
	int	j;
	int	db_qtes_counter;
	int	si_qtes_counter;

	i = 0;
	db_qtes_counter = 0;
	si_qtes_counter = 0;
	while (cmd[i])
	{
		j = 0;
		if (cmd[i] == '"')
		{
			j = i + 1;
			// db_qtes_counter = 1;
			while (cmd[j])
			{
				if (cmd[j] == '\'')
					return (-1);
				else if (cmd[j] == '\"')
					j++;
			}
		}
		else if (cmd[i] == '\'')
		{
			j = i + 1;
			// db_qtes_counter = 1;
			while (cmd[j])
			{
				if (cmd[j] == '\"')
					return (-1);
				else if (cmd[j] == '\'')
					j++;
			}
		}
		i++;
	}
	return (0);
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
		// if (check_qtes_between_cmd(cmd->cmd_array[0]) != -1)
		// {
			if (!ft_strcmp(cmd->cmd_array[0], "export")
				|| !ft_strcmp(cmd->cmd_array[0], "unset")
				|| !ft_strcmp(cmd->cmd_array[0], "exit"))
				return (0);
			path = ft_strjoin(data->splitted_path[i], "/");
			path = ft_strjoin(path, cmd->cmd_array[0]);
			if (access(path, X_OK) != -1)
			{
				result = 0;
				break ;
			}
			i++;
		// }
		// else
		// {
		// 	result = -1;
		// 	break;
		// }
	}
	if (result == -1)
		print_not_found (&cmd);
	return (free(path), result);
}
