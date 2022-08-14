/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:49:51 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/08/14 17:20:37 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	show_err_msg(t_command *cmd)
{
	write(2, RED "minishell: ", 19);
	write(2, cmd->cmd_array[0], ft_strlen(cmd->cmd_array[0]));
	write(2, ": command not found\n" BLU, 28);
	g_tools.g_dollar_question = 127;
}

int	error_mssj(t_data *data, char *cmd)
{
	if (!data->splitted_path)
	{
		write(2, RED "minishell: ", 19);
		write(2, cmd, ft_strlen(cmd));
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

int	check_builts(char *cmd)
{
	if (!ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

void	execution(t_data *data, t_command *cmd)
{
	fill_struct(cmd);
	data->splitted_path = ft_get_spllited_path_env(data);
	if (check_builts(cmd->cmd_array[0])
		&& !pipe_founded(data->tokens)
		&& !found_rdr(cmd))
	{
		builtins_execution(data, cmd);
		return ;
	}
	else
	{
		if (cmd_founded_y_n(data, cmd) == -1
			|| (pipe_founded(data->tokens)
				&& ft_pipe(data, cmd)) || rdr_execution(data, cmd)
			|| execution_other_builtins(data, cmd))
			return ;
	}
}
