/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 18:57:10 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/06/22 11:51:18 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	data_initializer(t_data *data, char **env)
{
	data->g_std._stdin = dup(0);
	data->g_std._stdout = dup(1);
	data->env = env;
	data->splitted_path = ft_get_spllited_path_env(data);
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	data_initializer(data, env);
	(void)argv;
	if (argc > 1)
		exit(1);
	minishel_start(data);
	return (0);
}
