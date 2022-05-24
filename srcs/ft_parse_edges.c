#include "lem-in.h"

void	add_edges(size_t in, size_t out, t_room *p_rooms);
size_t	read_room_a(char **p, char *p_names, size_t room_count);
size_t	read_room_b(char **p, char *p_names, size_t room_count);

t_room	*parse_edges(char *p, char *p_names, size_t room_count)
{
	t_room		*p_rooms;
	enum e_type	line_type;
	size_t		room_a;
	size_t		room_b;

	p_rooms = (t_room *)malloc(sizeof(t_room) * room_count);
	bzero(p_rooms, sizeof(t_room) * room_count);
	while (*p != 0)
	{
		line_type = comment_or_command(p);
		if (line_type == START || line_type == END)
			ft_out("Error on edges");
		else if (line_type == COMMENT)
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
		bzero(p_rooms[in].edges, sizeof(size_t) * 1);
	}
	else
	{
		edges = (size_t *)malloc(sizeof(size_t) * (p_rooms[in].edge_count + 1));
		bzero(edges, sizeof(size_t) * (p_rooms[in].edge_count + 1));
		memcpy(edges, p_rooms[in].edges, (p_rooms[in].edge_count
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
		ft_out("No edge name");
	p_save = *p;
	while (**p != '-' && **p != 0)
		(*p)++;
	if (*p - p_save > NAME_LENGTH)
		ft_out("Too long edge name");
	while (strncmp(p_save, &p_names[i * NAME_LENGTH],
			(*p) - p_save) && i != room_count)
		i++;
	if (i == room_count)
		ft_out("Error on edge name");
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
		ft_out("Too long edge name");
	if (*p == p_save)
		ft_out("Error on edge name");
	if (**p != '\n')
		ft_out("No new line in edge");
	while (strncmp(p_save, &p_names[i * NAME_LENGTH],
			*p - p_save) && i != room_count)
		i++;
	if (i == room_count)
		ft_out("Error on edge name");
	(*p)++;
	return (i);
}

