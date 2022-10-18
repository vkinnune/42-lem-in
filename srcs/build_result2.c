/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_result2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinnune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:07:15 by vkinnune          #+#    #+#             */
/*   Updated: 2022/10/13 14:45:05 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

uint64_t	handle_nums(char *str, uint64_t ant)
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
	ft_strcpy(str, p_num);
	return (ft_strlen(p_num));
}

char	*add_newline(char *str)
{
	uint64_t	size;

	if (str == 0)
		return (0);
	size = ft_strlen(str) + 1;
	str = ft_realloc(str, size + 1, size);
	str[size - 2] = '\n';
	str[size - 1] = 0;
	return (str);
}

