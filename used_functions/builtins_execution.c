/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 15:38:16 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/07/23 16:40:41 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_options(t_command *cmd)
{
	int	i;

	i = 0;
	if (!ft_strcmp(cmd->cmd_array[i], "pwd")
		|| !ft_strcmp(cmd->cmd_array[i], "cd")
		|| !ft_strcmp(cmd->cmd_array[i], "export")
		|| !ft_strcmp(cmd->cmd_array[i], "unset")
		|| !ft_strcmp(cmd->cmd_array[i], "env")
		|| !ft_strcmp(cmd->cmd_array[i], "exit"))
	{
		if (!cmd->cmd_array[i + 1])
			return (0);
		else if (cmd->cmd_array[i + 1][0] == '-')
		{
			printf(RED"%s Command Must Works Without Options\n",
				cmd->cmd_array[i]);
			return (1);
		}
	}
	return (0);
}

int	builtins_execution(t_data *data, t_command *cmd)
{
	int	i;

	i = 0;
	if (check_options(cmd))
		return (0);
	while (cmd->cmd_array[i])
	{
		if (!ft_strcmp(cmd->cmd_array[i], "pwd"))
			return (ft_pwd(data));
		else if (!ft_strcmp(cmd->cmd_array[i], "cd"))
			return (ft_cd(data, cmd, i));
		else if (!ft_strcmp(cmd->cmd_array[i], "echo"))
			return (ft_echo(data, cmd, i));
		else if (!ft_strcmp(cmd->cmd_array[i], "export"))
			return (ft_export(data, cmd));
		else if (!ft_strcmp(cmd->cmd_array[i], "unset"))
			return (ft_unset(data, cmd, i));
		else if (!ft_strcmp(cmd->cmd_array[i], "env"))
			return (ft_env(data->env));
		else if (!ft_strcmp(cmd->cmd_array[i], "exit"))
		{
			if (!ft_exit(cmd))
				exit(0);
		}
		i++;
	}
	return (0);
}
