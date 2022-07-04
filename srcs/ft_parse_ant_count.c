/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_ant_count.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinnune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:31:29 by vkinnune          #+#    #+#             */
/*   Updated: 2022/05/24 15:36:21 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

size_t	parse_ant_count(const char *p_buf, t_info *info)
{
	enum e_type	line_type;
	char		*p_str;

	p_str = (char *)p_buf;
	info->ant_count = 0;
	while (1)
	{
		line_type = comment_or_command(p_str);
		if (line_type == COMMENT || line_type == IGNORE)
		{
			while (*p_str != '\n')
				p_str++;
			continue ;
		}
		break ;
	}
	p_str = ant_num(p_str, info);
	if (*p_str != '\n')
		ft_out("ERROR");
	p_str++;
	return (p_str - p_buf);
}

char	*ant_num(char *p_str, t_info *info)
{
	if (*p_str == '0')
		ft_out("ERROR");
	while (ft_isdigit(*p_str))
	{
		info->ant_count *= 10;
		info->ant_count += *p_str - '0';
		p_str++;
	}
	return (p_str);
}
