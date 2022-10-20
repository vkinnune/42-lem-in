/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrummuka <jrummuka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:32:10 by vkinnune          #+#    #+#             */
/*   Updated: 2022/10/20 20:48:17 by jrummuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char	*parse_nodes(const char *input_str, t_info *info,
			char **names, uint64_t node_count)
{
	enum e_type	line_type;
	enum e_type	last_line_type;
	char		*p;
	char		*res;

	line_type = UNKNOWN;
	p = (char *)input_str;
	while (1)
	{
		last_line_type = line_type;
		line_type = comment_or_command(p);
		afterstartorend(line_type, last_line_type);
		if (skip_comment_or_command(&p, line_type))
			continue ;
		res = p;
		p = save_name(p, p, names, node_count);
		if (res == p)
			break ;
		p = skip_cords(p);
		check_last_type(last_line_type, info, &node_count);
		p++;
	}
	info->node_count = node_count;
	return (p);
}

int	skip_comment_or_command(char **p, enum e_type line_type)
{
	if (line_type == COMMENT || line_type == IGNORE)
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

char	*save_name(char *p, char *save, char **names, uint64_t node_count)
{
	while (ft_isascii(*p) && *p != ' ' && *p != '-' && *p != '\0')
		p++;
	if (p - save > NAME_LENGTH)
		ft_out("ERROR");
	if (*p == '-')
		return (save);
	if (*p != ' ')
		ft_out("ERROR");
	*names = name_alloc(names, node_count);
	ft_memcpy(&(*names)[node_count * NAME_LENGTH], save, p - save);
	(*names)[(p - save) + (node_count * NAME_LENGTH)] = '\0';
	p++;
	return (p);
}

char	*name_alloc(char **names, uint64_t node_count)
{
	char	*p;

	if (node_count == 0)
	{
		*names = (char *)malloc(sizeof(char) * NAME_LENGTH);
		ft_bzero(*names, sizeof(char) * NAME_LENGTH);
	}
	else
	{
		p = (char *)malloc((sizeof(char) * NAME_LENGTH) * (node_count + 1));
		ft_bzero(p, (sizeof(char) * NAME_LENGTH) * (node_count + 1));
		ft_memcpy(p, *names,
			(sizeof(char) * NAME_LENGTH) * (node_count));
		free(*names);
		*names = p;
	}
	return (*names);
}

char	*skip_cords(char *p)
{
	while (ft_isdigit(*p))
		p++;
	if (*p != ' ')
		ft_out("ERROR");
	p++;
	while (ft_isdigit(*p))
		p++;
	if (*p != '\n')
		ft_out("ERROR");
	return (p);
}
