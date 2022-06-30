/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:52:30 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/06/30 17:11:09 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (check_equal_sign(env[i]))
			printf("%s\n", env[i]);
		i++;
	}
	return (0);
}
