/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_rdr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 18:37:26 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/07/14 16:20:07 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*verify_rdr(t_data *data)
{
	int	i;

	i = 0;
	if (!data->spllited_cmd_buf)
		return (0);
	while (data->spllited_cmd_buf[i])
	{
		if (!ft_strcmp(data->spllited_cmd_buf[i], "<"))
			return ("<");
		else if (!ft_strcmp(data->spllited_cmd_buf[i], ">"))
			return (">");
		else if (!ft_strcmp(data->spllited_cmd_buf[i], ">>"))
			return (">>");
		i++;
	}
	return (0);
}
