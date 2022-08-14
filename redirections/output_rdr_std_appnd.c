/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_rdr_std_appnd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 11:06:20 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/08/14 22:27:00 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_rdr(t_data *data, t_command *tmp)
{
	if (check_builts(tmp->cmd_array[0]))
		builtins_execution(data, tmp);
	else
		execution_other_builtins(data, tmp);
}

int	output_rdr_std_appnd(t_data *data, t_command *cmd, t_redirection *red, int flag)
{
	t_command		*tmp;

	tmp = cmd;
	while (red)
	{
		if (red->type == 4 || red->type == 6)
		{
			if (flag == 0x0008)
				data->fd_reds = open(red->file,
						O_CREAT | O_RDWR | O_APPEND, 0777);
			else
				data->fd_reds = open(red->file, O_CREAT | O_RDWR | O_TRUNC, 0777);
			if (data->fd_reds == -1)
			{
				perror(ft_strjoin("minishell: ", red->file));
				return (-1);
			}
		}
		else
			return (0);
		red = red->next;
	}
	data->g_std._redout = data->fd_reds;
	return (1);
}
