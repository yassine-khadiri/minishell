/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 15:38:16 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/07/15 15:43:27 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_err_mssj(t_data *data, int index)
{
	if (data->cmd->command[index + 1])
	{
		printf("Invalid Command :)\n");
		return (1);
	}
	return (0);
}

int	builtins_execution(t_data *data)
{
	int	i;
	int	val;

	i = 0;
	val = false;
	while (data->cmd->command[i])
	{
		if (!ft_strcmp(data->cmd->command[i], "pwd"))
			return (ft_pwd(data));
		/*else if (!ft_strcmp(data->cmd->command[i], "cd"))
		{
			edit_pwd(env);
			if (chdir(data->cmd->command[++i]) == -1)
				printf("cd: %s: No such file or directory\n",
						data->cmd->command[i]);
		}*/
		else if (!ft_strcmp(data->cmd->command[i], "echo"))
			return (ft_echo(data, i));
		else if (!ft_strcmp(data->cmd->command[i], "export"))
			return (ft_export(data));
		else if (!ft_strcmp(data->cmd->command[i], "unset"))
			return (ft_unset(data, i));
		else if (!ft_strcmp(data->cmd->command[i], "env"))
			return (ft_env(data->env));
		else if (!ft_strcmp(data->cmd->command[i], "exit"))
		{
			if (!print_err_mssj(data, i))
			{
				printf("exit\n");
				exit(0);
			}
		}
		else if (!verify_rdr(data))
		{
			execution_other_builtins(data);
			break ;
		}
		i++;
	}
	return (val);
}
