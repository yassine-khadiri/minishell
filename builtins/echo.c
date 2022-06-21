/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 12:28:52 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/06/21 18:29:06 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char    *extract_var_name_env(char *env)
{
    char    *var_name;
    int     i;

    i = 0;
    var_name = malloc(sizeof(char) * ft_strlen(env));
    if (!var_name)
        return (0);
    while (env[i])
    {
       if (env[i] == '=')
       {
           var_name[i] = '\0';
           return (var_name);
       }
        var_name[i] = env[i];
        i++;
    }
    return (0);
}

void	env_vars(char **env, char *var_name)
{
    // char    *var_name;
	// char	*mssj;

    // printf("%s\n", extract_var_name_env(env[0]));
            printf("%s\n", var_name);
    while (*env)
    {
        printf("%s\n", extract_var_name_env(*env));
            // printf("%s\n", get_path(env, extract_var_name_env(*env)));
        if (!ft_strcmp(var_name, extract_var_name_env(*env)))
		{
            printf("HERE!\n");
            // mssj = get_path(env, extract_var_name_env(*env));
            // printf("%s\n", mssj);
			// if (mssj)
			// 	printf("%s\n", mssj);
			// else
			// 	printf("hello\n");
		}
        env++;
    }
}

int	ft_echo(t_data *data, int index)
{
    // (void)env;
    if (!ft_strcmp(data->spllited_cmd_buf[++index], "-n"))
        printf("%s", ft_strtrim(data->spllited_cmd_buf[++index], "\""));
	else if (data->spllited_cmd_buf[index][0] == '$')
    {
        // printf("HERE!\n");
		env_vars(data->env, ++data->spllited_cmd_buf[index]);
    }
	// else
	// 	printf("%s\n", ft_strtrim(string[index], "\""));
	return (0);
}
