/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 15:38:16 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/08/07 01:24:55 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_options(t_command *cmd)
{
	int	i;

	i = 0;
	if (!ft_strcmp(cmd->cmd_array[i], "pwd") || !ft_strcmp(cmd->cmd_array[i],
			"cd") || !ft_strcmp(cmd->cmd_array[i], "export")
		|| !ft_strcmp(cmd->cmd_array[i], "unset")
		|| !ft_strcmp(cmd->cmd_array[i], "env") || !ft_strcmp(cmd->cmd_array[i],
			"exit"))
	{
		if (!cmd->cmd_array[i + 1])
			return (0);
		else if (cmd->cmd_array[i + 1][0] == '-')
		{
			printf(RED "%s Command Must Works Without Options\n",
				cmd->cmd_array[i]);
			return (1);
		}
	}
	return (0);
}

int	exec_builts(t_data *data, t_command *cmd, int index)
{
	if (!ft_strcmp(cmd->cmd_array[index], "pwd"))
		return (ft_pwd(data));
	else if (!ft_strcmp(cmd->cmd_array[index], "cd"))
		return (ft_cd(data, cmd, index));
	else if (!ft_strcmp(cmd->cmd_array[index], "echo"))
		return (ft_echo(data, cmd, index));
	else if (!ft_strcmp(cmd->cmd_array[index], "export"))
		return (ft_export(data, cmd));
	else if (!ft_strcmp(cmd->cmd_array[index], "unset"))
		return (ft_unset(data, cmd, index));
	else if (!ft_strcmp(cmd->cmd_array[index], "env"))
	{
		if (!data->splitted_path)
			return (0);
		return (ft_env(data->env));
	}
	else if (!ft_strcmp(cmd->cmd_array[index], "exit"))
	{
		if (!ft_exit(cmd))
			exit(g_dollar_question);
	}
	return (0);
}

int	builtins_execution(t_data *data, t_command *cmd)
{
	int	i;
	int	ret;

	i = 0;
	if (check_options(cmd))
		return (0);
	while (cmd->cmd_array[i])
	{
		ret = exec_builts(data, cmd, i);
		if (ret == 0)
			i++;
		return (ret);
	}
	return (0);
}
