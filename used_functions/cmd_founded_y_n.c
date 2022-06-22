/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_founded_y_n.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:42:07 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/06/22 14:34:55 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int pipe_founded(t_data *data)
{
	while (*data->spllited_cmd_buf)
	{
		if (!ft_strcmp(*data->spllited_cmd_buf, "|"))
			return (1);
		data->spllited_cmd_buf++;
	}
	return (0);
}

int cmd_founded_y_n(t_data *data)
{
	char	*path;
	int 	result;
	int 	i;

	path = NULL;
	result = -1;
	i = 0;
	while (data->splitted_path[i])
	{
		if (!ft_strcmp(data->spllited_cmd_buf[0], "export")
		|| !ft_strcmp(data->spllited_cmd_buf[0], "unset"))
			return (0);
		path = ft_strjoin(data->splitted_path[i], "/");
		path = ft_strjoin(path, data->spllited_cmd_buf[0]);
		if (access(path, X_OK) != -1)
		{
			result = 0;
			break;
		}
		i++;
	}
	if (result == -1)
		printf(WHT "minishell : %s: command not found\n" BLU, data->spllited_cmd_buf[0]);
	return (free(path), result);
}
