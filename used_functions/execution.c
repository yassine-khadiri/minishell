/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouqssi <hbouqssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:49:51 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/08/02 02:09:23 by hbouqssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_remove_dollars(t_data *data, char *cmd)
{
	char	*var_name;
	char	*res;
	int		i;
	int		j;
	int		dollar_counter;

	i = 0;
	var_name = malloc(sizeof(char) * 1000);
	res = malloc(sizeof(char) * ft_strlen(cmd));
	while (cmd[i])
	{
			j = 0;
			dollar_counter = 0;
			while (cmd[i] && cmd[i] == '$')
			{
				dollar_counter++;
				var_name[j++] = cmd[i++];
			}
			while (cmd[i] && cmd[i] != '$')
				var_name[j++] = cmd[i++];
			var_name[j] = '\0';
			if (dollar_counter > 1 || dollar_counter == 0
				|| (dollar_counter == 1 && !var_name[dollar_counter]))
				res = ft_strjoin(res, var_name);
			else
				res = ft_strjoin(res, check_res(var_name, data->env));
	}
	res[ft_strlen(res)] = '\0';
	return (res);
}

char	*check_quotes(char *cmd)
{
	int		i;
	int		j;
	char	quote_symbol;
	char	*res;
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
		res = ft_strjoin(res, command);
	}
	return (res);
}

int	fill_struct(t_data *data, t_command *cmd)
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
			// if (!ft_strcmp(cmdline->cmd, " "))
			// 	cmdline = cmdline->next;
		
				cmd->cmd_array[i++] = check_remove_dollars(data, cmdline->cmd);
				cmdline = cmdline->next;
		}
		cmd->cmd_array[i] = NULL;
		cmd = cmd->next;
	}
	return (0);
}


void	execution(t_data *data, t_command *cmd)
{
	int	i = 0;

	fill_struct(data, cmd);
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
