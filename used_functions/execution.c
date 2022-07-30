/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouqssi <hbouqssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:49:51 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/07/30 03:13:39 by hbouqssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_quotes(char *cmd)
{
	int		i;
	int		j;
	char	quote_symbol;
	char	*res;
	char	*tmp;
	char	*command;

	res = malloc(sizeof(char) * 1000);
	command = malloc(sizeof(char) * 1000);
	i = 0;
	while (cmd[i])
	{
		j = 0;
		if (cmd[i] == '"' || cmd[i] == '\'')
		{
			quote_symbol = cmd[i];
			i++;
			while (cmd[i])
			{
				if (cmd[i] == quote_symbol)
				{
					i++;
					command[j] = '\0';
					quote_symbol = 0;
					break;
				}
				command[j++] = cmd[i++];
			}
			if (quote_symbol == 0)
				j = 0;
			else
			{
				write(2, RED"Syntax Error\n", 21);
				return (0);
			}
		}
		else
		{
			while (cmd[i] && cmd[i] != '\'' && cmd[i] != '"')
				command[j++] = cmd[i++];
		}
		tmp = res;
		free(res);
		res = ft_strjoin(tmp, command);
	}
	return (res);
}

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
			cmd->cmd_array[i++] = check_quotes(cmdline->cmd);
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
	free(data->tokens);
	execution_other_builtins(data, cmd);
}
