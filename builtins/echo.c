/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 12:28:52 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/07/18 21:03:19 by ykhadiri         ###   ########.fr       */
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

// int	ft_echo(t_data *data, t_command *cmd, int index)
// {
// 	char	**get_mssjs;
// 	int		i;
// 	int		j;
// 	int		len;
// 	char	mode;
// 	char	*string;

// 	mode = '\n';
// 	len = 0;
// 	while (cmd->cmd_array[++len]);
// 	get_mssjs = (char **)malloc(sizeof(char *) * len);
// 	if (!get_mssjs)
// 		return (0);
// 	index++;
// 	if (!cmd->cmd_array[index])
// 	{
// 		printf("\n");
// 		return (0);
// 	}
// 	i = 0;
// 	while (cmd->cmd_array[index])
// 		get_mssjs[i++] = ft_strdup(ft_strtrim(cmd->cmd_array[index++],
// 					"\""));
// 	get_mssjs[i] = NULL;
// 	i = 0;
// 	while (get_mssjs[i])
// 	{
// 		j = 0;
// 		string = malloc(sizeof(char) * (ft_strlen(get_mssjs[i]) + 1));
// 		if (!string)
// 			return (0);
// 		if (!ft_strcmp(get_mssjs[i], "-n") && i == 0)
// 		{
// 			mode = '\n';
// 			i++;
// 		}
// 		if (get_mssjs[i][0] == '\'' && get_mssjs[i][ft_strlen(get_mssjs[i])
// 			- 1] == '\'')
// 			get_mssjs[i] = ft_strtrim(get_mssjs[i], "'");
// 		print_mssj(get_mssjs[i], mode);
// 		if (i < len - 2 && !ft_strcmp(get_mssjs[0], "-n"))
// 			printf(" ");
// 		;
// 		while (get_mssjs[i][j])
// 		{
// 			if (get_mssjs[i][j] == '$' && get_mssjs[i][j + 1] != '$'
// 				&& get_mssjs[i][j + 1] != '\0')
// 			{
// 				check_dollar_sign(get_mssjs[i], string, data->env);
// 				break ;
// 			}
// 			else if (get_mssjs[i][j] == '$' && get_mssjs[i][j + 1] == '$')
// 			{
// 				check_dollars(get_mssjs[i]);
// 				break ;
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (0);
// }
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
	// i = 0;
	// while (cmd->cmd_array[index])
	// 	get_mssjs[i++] = ft_strdup(ft_strtrim(cmd->cmd_array[index++], "\""));
	// get_mssjs[i] = NULL;
	// i = index + 1;
	while (cmd->cmd_array[index])
	{
		
		mssj = malloc(sizeof(char) * ft_strlen(cmd->cmd_array[index]));
		string = malloc(sizeof(char) * ft_strlen(cmd->cmd_array[index]));
		if (!mssj)
			return (0);
		mssj = cmd->cmd_array[index];
		if (cmd->cmd_array[index][0] == '$')
		{
			int	i = 1;
			int	j = 0;
			while (cmd->cmd_array[index][i] && cmd->cmd_array[index][i] != '$')
				string[j++] = cmd->cmd_array[index][i++];
			string[j] = '\0';
			// printf("%s\n", string);
			if (!check_env_var(string))
				mssj = check_res(string, data->env);
		}
		printf("%s ",mssj);
		index++;
	// 	j = 0;
	// 	string = malloc(sizeof(char) * (ft_strlen(get_mssjs[i]) + 1));
	// 	if (!string)
	// 		return (0);
	// 	if (!ft_strcmp(get_mssjs[i], "-n") && i == 0)
	// 	{
	// 		mode = '\n';
	// 		i++;
	// 	}
	// 	if (get_mssjs[i][0] == '\'' && get_mssjs[i][ft_strlen(get_mssjs[i]) - 1] == '\'')
	// 		get_mssjs[i] = ft_strtrim(get_mssjs[i], "'");
	// 	print_mssj(get_mssjs[i], mode);
	// 	if (i < len - 2 && !ft_strcmp(get_mssjs[0], "-n"))
	// 		printf(" ");
	// 	while (get_mssjs[i][j])
	// 	{
	// 		if (get_mssjs[i][j] == '$' && get_mssjs[i][j + 1] != '$'
	// 			&& get_mssjs[i][j + 1] != '\0')
	// 		{
	// 			check_dollar_sign(get_mssjs[i], string, data->env);
	// 			break ;
	// 		}
	// 		else if (get_mssjs[i][j] == '$' && get_mssjs[i][j + 1] == '$')
	// 		{
	// 			check_dollars(get_mssjs[i]);
	// 			break ;
	// 		}
	// 		j++;
	// 	}
	// 	i++;
	}
	printf("\n");
	return (0);
}
