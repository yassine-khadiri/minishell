/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_rdr_std_appnd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 10:33:56 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/08/14 04:15:41 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	input_rdr_std_appnd(t_data *data, t_command *cmd)
{
	int				fd;
	t_command		*tmp;
	t_redirection	*red;

	red = cmd->redirection;
	tmp = cmd;
	while (red)
	{
		if (data->fd_h)
		{
			fd = data->fd_h;
			break ;
		}
		else
		{
			fd = open(red->file, O_RDONLY, 0777);
			if (fd == -1)
			{
				perror(ft_strjoin("minishell: ", red->file));
				return ;
			}
		}
		red = red->next;
	}
	dup2(fd, 0);
	exec_rdr(data, tmp);
	dup2(data->g_std._stdin, 0);
	close(fd);
}
