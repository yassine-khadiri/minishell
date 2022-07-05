/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 13:55:23 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/07/05 17:59:29 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_dollar_sign(char *str, char *string, char **env, char mode)
{
    bool    find;
	int		i;
	int		j;
	int		k;

	i = 0;
    find = false;
	while (str[i])
	{
        if (str[i] == '$')
        {
            mode = '\n';
            j = ++i;
            k = 0;
            while (str[j] && str[j] != '$'
                && (ft_isalpha(str[j]) || ft_isdigit(str[j])))
                string[k++] = str[j++];
            string[k] = '\0';
            if (ft_strcmp(check_var(string, env), ""))
                print_mssj(check_var(string, env), '\0');
            k = 0;
            while (str[j] && str[j] != '$')
                string[k++] = str[j++];
            string[k] = '\0';
            print_mssj(string, '\0');
            i = --j;
        }
        i++;
	}
    printf("\n");
	return (0);
}