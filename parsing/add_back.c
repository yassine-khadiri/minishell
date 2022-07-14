/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_back.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 19:06:52 by hbouqssi          #+#    #+#             */
/*   Updated: 2022/07/14 16:19:59 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void add_back(t_token **lst, t_token *new)
{
	t_token *temp;
	if (*lst == NULL)
		*lst = new;
	else
	{
		temp = is_last(*lst);
		temp->next = new;
		new->prev = temp;
	}
}