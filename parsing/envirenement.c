/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envirenement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 00:07:10 by hbouqssi          #+#    #+#             */
/*   Updated: 2022/07/14 16:20:01 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env *initial_env_node(char *name, char *value)
{
	t_env *first_env_node;
	first_env_node = (t_env *)malloc(sizeof(t_env));
	first_env_node->name = name;
	first_env_node->value = value;
	first_env_node->next = NULL;
	return (first_env_node);
}

void add_env_node(t_env *env_l, char *name, char *value)
{
	t_env *new_env;

	new_env = env_l;
	while (new_env->next != NULL)
		new_env = new_env->next;
	new_env->next = malloc(sizeof(t_env));
	new_env->next->name = name;
	new_env->next->value = value;
	new_env->next->next = NULL;
}

t_env *create_env_list(t_env *l_env, char **env)
{
	char **str;
	int i;

	i = 0;
	if (env[i])
	{
		//*lenv = (t_env *)malloc(sizeof(t_env));
		str = ft_split(env[i], '=');
		l_env = initial_env_node(str[0], str[1]);
		//(*lenv)->name = str[0];
		//(*lenv)->value = str[1];
		// free(str);
	}
	while (env[i])
	{
		//(*lenv)->next = malloc(sizeof(t_env));
		//(*lenv) = (*lenv)->next;
		str = ft_split(env[i], '=');
		add_env_node(l_env, str[0], str[1]);
		//(*lenv)->name = str[0];
		//(*lenv)->value = str[1];
		// free(str);
		i++;
	}
	return (l_env);
}