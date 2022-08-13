/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_rdr_std_appnd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 11:06:20 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/08/13 18:35:43 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_rdr(t_data *data, t_command *tmp)
{
	if (check_builts(tmp->cmd_array[0]))
		builtins_execution(data, tmp);
	else
		execution_other_builtins(data, tmp);
}

void	output_rdr_std_appnd(t_data *data, t_command *cmd, int flag)
{
	int				fd;
	t_command		*tmp;
	t_redirection	*red;

	tmp = cmd;
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
	exec_rdr(data, tmp);
	dup2(data->g_std._stdout, 1);
	close(fd);
}
