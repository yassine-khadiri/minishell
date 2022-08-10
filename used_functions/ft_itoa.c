/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 19:15:00 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/08/10 01:14:07 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	ft_nb_len(long nb)
{
	int	len;

	len = 0;
	if (nb <= 0)
		len++;
	while (nb)
	{
		len++;
		nb = nb / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long	len;
	char	*str;
	long	nb;

	nb = n;
	len = ft_nb_len(nb);
	str = (char *)malloc(sizeof(char) * len + 1);
	add(&g_tools.garbage, str);
	if (!str)
		return (NULL);
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	if (nb == 0)
		str[0] = '0';
	str[len--] = '\0';
	while (nb > 0)
	{
		str[len] = nb % 10 + '0';
		len--;
		nb = nb / 10;
	}
	return (str);
}
