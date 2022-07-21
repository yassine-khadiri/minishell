/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 15:38:16 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/07/20 23:31:45 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_err_mssj(t_command *cmd, int index)
{
	if (cmd->cmd_array[index + 1])
	{
		printf("Invalid Command :)\n");
		return (1);
	}
	return (0);
}

int	builtins_execution(t_data *data, t_command *cmd)
{
	int	i;

	i = 0;
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
			if (!print_err_mssj(cmd, i))
			{
				printf("exit\n");
				exit(0);
			}
		}
		i++;
	}
	return (0);
}
