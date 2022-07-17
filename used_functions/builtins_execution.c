/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 15:38:16 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/07/17 18:32:17 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_err_mssj(t_data *data, int index)
{
	if (data->arr_cmds[index + 1])
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
	while (data->arr_cmds[i])
	{
		if (!ft_strcmp(data->arr_cmds[i], "pwd"))
			return (ft_pwd(data));
		/*else if (!ft_strcmp(data->arr_cmds[i], "cd"))
		{
			edit_pwd(env);
			if (chdir(data->arr_cmds[++i]) == -1)
				printf("cd: %s: No such file or directory\n",
						data->arr_cmds[i]);
		}*/
		else if (!ft_strcmp(data->arr_cmds[i], "echo"))
			return (ft_echo(data, i));
		else if (!ft_strcmp(data->arr_cmds[i], "export"))
			return (ft_export(data));
		else if (!ft_strcmp(data->arr_cmds[i], "unset"))
			return (ft_unset(data, i));
		else if (!ft_strcmp(data->arr_cmds[i], "env"))
			return (ft_env(data->env));
		else if (!ft_strcmp(data->arr_cmds[i], "exit"))
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
