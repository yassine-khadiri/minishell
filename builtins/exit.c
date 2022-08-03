/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 18:27:51 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/08/03 19:21:46 by ykhadiri         ###   ########.fr       */
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

int	ft_exit(t_command *cmd)
{
	int	i;

	i = 0;
	printf("exit\n");
	while (cmd->cmd_array[++i])
	{
		if (!ft_isnumber(cmd->cmd_array[i]))
			printf(RED "minishell: exit: %s: numeric argument required\n",
				cmd->cmd_array[i]);
		if (!ft_strcmp(cmd->cmd_array[i], " "))
			++i;
	}
	return (0);
}
