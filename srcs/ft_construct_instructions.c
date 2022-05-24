#include "lem-in.h"

size_t	get_set(t_path *paths, size_t set_count);
size_t	*get_flow(t_path *path, size_t ant_count);
int		loop_flows(t_info info, char *p_names, t_path *paths, char **str);
int		loop_paths(t_info info, char *p_names, t_path *paths, char **str);
size_t	add_ants(size_t *flow, size_t path_index);
char	*build_str(size_t ant, char *name, char *str);

char	*construct_instructions(t_path *paths,
			size_t set_count, char *p_names, t_info info)
{
	char	*str;

	str = 0;
	info.ins.tick = 1;
	info.ins.set = get_set(paths, set_count);
	info.ins.flow = get_flow(&paths[info.ins.set], info.ant_count);
	while (1)
	{
		if (loop_paths(info, p_names, paths, &str))
			return (str);
		info.ins.tick++;
	}
}

int	loop_paths(t_info info, char *p_names, t_path *paths, char **str)
{
	char	*p;
	size_t	res;

	info.ins.i = 0;
	res = 0;
	info.ins.res = &res;
	while (info.ins.i != paths[info.ins.set].count)
	{
		info.ins.ant = 1;
		if (loop_flows(info, p_names, paths, str))
			return (1);
		info.ins.i++;
	}
	p = *str;
	while (*p != 0)
		p++;
	p--;
	*p = '\n';
	return (0);
}

int	loop_flows(t_info info, char *p_names, t_path *paths, char **str)
{
	t_ins	ins;

	ins = info.ins;
	while (ins.ant <= ins.flow[ins.i])
	{
		ins.pos = ins.tick - ins.ant;
		if (ins.pos >= 0 && ins.pos < (ssize_t)paths[ins.set].sizes[ins.i])
			*str = build_str(ins.ant + add_ants(ins.flow, ins.i),
					&p_names[paths[ins.set].data[ins.i][ins.pos]
					* NAME_LENGTH], *str);
		else
			(*(ins.res))++;
		if ((*(ins.res)) >= info.ant_count)
		{
			free(ins.flow);
			info.ins = ins;
			return (1);
		}
		ins.ant++;
	}
	info.ins = ins;
	return (0);
}

size_t	*get_flow(t_path *path, size_t ant_count)
{
	size_t	*flow;
	size_t	path_count;
	size_t	save_index;
	size_t	*sizes;
	size_t	i;

	sizes = path->sizes;
	path_count = path->count;
	flow = (size_t *)malloc(path_count * sizeof(size_t));
	ft_bzero(flow, path_count * sizeof(size_t));
	while (ant_count)
	{
		i = 0;
		save_index = 0;
		while (i != path_count)
		{
			if ((flow[save_index] + sizes[save_index]) > (flow[i] + sizes[i]))
				save_index = i;
			i++;
		}
		flow[save_index]++;
		ant_count--;
	}
	return (flow);
}

size_t	get_set(t_path *paths, size_t set_count)
{
	ssize_t	latency;
	ssize_t	save_i;
	size_t	i;

	latency = INT_MAX;
	i = 0;
	save_i = -1;
	while (i != set_count)
	{
		if (paths[i].latency < 0)
			paths[i].latency *= -1;
		if (paths[i].latency < latency && paths[i].latency >= 0)
		{
			latency = paths[i].latency;
			save_i = i;
		}
		i++;
	}
	if (save_i == -1)
		ft_out("Error on getting a set");
	return (save_i);
}

