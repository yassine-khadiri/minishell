/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_rdr_std_appnd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 10:33:56 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/07/14 16:20:06 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	input_rdr_std_appnd(t_data *data)
{
	int	fd;

	get_file_name(data);
	fd = open(data->fd_name, O_RDONLY, 0777);
	if (fd == -1)
	{
		printf(RED "minishell: %s: No such file or directory\n", data->fd_name);
		return ;
	}
	dup2(fd, 0);
	exec(data);
	dup2(data->g_std._stdin, 0);
	close(fd);
}
