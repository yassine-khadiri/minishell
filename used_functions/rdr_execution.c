/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 15:22:28 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/08/04 00:12:34 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*verify_rdr(t_data *data)
{
	t_token	*tokens;

	tokens = data->tokens;
	if (!tokens)
		return (0);
	while (tokens)
	{
		if (!ft_strcmp(tokens->value, "<") || !ft_strcmp(tokens->value, ">")
			|| !ft_strcmp(tokens->value, ">>") || !ft_strcmp(tokens->value,
				"<<"))
			return (tokens->value);
		else
			tokens = tokens->next;
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
			input_rdr_std_appnd(data, cmd, "input");
		else if (!ft_strcmp(verify_rdr(data), "<<"))
			input_rdr_std_appnd(data, cmd, "herdoc");
		else if (!ft_strcmp(verify_rdr(data), ">"))
			output_rdr_std_appnd(data, cmd, O_TRUNC);
		else if (!ft_strcmp(verify_rdr(data), ">>"))
			output_rdr_std_appnd(data, cmd, O_APPEND);
	}
	return (check_exec);
}
