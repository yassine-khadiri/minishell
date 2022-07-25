/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouqssi <hbouqssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:49:51 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/07/25 19:52:46 by hbouqssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fill_struct(t_command *cmd)
{
	int			i;
	t_cmdline	*cmdline;

	while (cmd)
	{
		cmdline = cmd->cmdline;
		cmd->cmd_array = malloc(sizeof(char *) * (ft_lstsize(cmdline) + 1));
		if (!cmd->cmd_array)
			return (0);
		i = 0;
		while (cmdline)
		{
			cmd->cmd_array[i++] = cmdline->cmd;
			cmdline = cmdline->next;
		}
		cmd->cmd_array[i] = NULL;
		cmd = cmd->next;
	}
	return (0);
}

void	execution(t_data *data, t_command *cmd)
{
	int	i;

	fill_struct(cmd);
	i = 0;
	while (cmd->cmd_array[i])
	{
		if (!ft_strcmp(cmd->cmd_array[i], "$?"))
		{
			printf("%d", g_dollar_question);
			g_dollar_question = 0;
			i++;
		}
		i++;
	}
	if (cmd_founded_y_n(data, cmd) == -1
		|| (pipe_founded(data->tokens) && ft_pipe(data, cmd))
		|| rdr_execution(data, cmd)
		|| builtins_execution(data, cmd))
		return ;
	if (builtins_execution(data, cmd))
		return ;
	execution_other_builtins(data, cmd);
}
