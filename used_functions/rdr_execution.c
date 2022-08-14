/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 15:22:28 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/08/14 04:16:55 by ykhadiri         ###   ########.fr       */
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
	t_redirection	*red;

	red = cmd->redirection;
	if (!red)
		return (0);
	else if (found_rdr(cmd))
	{
		while (red)
		{
			if (red->type == 4)
				output_rdr_std_appnd(data, cmd, O_APPEND);
			else if (red->type == 5)
				input_rdr_std_appnd(data, cmd);
			else if (red->type == 6)
				output_rdr_std_appnd(data, cmd, O_TRUNC);
			red = red->next;
		}
		return (1);
	}	
	return (0);
}
