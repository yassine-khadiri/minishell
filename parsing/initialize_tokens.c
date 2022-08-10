/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 01:06:40 by hbouqssi          #+#    #+#             */
/*   Updated: 2022/08/10 01:20:23 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*initialize_list(void)
{
	t_token	*token_list;

	token_list = malloc(sizeof(t_token));
	add(&g_tools.garbage, token_list);
	if (!token_list)
		return (NULL);
	token_list->type = NONE;
	token_list->value = ft_strdup("NONE");
	token_list->next = NULL;
	token_list->prev = NULL;
	return (token_list);
}

t_token	*create_token(int type, char *value)
{
	t_token	*tokens;

	tokens = (t_token *)malloc(sizeof(t_token));
	add(&g_tools.garbage, tokens);
	if (!tokens)
		return (NULL);
	tokens->type = type;
	tokens->value = ft_strdup(value);
	tokens->next = NULL;
	tokens->prev = NULL;
	return (tokens);
}
