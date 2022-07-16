/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 15:22:28 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/07/16 23:16:37 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	rdr_execution(t_data *data)
{
	if (verify_rdr(data))
	{
		if (!ft_strcmp(verify_rdr(data), "<"))
			input_rdr_std_appnd(data);
		else if (!ft_strcmp(verify_rdr(data), ">"))
			output_rdr_std_appnd(data, O_TRUNC);
		else if (!ft_strcmp(verify_rdr(data), ">>"))
			output_rdr_std_appnd(data, O_APPEND);
		else if (!ft_strcmp(verify_rdr(data), "<<"))
			output_rdr_std_appnd(data, O_APPEND);
		else
			return (0);
	}
	return (1);
}
