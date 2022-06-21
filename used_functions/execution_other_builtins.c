/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_other_builtins.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 16:59:05 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/06/21 18:01:24 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_path(char **env, char *env_variable)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], env_variable, ft_strlen(env_variable)))
			return (env[i] + ft_strlen(env_variable) + 1);
		i++;
	}
	return (NULL);
}

char	**ft_get_spllited_env(t_data *data)
{
	int		len;

	len = 0;
	while (data->env[len])
		len++;
	data->splitted_env = malloc(len * sizeof(char *));
	if (!data->splitted_env)
		return (NULL);
	data->splitted_env = ft_split(get_path(data->env, "PATH"), ':');
	return (data->splitted_env);
}

// void	execution_other_builtins(char **av, char **env)
void	execution_other_builtins(t_data *data)
{
	char	*path;
	int		pid;

	while (*data->splitted_env)
	{
		path = ft_strjoin(*data->splitted_env, "/");
		path = ft_strjoin(path, data->splitted_env[0]);
		if (!access(path, X_OK))
		{
			pid = fork(); // don't forget protection
			if (pid == 0)
				execve(path, data->spllited_cmd_buf, data->env);
			else
				waitpid(pid, NULL, 0);
		}
		data->splitted_env++;
	}
}
