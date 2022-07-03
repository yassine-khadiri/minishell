/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 12:28:52 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/07/03 19:16:15 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_var(char *var_name, char **env)
{
	var_name = ft_strtrim(var_name, "$");
	if (get_val_env_var(env, var_name))
		var_name = get_val_env_var(env, var_name);
	else
		var_name = "";
	return (var_name);
}

void	print_pid(char *str)
{
	int	i;
	int	dollar_count;
	char	dollars_arr[1000];

	i = 0;
	dollar_count = 0;
	while (str[i])
	{
		if ((str[i] == '$' && str[i + 1] == '$')
			|| (str[i] == '$' && str[i + 1] == '\0'))
		{
			dollars_arr[i] = '$';
			dollar_count++;
		}
		i++;
	}
	dollars_arr[i] = '\0';
	i = 0;
	while (dollars_arr[i] && dollar_count > 0)
	{
		printf("%d", getpid());
		dollar_count -= 2;
		if (!dollar_count)
		{
			printf("\n");
			break ;
		}
		else if (dollar_count == 1)
		{
			printf("$\n");
			break;
		}	
		i++;
	}
}

void	print_mssj(char *str, char mode)
{
	if (mode == '\n')
		printf("%s", str);
	else
		printf("%s\n", str);
}

int	ft_echo(t_data *data, int index)
{
	char	**get_mssjs;
	int		i;
	int		j;
	int		len;
	char mode;

	mode = '\0';
	len = 0;
	while (data->spllited_cmd_buf[++len]);
	get_mssjs = (char **)malloc(sizeof(char *) * len);
	if (!get_mssjs)
		return (0);
	index++;
	if (!data->spllited_cmd_buf[index])
	{
		printf("\n");
		return (0);
	}
	i = 0;
	while (data->spllited_cmd_buf[index])
		get_mssjs[i++] = ft_strdup(ft_strtrim(data->spllited_cmd_buf[index++], "\""));
	get_mssjs[i] = NULL;
	i = 0;
	while (get_mssjs[i])
	{
		j = 0;
		// while (get_mssjs[i][j])
		// {
		// 	if (get_mssjs[i][j] == '$')
		// 		get_mssjs[i] = check_var(get_mssjs[i], data->env);
		// 	j++;
		// }
		// if (!ft_strcmp(get_mssjs[i], "-n") && i == 0)
		// {
		// 	mode = '\n';
		// 	i++;
		// }
		// if (get_mssjs[i][0] == '\'' && get_mssjs[i][ft_strlen(get_mssjs[i]) - 1] == '\'')
		// 	get_mssjs[i] = ft_strtrim(get_mssjs[i], "'");
		if (get_mssjs[i][j] == '$')
			print_pid(get_mssjs[i]);
			// get_mssjs[i] = check_var(get_mssjs[i], data->env);
		// print_mssj(get_mssjs[i], mode);
		// if (i < len - 2 && !ft_strcmp(get_mssjs[0], "-n"))
		// 	printf(" ");
		i++;
	}
	return (0);
}
