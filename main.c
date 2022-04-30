#include "lem-in.h"

void	print_ants(t_global *g);
int		*get_flow(t_global *g);
int		add_ants(int *flow, int path_index);
int		move_ant(int path_index, int *flow, int tick, t_global *g);

int main(int ac, char **av)
{
	char		buf[BUFF_SIZE];
	int			fd;
	char		*p;
	t_global	g;

	bzero(&g, sizeof(g));
	bzero(buf, BUFF_SIZE);
	g.start = -1;
	g.end = -1;
	fd = open(av[1], O_RDONLY);
	if (fd <= 0)
		ft_out("Bad file");
	read(fd, buf, BUFF_SIZE);
	if (read(fd, 0, 0) != 0)
		ft_out("File too big");
	if (ac < 2)
		ft_out("give file");
	p = buf;
	p = parse_ant_count(&g, p);
	p = parse_nodes(&g, p);
	p = parse_edges(&g, p);
	find_paths(g.rooms[g.start].edge_count, &g);
	printf("%s", buf);
	print_ants(&g);
}

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
