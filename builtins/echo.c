/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouqssi <hbouqssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 12:28:52 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/07/25 21:59:21 by hbouqssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		g_index;

char	*case_1(char **env, t_command *cmd, int index, int i, char *str)
{
	char	*mssj;
	int		j;

	mssj = ft_strdup("");
	i++;
	while (cmd->cmd_array[index][i])
	{
		j = 0;
		while (cmd->cmd_array[index][i] && cmd->cmd_array[index][i] != '$')
			str[j++] = cmd->cmd_array[index][i++];
		str[j] = '\0';
		mssj = ft_strjoin(mssj, check_res(str, env));
		i++;
	}
	g_index = i;
	return (mssj);
}

char	*case_2(t_command *cmd, int index, int i)
{
	char	*mssj;
	int		j;

	mssj = ft_strdup("");
	j = 0;
	while (cmd->cmd_array[index][i])
	{
		if (cmd->cmd_array[index][i] == '$' && cmd->cmd_array[index][i] != '$')
		{
			mssj[j] = '\0';
			break ;
		}
		mssj[j++] = cmd->cmd_array[index][i++];
	}
	g_index = i;
	return (mssj);
}

char	*case_3(t_command *cmd, int index, int i)
{
	char	*mssj;
	int		j;

	mssj = ft_strdup("");
	j = 0;
	while (cmd->cmd_array[index][i])
	{
		if (cmd->cmd_array[index][i] == '$' && cmd->cmd_array[index][i
			+ 1] != '$')
			break ;
		mssj[j++] = cmd->cmd_array[index][i++];
	}
	g_index = i;
	mssj[j] = '\0';
	return (mssj);
}

int	check_dash_n(t_data *data, t_command *cmd, int i)
{
	int	j;

	(void)data;
	while (cmd->cmd_array[i])
	{
		if (!ft_strcmp(cmd->cmd_array[i], "-n"))
			i++;
		if (cmd->cmd_array[i][0] == '-' && cmd->cmd_array[i][1] == 'n')
		{
			j = 0;
			while (cmd->cmd_array[i][++j] == 'n')
				;
			if (ft_strlen(cmd->cmd_array[i]) == j)
				i++;
			else
				break ;
		}
		else
			break ;
	}
	if (i != 1)
		data->mode = '\0';
	return (i);
}

int	ft_echo(t_data *data, t_command *cmd, int index)
{
	char	*string;
	int		len;
	char	*mssj;

	data->mode = '\n';
	len = 0;
	index++;
	if (!cmd->cmd_array[index])
	{
		printf("\n");
		return (0);
	}
	index = check_dash_n(data, cmd, index);
	while (cmd->cmd_array[index])
	{
		mssj = ft_strdup("");
		string = malloc(sizeof(char) * ft_strlen(cmd->cmd_array[index]));
		if (!string)
			return (0);
		g_index = 0;
		while (cmd->cmd_array[index][g_index])
		{
			if (cmd->cmd_array[index][g_index] == '$'
				&& cmd->cmd_array[index][g_index + 1] != '$')
				mssj = ft_strjoin(mssj, case_1(data->env, cmd, index, g_index,
							string));
			else if (cmd->cmd_array[index][g_index] == '$'
					&& cmd->cmd_array[index][g_index + 1] == '$')
				mssj = ft_strjoin(mssj, case_2(cmd, index, g_index));
			else
				mssj = ft_strjoin(mssj, case_3(cmd, index, g_index));
		}
		printf("%s ", mssj);
		index++;
	}
	printf("%c", data->mode);
	return (1);
}
