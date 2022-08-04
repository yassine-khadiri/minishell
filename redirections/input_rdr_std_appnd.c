/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_rdr_std_appnd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 10:33:56 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/08/04 04:33:36 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	handle_herdoc()
// {

// }

void	input_rdr_std_appnd(t_data *data, t_command *cmd, char *str)
{
	int				fd;
	t_redirection	*red;

	red = cmd->redirection;
	while (red)
	{
		if (!ft_strcmp(str, "input"))
			fd = open(red->file, O_RDONLY, 0777);
		else
		{
			// file_path = malloc(sizeof(char) * (ft_strlen(red->file) + 6));
			// file_path = ft_strjoin("/tmp/", );
			// puts(file_path);
			red->file = "/tmp/yh";
			// while (!ft_strcmp(""))
			fd = open("/tmp/yh", O_CREAT | O_RDWR, 0777);
			write(fd, data->buffer_herdoc, ft_strlen(data->buffer_herdoc));
		}
		if (fd == -1)
		{
			perror(ft_strjoin("minishell: ", red->file));
			return ;
		}
		red = red->next;
	}
	dup2(fd, 0);
	exec(data, cmd);
	dup2(data->g_std._stdin, 0);
	close(fd);
}
