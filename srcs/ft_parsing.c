#include "lem-in.h"

char	*skip_cords(char *p);
int	comment_or_command(char *p);
void	check_last_type(enum e_type last_line_type, t_info *p_info, size_t room_count);
char	*save_name(char *p, char *p_save, char **pp_names, size_t room_count);
void	add_edges(size_t in, size_t out, t_room *p_rooms);
size_t	read_room_a(char **p, char *p_names, size_t room_count);
size_t	read_room_b(char **p, char *p_names, size_t room_count);

size_t	parse_ant_count(const char *p_buf, t_info *info)
{
	enum	e_type	line_type;
	char	*p_str;

	p_str = (char *)p_buf;
	info->ant_count = 0;
	while (1)
	{
		line_type = comment_or_command(p_str);
		if (line_type == COMMENT)
		{
			while (*(p_str++) != '\n');
			continue ;
		}
		break ;
	}
	while (isdigit(*p_str))
	{
		info->ant_count *= 10;
		info->ant_count += *p_str - '0';
		p_str++;
	}
	if (*p_str != '\n')
		ft_out("Error on ant number");
	p_str++;
	return (p_str - p_buf);
}

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
		if (line_type == COMMENT)
		{
			while (*(p++) != '\n');
			continue ;
		}
		if (line_type == START || line_type == END)
		{
			while (*(p++) != '\n');
			continue ;
		}
		res = save_name(p, p, pp_names, room_count);
		if (res == p)
			break ;
		else
			p = res;
		p = skip_cords(p);
		check_last_type(last_line_type, p_info, room_count);
		room_count++;
		p++;
		continue ;
	}
	p_info->room_count = room_count;
	return (p - p_buf);
}

void	check_last_type(enum e_type last_line_type, t_info *p_info, size_t room_count)
{
	if (last_line_type == START)
		p_info->start = room_count;
	else if (last_line_type == END)
		p_info->end = room_count;
}

char	*save_name(char *p, char *p_save, char **pp_names, size_t room_count)
{
	char	*p_str;

	while (isascii(*p) && *p != ' ' && *p != '-' && *p != '\0') //forward name
		p++;
	if (p - p_save > NAME_LENGTH)
		ft_out("Too long name");
	if (*p == '-') //edges section is starting
		return (p_save);
	if (*p != ' ')
		ft_out("Bad room name");
	if (room_count == 0)
	{
		*pp_names = (char *)malloc(sizeof(char) * NAME_LENGTH);
		bzero(*pp_names, sizeof(char) * NAME_LENGTH);
	}
	else
	{
		p_str = (char *)malloc((sizeof(char) * NAME_LENGTH) * (room_count + 1));
		bzero(p_str, (sizeof(char) * NAME_LENGTH) * (room_count + 1));
		memcpy(p_str, *pp_names, (sizeof(char) * NAME_LENGTH) * (room_count));
		free(*pp_names);
		*pp_names = p_str;
	}
	strncpy(&(*pp_names)[room_count * NAME_LENGTH], p_save, p - p_save);
	(*pp_names)[p - p_save] = '\0';
	p++;
	return (p);
}

char	*skip_cords(char *p)
{
	while (isdigit(*p)) //skip cords
		p++;
	if (*p != ' ')
		ft_out("Bad x coordinate");
	p++;
	while (isdigit(*p)) //skip cords
		p++;
	if (*p != '\n')
		ft_out("Bad y coordinate");
	return (p);
}

t_room	*parse_edges(const char *p_buf, char *p_names, size_t room_count)
{
	t_room		*p_rooms;
	enum e_type	line_type;
	char		*p;
	size_t		room_a;
	size_t		room_b;

	p = (char *)p_buf;
	p_rooms = (t_room *)malloc(sizeof(t_room) * room_count);
	bzero(p_rooms, sizeof(t_room) * room_count);
	while (*p != 0)
	{
		line_type = comment_or_command(p);
		if (line_type == START || line_type == END)
			ft_out("Error on edges");
		else if (line_type == COMMENT)
		{
			while (*(p++) != '\n');
			continue ;
		}
		room_a = read_room_a(&p, p_names, room_count);
		room_b = read_room_b(&p, p_names, room_count);
		add_edges(room_a, room_b, p_rooms);
		add_edges(room_b, room_a, p_rooms);
		continue ;
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
		memcpy(edges, p_rooms[in].edges, (p_rooms[in].edge_count * sizeof(size_t)));
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
	while (strncmp(p_save, &p_names[i * NAME_LENGTH], *p - p_save) && i != room_count)
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
	while (strncmp(p_save, &p_names[i * NAME_LENGTH], *p - p_save) && i != room_count)
		i++;
	if (i == room_count)
		ft_out("Error on edge name");
	(*p)++;
	return (i);
}

int	comment_or_command(char *p)
{
	char	a = p[0];
	char	b = p[1];

	if (a == '#' && b != '#') //comment
		return (COMMENT);
	else if (a == '#' && b == '#') //start or end
	{
		if (!memcmp(p, "##start\n", 8))
			return (START);
		else if (!memcmp(p, "##end\n", 6))
			return (END);
		else
			ft_out("Bad command");
	}
	return (UNKNOWN); //nothing
}

int		ft_out(char *reason)
{
	char	*p;

	p = reason;
	while (*p)
	{
		write(1, p, 1);
		p++;
	}
	write(1, "\n", 1);
	exit(EXIT_FAILURE);
	return (EXIT_FAILURE);
}

