/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_start.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouqssi <hbouqssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:38:27 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/07/28 20:19:40 by hbouqssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	minishel_start(t_data *data)
{
	t_command	*cmd;

	while (1)
	{
		// sleep(5);
		ft_ctl_c();
		ft_ctl_slash();
		data->command_buf = readline(BLU "minishell> " WHT);
		ft_ctl_d(data);
		if (ft_strlen(data->command_buf) > 0)
		{
			data->tokens = ft_tokenizer(&data->tokens, data->command_buf);
			if (data->tokens)
			{
				data->syntax_res = syntax_errors(data->tokens);
				if ((data->syntax_res) != 1)
				{
					cmd = ft_parse(data->tokens, data->lenv);
					execution(data, cmd);
				}
				add_history(data->command_buf);
			}
		}
	}
}
