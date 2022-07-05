/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 13:55:23 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/07/05 20:06:03 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int get_size_arr(char **arr)
{
    int len;
    
    len = 0;
    if (!arr)
        return (len);
    while (arr[len])
        len++;
    return (len);
}

char    **dollar_analayzer(t_data *data, char *str)
{
    char    **to_analize;
    int i;
    int j;
    int dollar_counter;

    i = 0;
    j = 0;
    dollar_counter = 0;
    to_analize = malloc(sizeof(char *) * (ft_strlen(str) + 1));
    if (!to_analize)
        return (NULL);
    while (str[i])
    {
        if (str[i] == '$')
        {
            to_analize[j] = ft_strdup("$");
            dollar_counter++;
        }
        if (!(dollar_counter % 2))
            to_analize[j] = ft_strdup(ft_itoa(getpid()));
        i++;
        j++;
    }
    data->new_index = i;
    to_analize[j] = NULL;
    return (to_analize);
}

char    **character_analayzer(char *str, char **loading, int new_index, char** env, char *string)
{
    if ((get_size_arr(loading) % 2))
    {
        new_index -= 1;
        check_dollar_sign(str + new_index, string, env);
    }
    return (NULL);
}

int	check_dollar_sign(char *str, char *string, char **env)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	while (str[i])
	{
        if (str[i] == '$')
        {
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

char    **ft_analayzer(t_data *data, char *str, char *string)
{
    int     i;
    char    **to_display;

    to_display = malloc(sizeof(char *) * (ft_strlen(str) + 1));
    if (!to_display)
        return (NULL);
    i = 0;
    data->new_index = 0;
    while (str[i])
    {
        if (str[i] == '$')
        {
            to_display = dollar_analayzer(data, str);
            data->new_index = i;
            character_analayzer(str + i, to_display, data->new_index, data->env, string);
            break ;
        }
        i++;
    }
    i = 0;
    while (to_display[i])
        printf("%s\n", to_display[i++]);
    return (0);
}
