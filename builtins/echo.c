/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 12:28:52 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/07/23 01:27:03 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_index;

char	*get_val_env_var1(char **env, char *env_variable)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strcmp(extract_var_name(env[i]), env_variable))
			return (env[i] + ft_strlen(env_variable) + 1);
		i++;
	}
	return (NULL);
}

char	*check_res(char *var_name, char **env)
{
	if (get_val_env_var1(env, var_name))
		var_name = get_val_env_var1(env, var_name);
	else
		var_name = "";
	return (var_name);
}

void	print_dollar(int dollar_count, char *dollars_arr)
{
	int	i;

	i = 0;
	while (dollars_arr[i] && dollar_count > 0)
	{
		if (dollar_count == 1)
		{
			printf("$\n");
			break ;
		}
		else if (!dollar_count)
		{
			printf("\n");
			break ;
		}
		printf("%d", getpid());
		dollar_count -= 2;
		i++;
	}
}

void	check_dollars(char *str)
{
	int		i;
	int		dollar_count;
	char	dollars_arr[1000];

	i = 0;
	dollar_count = 0;
	while (str[i])
	{
		if ((str[i] == '$' && str[i + 1] == '$') || (str[i] == '$' && str[i
				+ 1] == '\0'))
		{
			dollars_arr[i] = '$';
			dollar_count++;
		}
		i++;
	}
	dollars_arr[i] = '\0';
	print_dollar(dollar_count, dollars_arr);
}

void	print_mssj(char *str, char mode)
{
	if (mode == '\0')
		printf("%s", str);
	else if (mode == '\n')
		printf("%s\n", str);
}

char	*case_1(char **env, t_command *cmd, int index, int i, char *str)
{
	char	*mssj;
	int		j;

	mssj = ft_strdup("");
	i++;
	while (cmd->cmd_array[index][i])
	{
		j = 0;
		while (cmd->cmd_array[index][i]
			&& cmd->cmd_array[index][i] != '$')
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
		if (cmd->cmd_array[index][i] == '$'
			&& cmd->cmd_array[index][i] != '$')
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
		if (cmd->cmd_array[index][i] == '$'
			&& cmd->cmd_array[index][i + 1] != '$')
			break ;
		mssj[j++] = cmd->cmd_array[index][i++];
	}
	g_index = i;
	mssj[j] = '\0';
	return (mssj);
}

int	check_dash_n(t_command *cmd, int i)
{
	int	j;
	
	while (cmd->cmd_array[i])
	{
		while (!ft_strcmp(cmd->cmd_array[i], "-n"))
			i++;
		if (cmd->cmd_array[i][0] == '-')
		{
			j = 0;
			while (cmd->cmd_array[i][++j] == 'n');
			if (ft_strlen(cmd->cmd_array[i]) == j + 1)
				i++;
		}
		if (i != 1)
			return (i);
	}
	return (0);
}

int	ft_echo(t_data *data, t_command *cmd, int index)
{
	char	*string;
	int		len;
	char	mode;
	char	*mssj;

	mode = '\n';
	len = 0;
	index++;
	if (!cmd->cmd_array[index])
	{
		printf("\n");
		return (0);
	}
	printf("%d\n", index);
	if (check_dash_n(cmd, index))
		index = check_dash_n(cmd, index);
	while (cmd->cmd_array[index])
	{
		mssj = ft_strdup("");
		string = malloc(sizeof(char) * ft_strlen(cmd->cmd_array[index]));
		if (!string)
			return (0);
		g_index = 0;
		while (cmd->cmd_array[index][g_index])
		{
			if (cmd->cmd_array[index][g_index] == '$' && cmd->cmd_array[index][g_index + 1] != '$')
				mssj = ft_strjoin(mssj, case_1(data->env, cmd, index, g_index, string));
			else if (cmd->cmd_array[index][g_index] == '$' && cmd->cmd_array[index][g_index + 1] == '$')
				mssj = ft_strjoin(mssj, case_2(cmd, index, g_index));
			else
				mssj = ft_strjoin(mssj, case_3(cmd, index, g_index));
		}
		printf("%s ", mssj);
		// free(mssj);
		// free(string);
		index++;
	}
	printf("\n");
	return (1);
}
