/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 18:27:51 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/08/16 22:05:06 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	while (ft_isdigit(str[i]))
		i++;
	if (ft_strlen(str) == i)
		return (1);
	return (0);
}

int	set_res(t_command *cmd, int index)
{
	int	i;

	i = 0;
	while (cmd->cmd_array[++index])
		i++;
	if (i > 1)
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		return (1);
	}
	if (i == 0)
		g_tools.g_dollar_question = ft_atoi(cmd->cmd_array[1]);
	return (0);
}

int	ft_exit(t_command *cmd)
{
	int	i;

	i = 0;
	printf("exit\n");
	while (cmd->cmd_array[++i])
	{
		if (!ft_isnumber(cmd->cmd_array[i]))
		{
			write(2, RED"minishell: exit: ", 25);
			write(2, cmd->cmd_array[i], ft_strlen(cmd->cmd_array[i]));
			write(2, ": numeric argument required\n"BLU, 35);
			break ;
		}
		else
			return (set_res(cmd, i));
	}
	return (0);
}
