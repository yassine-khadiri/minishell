/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 15:12:35 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/06/18 19:08:27 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char    *get_var_name(char **cmd)
{
    char    *var_name;

    while (*cmd)
    {
        if (!ft_strcmp(*cmd, "$"))
        {
            var_name = *cmd;
            return (var_name);
        }
        cmd++;
    }
    return (0);
}

void    env_vars(char **env)
{
    char    *var_name;

    var_name = get_var_name(env);
    while (*env)
    {echo
        if (!ft_strcmp(*env, get_var_name(env)))
            get_path(env, get_var_name(env));
        env++;
    }
}
