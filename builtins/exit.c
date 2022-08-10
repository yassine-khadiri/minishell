/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 18:27:51 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/08/10 01:51:57 by ykhadiri         ###   ########.fr       */
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
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	if (i == 0)
		g_dollar_question = ft_atoi(cmd->cmd_array[1]);
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
			printf(RED "minishell: exit: %s: numeric argument required\n",
				cmd->cmd_array[i]);
			break ;
		}
		else
			return (set_res(cmd, i));
	}
	return (0);
}
