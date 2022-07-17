/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_rdr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 18:37:26 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/07/17 18:50:19 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*verify_rdr(t_data *data)
{
	int	i;

	i = 0;
	if (!data->arr_cmds)
		return (0);
	while (data->arr_cmds[i])
	{
		if (!ft_strcmp(data->arr_cmds[i], "<"))
			return ("<");
		else if (!ft_strcmp(data->arr_cmds[i], ">"))
			return (">");
		else if (!ft_strcmp(data->arr_cmds[i], ">>"))
			return (">>");
		i++;
	}
	return (0);
}
