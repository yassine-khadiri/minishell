/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_rdr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 18:37:26 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/07/15 15:43:56 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*verify_rdr(t_data *data)
{
	int	i;

	i = 0;
	if (!data->cmd->command)
		return (0);
	while (data->cmd->command[i])
	{
		if (!ft_strcmp(data->cmd->command[i], "<"))
			return ("<");
		else if (!ft_strcmp(data->cmd->command[i], ">"))
			return (">");
		else if (!ft_strcmp(data->cmd->command[i], ">>"))
			return (">>");
		i++;
	}
	return (0);
}
