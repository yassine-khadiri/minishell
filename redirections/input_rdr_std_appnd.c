/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_rdr_std_appnd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 10:33:56 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/07/30 00:52:03 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	input_rdr_std_appnd(t_data *data, t_command *cmd)
{
	int	fd;

	while (cmd->redirection)
	{
		fd = open(cmd->redirection->file, O_RDONLY, 0777);
		if (fd == -1)
		{
			printf(RED "minishell: %s: No such file or directory\n",
				cmd->redirection->file);
			return ;
		}
		cmd->redirection = cmd->redirection->next;
	}
	dup2(fd, 0);
	exec(data, cmd);
	dup2(data->g_std._stdin, 0);
	close(fd);
}
