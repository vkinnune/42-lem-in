#include "lem-in.h"

void	read_input(char **av, char *buf);
void	parse_input(char *p_buf, t_info *p_info, char **pp_names, t_room **pp_rooms);

int	main(int argc, char **argv)
{
	char	p_buf[BUFF_SIZE];
	char	*p_names;
	t_room	*p_rooms;
	t_info	info;
	char	*res;

	if (argc < 2)
		ft_out("Give a file");
	else if (argc > 2)
		ft_out("Too many files");
	read_input(argv, p_buf);
	parse_input(p_buf, &info, &p_names, &p_rooms);
	res = move_ants(info, p_names, p_rooms);
	write(1, p_buf, strlen(p_buf));
	write(1, "\n", 1);
	write(1, res, strlen(res));
	//free_edges(p_rooms, info.room_count);
	free(p_names); //free also edges
	free(p_rooms);
	free(res);
}


void	read_input(char **av, char *p_buf)
{
	int	fd;
	int	size;

	fd = open(av[1], O_RDONLY);
	if (fd <= 0)
		ft_out("Wrong file");
	size = read(fd, p_buf, BUFF_SIZE);
	if (size <= 0)
		ft_out("Error reading");
	if (read(fd, 0, 1) != 0)
		ft_out("File too big");
	p_buf[size] = '\0';
}

void	parse_input(char *p_buf, t_info *p_info, char **pp_names, t_room **pp_rooms)
{
	size_t	bytes_parsed;

	bytes_parsed = parse_ant_count(p_buf, p_info);
	bytes_parsed += parse_nodes(&p_buf[bytes_parsed], p_info, pp_names);
	*pp_rooms = parse_edges(&p_buf[bytes_parsed], *pp_names, p_info->room_count);
}
	/*
void	print_ants(t_global *g)
{
	int	ant_count;
	int	*flow;
	int	res;
	int	tick;
	int	path_index;

	ant_count = g->ant_count;
	flow = get_flow(g);
	tick = 1;
	while (1)
	{
		printf("\n");
		res = 0;
		path_index = 0;
		g->is_space = false;
		while (path_index != g->path_count)
		{
			res += move_ant(path_index, flow, tick, g);
			path_index++;
		}
		if (res >= ant_count)
			break ;
		tick++;
	}
	free(flow);
	//printf("\n");
}

int	move_ant(int path_index, int *flow, int tick, t_global *g)
{
	int		len;
	int		res;
	int		pos;
	int		ant;

	len = g->paths[path_index].size;
	res = 0;
	ant = 1;
	while (ant <= flow[path_index])
	{
		pos = tick - ant;
		if (pos >= 0 && pos <= len)
		{
			if (g->is_space == true)
				printf(" ");
			printf("L%d-%s", ant + add_ants(flow, path_index), g->names[g->paths[path_index].data[pos]]);
			g->is_space = true;
		}
		else
			res++;
		ant++;
	}
	return (res);
}

int	add_ants(int *flow, int path_index)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (i != path_index)
	{
		res += flow[i];
		i++;
	}
	return (res);
}

int	*get_flow(t_global *g)
{
	int	*flow;
	int	i;
	int	save_index;
	int	ant_count;

	flow = (int *)malloc(sizeof(int) * g->path_count);
	bzero(flow, sizeof(*flow));
	ant_count = g->ant_count;
	while (ant_count)
	{
		save_index = 0;
		i = 0;
		while (i != g->path_count)
		{
			if ((flow[save_index] + g->paths[save_index].size) > (flow[i] + g->paths[i].size))
				save_index = i;
			i++;
		}
		flow[save_index]++;
		ant_count--;
	}
	return (flow);
}
*/

