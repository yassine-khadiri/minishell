/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 15:38:16 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/07/02 12:26:20 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_err_mssj(t_data *data, int index)
{
	if(data->spllited_cmd_buf[index + 1])
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

	while (data->spllited_cmd_buf[i])
	{
		if (!ft_strcmp(data->spllited_cmd_buf[i], "pwd"))
			return (ft_pwd(data));
		/*else if (!ft_strcmp(data->spllited_cmd_buf[i], "cd"))
		{
			edit_pwd(env);
			if (chdir(data->spllited_cmd_buf[++i]) == -1)
				printf("cd: %s: No such file or directory\n", data->spllited_cmd_buf[i]);
		}*/
		else if (!ft_strcmp(data->spllited_cmd_buf[i], "echo"))
			return (ft_echo(data, i));
		else if (!ft_strcmp(data->spllited_cmd_buf[i], "export"))
			return (ft_export(data));
		else if (!ft_strcmp(data->spllited_cmd_buf[i], "unset"))
			return (ft_unset(data, i));
		else if (!ft_strcmp(data->spllited_cmd_buf[i], "env"))
			return (ft_env(data->env));
		else if (!ft_strcmp(data->spllited_cmd_buf[i], "exit"))
		{
			if(!print_err_mssj(data, i))
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
