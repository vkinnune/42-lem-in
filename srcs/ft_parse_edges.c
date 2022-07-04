/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_edges.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinnune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:31:35 by vkinnune          #+#    #+#             */
/*   Updated: 2022/05/24 15:36:33 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room	*parse_edges(char *p, char *p_names, size_t room_count)
{
	t_room		*p_rooms;
	enum e_type	line_type;
	size_t		room_a;
	size_t		room_b;

	p_rooms = (t_room *)malloc(sizeof(t_room) * room_count);
	ft_bzero(p_rooms, sizeof(t_room) * room_count);
	while (*p != 0 && p[1] != 0)
	{
		line_type = comment_or_command(p);
		if (line_type == START || line_type == END)
			ft_out("ERROR");
		else if (line_type == COMMENT || line_type == IGNORE)
		{
			while (*p != '\n')
				p++;
			continue ;
		}
		room_a = read_room_a(&p, p_names, room_count);
		room_b = read_room_b(&p, p_names, room_count);
		add_edges(room_a, room_b, p_rooms);
		add_edges(room_b, room_a, p_rooms);
	}
	return (p_rooms);
}

void	add_edges(size_t in, size_t out, t_room *p_rooms)
{
	size_t	*edges;

	if (p_rooms[in].edge_count == 0)
	{
		p_rooms[in].edges = (size_t *)malloc(sizeof(size_t) * 1);
		ft_bzero(p_rooms[in].edges, sizeof(size_t) * 1);
	}
	else
	{
		edges = (size_t *)malloc(sizeof(size_t) * (p_rooms[in].edge_count + 1));
		ft_bzero(edges, sizeof(size_t) * (p_rooms[in].edge_count + 1));
		ft_memcpy(edges, p_rooms[in].edges, (p_rooms[in].edge_count
				* sizeof(size_t)));
		free(p_rooms[in].edges);
		p_rooms[in].edges = edges;
	}
	p_rooms[in].edges[p_rooms[in].edge_count] = out;
	p_rooms[in].edge_count++;
}

size_t	read_room_a(char **p, char *p_names, size_t room_count)
{
	size_t	i;
	char	*p_save;

	i = 0;
	if (**p == '-')
		ft_out("ERROR4");
	p_save = *p;
	while (**p != '-' && **p != 0)
		(*p)++;
	if (*p - p_save > NAME_LENGTH)
		ft_out("ERROR3");
	while (ft_strncmp(p_save, &p_names[i * NAME_LENGTH], (*p) - p_save)
		&& i != room_count)
		i++;
	if (i == room_count)
		ft_out("ERROR2");
	(*p)++;
	return (i);
}

size_t	read_room_b(char **p, char *p_names, size_t room_count)
{
	size_t	i;
	char	*p_save;

	i = 0;
	p_save = *p;
	while (**p != '\n' && **p != 0)
		(*p)++;
	if (*p - p_save > NAME_LENGTH)
		ft_out("ERROR");
	if (*p == p_save)
		ft_out("ERROR");
	if (**p != '\n')
		ft_out("ERROR");
	while (ft_strncmp(p_save, &p_names[i * NAME_LENGTH],
			*p - p_save) && i != room_count)
		i++;
	if (i == room_count)
		ft_out("ERROR");
	(*p)++;
	return (i);
}

