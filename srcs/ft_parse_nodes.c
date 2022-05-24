/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_nodes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinnune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:32:10 by vkinnune          #+#    #+#             */
/*   Updated: 2022/05/24 16:32:15 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

size_t	parse_nodes(const char *p_buf, t_info *p_info, char **pp_names)
{
	enum e_type	line_type;
	enum e_type	last_line_type;
	char		*p;
	char		*res;
	size_t		room_count;

	room_count = 0;
	line_type = UNKNOWN;
	p = (char *)p_buf;
	while (1)
	{
		last_line_type = line_type;
		line_type = comment_or_command(p);
		if (skip_comment_or_command(&p, line_type))
			continue ;
		res = p;
		p = save_name(p, p, pp_names, room_count);
		if (res == p)
			break ;
		p = skip_cords(p);
		check_last_type(last_line_type, p_info, &room_count);
		p++;
	}
	p_info->room_count = room_count;
	return (p - p_buf);
}

int	skip_comment_or_command(char **p, enum e_type line_type)
{
	if (line_type == COMMENT)
	{
		while (**p != '\n')
			(*p)++;
		(*p)++;
		return (1);
	}
	if (line_type == START || line_type == END)
	{
		while (**p != '\n')
			(*p)++;
		(*p)++;
		return (1);
	}
	return (0);
}

char	*save_name(char *p, char *p_save, char **pp_names, size_t room_count)
{
	while (ft_isascii(*p) && *p != ' ' && *p != '-' && *p != '\0')
		p++;
	if (p - p_save > NAME_LENGTH)
		ft_out("Too long name");
	if (*p == '-')
		return (p_save);
	if (*p != ' ')
		ft_out("Bad room name");
	*pp_names = name_alloc(pp_names, room_count);
	ft_memcpy(&(*pp_names)[room_count * NAME_LENGTH], p_save, p - p_save);
	(*pp_names)[p - p_save] = '\0';
	p++;
	return (p);
}

char	*name_alloc(char **pp_names, size_t room_count)
{
	char	*p_str;

	if (room_count == 0)
	{
		*pp_names = (char *)malloc(sizeof(char) * NAME_LENGTH);
		ft_bzero(*pp_names, sizeof(char) * NAME_LENGTH);
	}
	else
	{
		p_str = (char *)malloc((sizeof(char) * NAME_LENGTH) * (room_count + 1));
		ft_bzero(p_str, (sizeof(char) * NAME_LENGTH) * (room_count + 1));
		ft_memcpy(p_str, *pp_names,
			(sizeof(char) * NAME_LENGTH) * (room_count));
		free(*pp_names);
		*pp_names = p_str;
	}
	return (*pp_names);
}

char	*skip_cords(char *p)
{
	while (ft_isdigit(*p))
		p++;
	if (*p != ' ')
		ft_out("Bad x coordinate");
	p++;
	while (ft_isdigit(*p))
		p++;
	if (*p != '\n')
		ft_out("Bad y coordinate");
	return (p);
}
