/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 16:42:37 by hbouqssi          #+#    #+#             */
/*   Updated: 2022/08/16 22:15:32 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec1_launcher(t_data *data, t_command *cmd, int i)
{
	int	in;

	in = i;
	while (cmd)
	{
		if (cmd->next != NULL)
			data->fd[1] = data->pipes[i][1];
		else
			data->fd[1] = 1;
		data->pid1 = fork();
		data->pids[i] = data->pid1;
		if (data->pid1 < 0)
			return (0);
		if (data->pid1 == 0)
			exec1(data, cmd, in);
		if (in != 0)
			close(in);
		if (data->fd[1] != 1)
			close(data->fd[1]);
		in = data->pipes[i][0];
		cmd = cmd->next;
		++i;
	}
	return (1);
}

int	pipe_initializer(t_data *data, t_command *cmd)
{
	int	i;

	i = 0;
	data->nb_cmds = get_nb_cmds(cmd);
	data->pids = malloc(sizeof(int) * data->nb_cmds);
	data->pipes = malloc(sizeof(int *) * data->nb_cmds);
	if (!data->pids || !data->pipes)
		return (0);
	add(&g_tools.garbage, data->pids);
	add(&g_tools.garbage, data->pipes);
	while (i < data->nb_cmds)
	{
		data->pipes[i] = malloc(sizeof(int) * 2);
		if (!data->pipes[i])
			return (0);
		add(&g_tools.garbage, data->pipes[i]);
		i++;
	}
	return (1);
}

int	ft_pipe(t_data *data, t_command *cmd)
{
	t_command	*tmp;
	int			i;

	i = 0;
	tmp = cmd;
	pipe_initializer(data, tmp);
	i = 0;
	while (cmd->next)
	{
		pipe(data->pipes[i]);
		cmd = cmd->next;
		++i;
	}
	cmd = tmp;
	exec1_launcher(data, cmd, 0);
	cmd = tmp;
	i = 0;
	while (cmd)
	{
		waitpid(data->pids[i], NULL, 0);
		cmd = cmd->next;
		++i;
	}
	return (1);
}
