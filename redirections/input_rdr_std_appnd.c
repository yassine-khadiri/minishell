/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_rdr_std_appnd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouqssi <hbouqssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 10:33:56 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/07/30 01:41:39 by hbouqssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	input_rdr_std_appnd(t_data *data, t_command *cmd)
{
	int	fd;
	t_redirection *red;

	red = cmd->redirection;
	while (red)
	{
		fd = open(red->file, O_RDONLY, 0777);
		if (fd == -1)
		{
			printf(RED "minishell: %s: No such file or directory\n",
				red->file);
			return ;
		}
		red = red->next;
	}
	dup2(fd, 0);
	exec(data, cmd);
	dup2(data->g_std._stdin, 0);
	close(fd);
}
