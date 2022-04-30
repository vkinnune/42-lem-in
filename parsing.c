#include "lem-in.h"

char	*parse_ant_count(t_global *g, char *p)
{
	enum e_type	line_type;

	g->ant_count = 0;
	while (1)
	{
		line_type = comment_or_command(p);
		if (line_type == START || line_type == END)
			ft_out("Error first line");
		else if (line_type == COMMENT)
		{
			while (*(p++) != '\n'); //SKIP LINE
			continue ;
		}
		break ;
	}
	while (isdigit(*p))
	{
		g->ant_count *= 10;
		g->ant_count += *p - '0';
		p++;
	}
	if (*p != '\n')
			ft_out("Error on ant number");
	p++;
	return (p);
}

char	*parse_nodes(t_global *g, char *p)
{
	enum e_type	line_type;
	enum e_type	last_line_type;
	char		*s;

	g->room_count = 0;
	line_type = UNKNOWN;
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
		s = p;
		while (isascii(*p) && *p != ' ' && *p != '-')
			p++;
		if (*p == '-')
		{
			p = s;
			break ;
		}
		else if (*p != ' ')
			ft_out("Bad room name");
		memcpy(g->names[g->room_count], s, p - s);
		g->names[g->room_count][p - s] = 0;
		p++;
		while (isdigit(*p))
		{
			g->cords[g->room_count].x *= 10;
			g->cords[g->room_count].x += *p - '0';
			p++;
		}
		if (*p != ' ')
			ft_out("Bad x coordinate");
		p++;
		while (isdigit(*p))
		{
			g->cords[g->room_count].y *= 10;
			g->cords[g->room_count].y += *p - '0';
			p++;
		}
		if (*p != '\n')
			ft_out("Bad y coordinate");
		if (last_line_type == START)
			g->start = g->room_count;
		else if (last_line_type == END)
			g->end = g->room_count;
		p++;
		g->room_count++;
		continue ;
	}
	if (g->start == -1)
		ft_out("Start not found");
	else if (g->end == -1)
		ft_out("End not found");
	return (p);
}

char	*parse_edges(t_global *g, char *p)
{
	char		*s;
	unsigned int			i;
	enum e_type	line_type;
	int			room_a;
	int			room_b;

	while (1)
	{
		i = 0;
		line_type = comment_or_command(p);
		if (*p == 0)
			break ;
		if (line_type == START || line_type == END)
			ft_out("Error on edges");
		else if (line_type == COMMENT)
		{
			while (*(p++) != '\n');
			continue ;
		}
		if (*p == '-')
			ft_out("No edge name");
		s = p;
		while (*p != '-')
			p++;
		while (strncmp(s, g->names[i], p - s) && i != g->room_count)
			i++;
		if (i == g->room_count)
			ft_out("Error on edge name");
		room_a = i;
		p++;
		s = p;
		i = 0;
		while (*p != '\n' && *p != 0)
			p++;
		if (p == s)
			ft_out("Error on edge name");
		if (*p != '\n')
			ft_out("No new line in edge");
		while (strncmp(s, g->names[i], p - s) && i != g->room_count)
			i++;
		if (i == g->room_count)
			ft_out("Error on edge name");
		room_b = i;
		{
			g->rooms[room_a].edges[g->rooms[room_a].edge_count++] = room_b;
			g->rooms[room_b].edges[g->rooms[room_b].edge_count++] = room_a;
		}
		p++;
		continue ;
	}
	return (p);
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

int		ft_out(char *reason) //todo use ft_printf
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

