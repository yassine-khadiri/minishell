/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 12:28:52 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/07/19 21:13:57 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	// var_name = ft_strtrim(var_name, "$");
	// printf("%s:\n", var_name);
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
		if ((str[i] == '$' && str[i + 1] == '$') || (str[i] == '$' && str[i + 1] == '\0'))
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

int	ft_echo(t_data *data, t_command *cmd, int index)
{
	(void)data;
	// int	dollars_count = 0;
	// char	**get_mssjs;
	// int		i;
	// int		j;
	char	*string;
	int		len;
	char	mode;
	char	*mssj;
	// char	*dollars_arr;
	// int	i;

	mode = '\n';
	len = 0;
	// while (cmd->cmd_array[++len]);
	// get_mssjs = (char **)malloc(sizeof(char *) * len);
	// if (!get_mssjs)
	// 	return (0);
	index++;
	if (!cmd->cmd_array[index])
	{
		printf("\n");
		return (0);
	}
	while (cmd->cmd_array[index])
	{
		// mssj = malloc(sizeof(char) * ft_strlen(cmd->cmd_array[index]));
		mssj = ft_strdup("");
		// printf("#%s\n", mssj);
		string = malloc(sizeof(char) * ft_strlen(cmd->cmd_array[index]));
		if (!string)
			return (0);
		int	i = 0;
		int	j = 0;
		while (cmd->cmd_array[index][i])
		{
			if (cmd->cmd_array[index][i] == '$' && cmd->cmd_array[index][i + 1] != '$')
			{
				// bool	check_execution = false;
					i++;
				while (cmd->cmd_array[index][i])
				{
					j = 0;
					while (cmd->cmd_array[index][i] && cmd->cmd_array[index][i] != '$')
						string[j++] = cmd->cmd_array[index][i++];
					string[j] = '\0';
					// printf("%s\n", string);
					// if (check_env_var(string))
					// 	mssj = ft_strjoin(mssj, get_val_env_var(data->env, string));
					// else
						mssj = ft_strjoin(mssj, check_res(string, data->env));
						// mssj = ft_strdup(check_res(string, data->env));
					i++;
				}
			}
			else if (cmd->cmd_array[index][i] == '$' && cmd->cmd_array[index][i + 1] == '$')
			{
				j = 0;
				while (cmd->cmd_array[index][i])
				{
					if (cmd->cmd_array[index][i] == '$' && cmd->cmd_array[index][i] != '$')
					{
						mssj[j] = '\0';
						break;
					}
					mssj[j++] = cmd->cmd_array[index][i++];
				}
			}
			else
			{
				j = 0;
				while (cmd->cmd_array[index][i])
				{
					if (cmd->cmd_array[index][i] == '$')
						break ;
					mssj[j++] = cmd->cmd_array[index][i++];
				}
				mssj[j] = '\0';
			}
		}
		printf("%s ", mssj);
		// free(mssj);
		// free(string);
		index++;
	}
	printf("\n");
	return (0);
}
