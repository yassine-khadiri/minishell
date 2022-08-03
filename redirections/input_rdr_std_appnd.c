/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_rdr_std_appnd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 10:33:56 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/07/31 17:49:30 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	input_rdr_std_appnd(t_data *data, t_command *cmd)
{
	int				fd;
	t_redirection	*red;

	red = cmd->redirection;
	while (red)
	{
		fd = open(red->file, O_RDONLY, 0777);
		if (fd == -1)
		{
			write(2, RED "minishell: ", 19);
			write(2, &red->file, ft_strlen(red->file));
			write(2, ": No such file or directory\n", 28);
			return ;
		}
		red = red->next;
	}
	dup2(fd, 0);
	exec(data, cmd);
	dup2(data->g_std._stdin, 0);
	close(fd);
}
