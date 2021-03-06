/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinnune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:30:03 by vkinnune          #+#    #+#             */
/*   Updated: 2022/05/24 15:38:20 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char	*build_str(size_t ant, char *name, char *str)
{
	char	buf[1000];
	char	*p;

	p = buf;
	*p = 'L';
	p++;
	handle_nums(p, ant);
	while (*p != 0)
		p++;
	*p = '-';
	p++;
	ft_strcpy(p, name);
	while (*p != 0)
		p++;
	*p = ' ';
	p++;
	*p = 0;
	str = allocate_more(str, buf);
	return (str);
}

void	handle_nums(char *p, size_t ant)
{
	char	num[100];
	char	*p_num;

	p_num = &num[100 - 1];
	*p_num = 0;
	p_num--;
	while (ant)
	{
		*p_num = (ant % 10) + '0';
		ant /= 10;
		p_num--;
	}
	p_num++;
	ft_strcpy(p, p_num);
}

char	*allocate_more(char *str, char *buf)
{
	char	*cpy;

	if (str == 0)
	{
		str = (char *)malloc(((ft_strlen(buf)) + 1) * sizeof(char));
		ft_strcpy(str, buf);
	}
	else
	{
		cpy = (char *)malloc(((ft_strlen(str)
						+ ft_strlen(buf) + 1) * sizeof(char)));
		ft_strcpy(cpy, str);
		ft_strcat(cpy, buf);
		free(str);
		str = cpy;
	}
	return (str);
}

size_t	add_ants(size_t *flow, size_t path_index)
{
	size_t	res;
	size_t	i;

	res = 0;
	i = 0;
	while (i != path_index)
	{
		res += flow[i];
		i++;
	}
	return (res);
}
