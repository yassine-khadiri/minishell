/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_rdr_std_appnd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 10:33:56 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/08/14 22:34:31 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	input_rdr_std_appnd(t_data *data, t_command *cmd, t_redirection *red)
{
	t_command		*tmp;

	tmp = cmd;
	while (red)
	{
		if (data->fd_h)
		{
			data->fd_reds = data->fd_h;
			break ;
		}
		else if (red->type == 5)
		{
			data->fd_reds = open(red->file, O_RDONLY, 0777);
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
	data->g_std._redin = data->fd_reds;
	return (1);
}
