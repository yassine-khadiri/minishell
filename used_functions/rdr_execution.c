/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 15:22:28 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/07/20 18:49:52 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*verify_rdr(t_data *data)
{
	if (!data->tokens)
		return (0);
	while (data->tokens)
	{
		if (!ft_strcmp(data->tokens->value, "<")
			|| !ft_strcmp(data->tokens->value, ">")
			|| !ft_strcmp(data->tokens->value, ">>")
			|| !ft_strcmp(data->tokens->value, "<<"))
			return (data->tokens->value);
		else
			data->tokens = data->tokens->next;
	}
	return (0);
}

int	rdr_execution(t_data *data, t_command *cmd)
{
	bool	check_exec;

	check_exec = false;
	if (verify_rdr(data))
	{
		check_exec = true;
		if (!ft_strcmp(verify_rdr(data), "<"))
			input_rdr_std_appnd(data, cmd);
		else if (!ft_strcmp(verify_rdr(data), ">"))
			output_rdr_std_appnd(data, cmd, O_TRUNC);
		else if (!ft_strcmp(verify_rdr(data), ">>"))
			output_rdr_std_appnd(data, cmd, O_APPEND);
		// else if (!ft_strcmp(verify_rdr(data, cmd), "<<"))
		// 	output_rdr_std_appnd(data, O_APPEND);
	}
	return (check_exec);
}
