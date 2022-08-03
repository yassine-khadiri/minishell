/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_start.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouqssi <hbouqssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:38:27 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/08/03 03:23:26 by hbouqssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_cmd(t_command *cmd, t_token *tokens)
{
	void	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(((t_token *)tmp)->value);
		free(tmp);
	}
	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
}

void	minishel_start(t_data *data)
{
	t_command	*cmd;

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
			// while(data->tokens != NULL)
			// {
			// 	printf("[ type :  |%d| ]  \n", data->tokens->type);
			// 	printf("[ Value : |%s| ]  \n", data->tokens->value);
			// 	printf("\n");
			// 	data->tokens = data->tokens->next;
			// }
			if (data->tokens)
			{
				data->syntax_res = syntax_errors(data->tokens);
				if ((data->syntax_res) != 1)
				{
					cmd = ft_parse(data->tokens);
					execution(data, cmd);
				}
			}
			add_history(data->command_buf);
		}
	}
	// free(data->command_buf);
	// free_cmd(cmd, data->tokens);
}
