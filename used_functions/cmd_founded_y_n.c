/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_founded_y_n.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:42:07 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/06/21 18:15:23 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pipe_founded(t_data *data)
{
	while (*data->spllited_cmd_buf)
	{
		if (!ft_strcmp(*data->spllited_cmd_buf, "|"))
			return (1);
		data->spllited_cmd_buf++;
	}
	return (0);
}

int	cmd_founded_y_n(t_data *data)
{
	char	*path;

	while (*data->splitted_env)
	{
		if (!ft_strcmp(data->spllited_cmd_buf[0], "export")
			|| !ft_strcmp(data->spllited_cmd_buf[0], "unset"))
			return (0);
		path = ft_strjoin(*data->splitted_env, "/");
		path = ft_strjoin(path, data->spllited_cmd_buf[0]);
		if (access(path, X_OK) == -1)
			data->splitted_env++;
		else
			return (0);
	}
	printf(WHT"minishell : %s: command not found\n"BLU, *data->spllited_cmd_buf);
	return (-1);
}
