/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_rdr_std_appnd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 11:06:20 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/08/10 01:48:49 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	output_rdr_std_appnd(t_data *data, t_command *cmd, int flag)
{
	int				fd;
	t_redirection	*red;

	red = cmd->redirection;
	while (red)
	{
		if (flag == 0x0008)
			fd = open(red->file,
					O_CREAT | O_RDWR | O_APPEND, 0777);
		else
			fd = open(red->file, O_CREAT | O_RDWR | O_TRUNC, 0777);
		if (fd == -1)
		{
			perror(ft_strjoin("minishell: ", red->file));
			return ;
		}
		red = red->next;
	}
	dup2(fd, 1);
	execution_other_builtins(data, cmd);
	dup2(data->g_std._stdout, 1);
	close(fd);
}
