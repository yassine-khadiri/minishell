/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 15:22:28 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/08/16 03:27:29 by ykhadiri         ###   ########.fr       */
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

void	check_red_type(t_data *data, t_command *cmd)
{
	t_command		*cmds;
	t_redirection	*red;

	red = cmd->redirection;
	cmds = cmd;
	while (red)
	{
		if (red->type == 4)
		{
			if (output_rdr_std_appnd(data, cmds, red, O_APPEND) == -1)
				break ;
		}
		else if (red->type == 5)
		{
			if (input_rdr_std_appnd(data, cmds, red) == -1)
				break ;
		}
		else if (red->type == 6)
		{
			if (output_rdr_std_appnd(data, cmds, red, O_TRUNC) == -1)
				break ;
		}
		red = red->next;
	}
}

void	dup_and_close_files(t_data *data, t_command *tmp)
{
	if (data->g_std._redin != 0)
		dup2(data->g_std._redin, 0);
	if (data->g_std._redout != 1)
		dup2(data->g_std._redout, 1);
	exec_rdr(data, tmp);
	dup2(data->g_std._stdin, 0);
	dup2(data->g_std._stdout, 1);
	if (data->g_std._redin != 0)
		close(data->g_std._redin);
	if (data->g_std._redout != 1)
		close(data->g_std._redout);
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
		check_red_type(data, cmd);
		if (data->fd_reds != -1)
			dup_and_close_files(data, tmp);
		return (1);
	}	
	return (0);
}
