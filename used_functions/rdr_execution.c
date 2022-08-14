/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 15:22:28 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/08/14 22:32:40 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	found_rdr(t_command *cmd)
{
	t_redirection	*tmp;
	int				file_number;

	tmp = cmd->redirection;
	if (!tmp)
		return (0);
	else if (tmp->type == 4)
		file_number = 4;
	else if (tmp->type == 5)
		file_number = 5;
	else if (tmp->type == 6)
		file_number = 6;
	else
		file_number = 0;
	return (file_number);
}

int	rdr_execution(t_data *data, t_command *cmd)
{
	t_redirection	*red;
	t_command		*tmp;

	tmp = cmd;
	red = cmd->redirection;
	if (!red)
		return (0);
	else if (found_rdr(cmd))
	{
		while (red)
		{
			if (red->type == 4)
			{
				// append 
				if (output_rdr_std_appnd(data, cmd, red, O_TRUNC) == -1)
					break ;
			}
			else if (red->type == 5)
			{
				// stdin && herdoc (< && <<)
				if (input_rdr_std_appnd(data, cmd, red) == -1)
					break ;
			}
			else if (red->type == 6)
			{
				// stdout
				if (output_rdr_std_appnd(data, cmd, red, O_TRUNC) == -1)
					break ;
			}
			red = red->next;
		}
		if (data->fd_reds != -1)
		{	
			dup2(data->g_std._redin, 0);
			dup2(data->g_std._redout, 1);
			exec_rdr(data, tmp);
			dup2(data->g_std._stdin, 0);
			dup2(data->g_std._stdout, 1);
			close(data->g_std._redin);
			close(data->g_std._redout);
		}
		return (1);
	}	
	return (0);
}
