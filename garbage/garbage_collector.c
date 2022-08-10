/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 00:19:48 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/08/10 01:49:23 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add(t_node **garbage, void *pointer)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	node->pointer = pointer;
	node->next = *garbage;
	*garbage = node;
}

void	free_all(t_node *garbage)
{
	void	*tmp;

	tmp = NULL;
	while (garbage)
	{
		free(garbage->pointer);
		tmp = garbage;
		garbage = garbage->next;
		free(tmp);
	}
}
