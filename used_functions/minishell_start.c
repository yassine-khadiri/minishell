/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_start.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:38:27 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/08/10 01:46:42 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	minishel_start(t_data *data)
{
	t_command	*cmd;

	cmd = NULL;
	while (1)
	{
		ft_ctl_c();
		ft_ctl_slash();
		data->command_buf = readline(BLU "minishell> " WHT);
		ft_ctl_d(data);
		if (ft_strlen(data->command_buf) > 0)
		{
			data->tokens = ft_tokenizer(&data->tokens, data->command_buf);
			final_tokens(&data->tokens, data->env);
			if (data->tokens)
			{
				data->syntax_res = syntax_errors(data->tokens);
				if ((data->syntax_res) != 1)
				{
					cmd = ft_parse(data, data->tokens);
					execution(data, cmd);
				}
			}
			add_history(data->command_buf);
		}
		free(data->command_buf);
	}
	clear_history();
}
