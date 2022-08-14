/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 15:22:28 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/08/14 21:30:01 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	found_rdr(t_command *cmd)
{
	t_redirection	*tmp;

	tmp = cmd->redirection;
	int	number;
	if (!tmp)
		return (0);
	else if (tmp->type == 4) // append
		number = 4;
	else if (tmp->type == 5) // stdin && herdoc (< && <<)
		number = 5;
	else if (tmp->type == 6) // stdout
		number = 6;
	else
		number = 0;
	return (number);
}

int	rdr_execution(t_data *data, t_command *cmd)
{
	bool getres1 = false, getres2 = false;
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
				getres1 = true;	
				output_rdr_std_appnd(data, cmd, red, O_APPEND);
			}
			else if (red->type == 5)
			{
				getres2 = true;	
				
				input_rdr_std_appnd(data, cmd, red);
			}
			else if (red->type == 6)
			{
				getres1 = true;	
				output_rdr_std_appnd(data, cmd, red, O_TRUNC);
			}
			red = red->next;
		}
		dup2(data->g_std._redin, 0);
		dup2(data->g_std._redout, 1);
		exec_rdr(data, tmp);
		dup2(data->g_std._stdin, 0);
		dup2(data->g_std._stdout, 1);
		// if (getres1)
		// 	close(data->g_std._redin);
		// close(data->g_std._redout);
		return (1);
	}	
	return (0);
}
