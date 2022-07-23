/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 01:09:55 by hbouqssi          #+#    #+#             */
/*   Updated: 2022/07/23 17:43:04 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redirection	*initalize_redirections(int type, char *value, t_env *lenv)
{
	t_redirection	*redirection;

	redirection = malloc(sizeof(t_redirection));
	if (!redirection)
		return (NULL);
	if (type == HERDOC)
		value = treat_heredocs(value, lenv);
	redirection->type = type;
	redirection->file = value;
	redirection->next = NULL;
	return (redirection);
}

void	push_redirections(t_redirection **head, t_redirection *new_redirection)
{
	t_redirection	*_head;

	if (!head || !new_redirection)
		return ;
	_head = *head;
	if (!_head)
	{
		*head = new_redirection;
		return ;
	}
	while (_head->next)
		_head = _head->next;
	_head->next = new_redirection;
}

int	tab_size(char **cmd_args)
{
	int	i;

	i = 0;
	while (cmd_args[i] != NULL)
		i++;
	return (i);
}
