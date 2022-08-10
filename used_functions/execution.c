/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:49:51 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/08/10 01:21:42 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	error_mssj(t_data *data, t_command *cmd)
{
	if (!data->splitted_path)
	{
		write(2, RED "minishell: ", 19);
		write(2, cmd->cmd_array[0], ft_strlen(cmd->cmd_array[0]));
		write(2, ": No such file or directory\n" BLU, 36);
		return (1);
	}
	return (0);
}

int	fill_struct(t_command *cmd)
{
	int			i;
	t_cmdline	*cmdline;

	while (cmd)
	{
		cmdline = cmd->cmdline;
		cmd->cmd_array = malloc(sizeof(char *) * (ft_lstsize(cmdline) + 1));
		add(&g_tools.garbage, cmd->cmd_array);
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
	fill_struct(cmd);
	data->splitted_path = ft_get_spllited_path_env(data);
	if (builtins_execution(data, cmd))
		return ;
	if (cmd_founded_y_n(data, cmd) == -1 || (pipe_founded(data->tokens)
			&& ft_pipe(data, cmd)) || rdr_execution(data, cmd))
		return ;
	if (!execution_other_builtins(data, cmd))
		return ;
}
