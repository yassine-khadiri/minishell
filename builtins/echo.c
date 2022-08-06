/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 12:28:52 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/08/06 18:09:49 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_dash_n(t_data *data, t_command *cmd, int i)
{
	int	j;

	while (cmd->cmd_array[i])
	{
		if (!ft_strcmp(cmd->cmd_array[i], "-n"))
			i++;
		if (cmd->cmd_array[i] && cmd->cmd_array[i][0] == '-'
			&& cmd->cmd_array[i][1] == 'n')
		{
			j = 0;
			while (cmd->cmd_array[i][++j] == 'n')
				;
			if (ft_strlen(cmd->cmd_array[i]) == j)
				i++;
			else
				break ;
		}
		else
			break ;
	}
	if (i != 1)
		data->mode = '\0';
	return (i);
}

int	ft_echo(t_data *data, t_command *cmd, int index)
{
	int	len;

	data->mode = '\n';
	len = 0;
	index++;
	if (!cmd->cmd_array[index])
	{
		printf("\n");
		return (0);
	}
	index = check_dash_n(data, cmd, index);
	while (cmd->cmd_array[index])
	{
		if (cmd->cmd_array[index + 1])
			printf("%s ", cmd->cmd_array[index]);
		else
			printf("%s", cmd->cmd_array[index]);
		index++;
	}
	printf("%c", data->mode);
	return (1);
}
