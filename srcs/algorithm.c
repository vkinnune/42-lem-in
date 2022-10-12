#include "lem_in.h"

void	alloc_flows(t_node *nodes, t_info info)
{
	size_t	i;

	i = 0;
	while (i != info.node_count)
	{
		nodes[i].flows = (ssize_t *)malloc(sizeof(ssize_t)
				* nodes[i].edge_count);
		nodes[i].path_id = -1;
		nodes[i].is_end = false;
		ft_bzero(nodes[i].flows, sizeof(ssize_t) * nodes[i].edge_count);
		i++;
	}
	nodes[info.end].is_end = true;
}

t_path	find_augmenting_paths(t_node *nodes, t_info info)
{
	t_path	paths[2];
	size_t	i;

	ft_bzero(paths, sizeof(t_path) * 2);
	paths[0].latency = INT_MAX;
	alloc_flows(nodes, info);
	while (1)
	{
		i = 0;
		while (i != info.node_count)
		{
			nodes[i].visited = false;
			nodes[i].prev_node = -1;
			nodes[info.start].path_id = -1;
			nodes[info.end].path_id = -1;
			i++;
		}
		if (!bfs(nodes, info))
			break ;
		augment(nodes, info);
		create_path(paths, nodes, info);
		if (paths[1].latency < paths[0].latency)
			paths[0] = paths[1];
	}
	return (paths[0]);
}

t_path	alloc_path(t_node *nodes, t_info info, size_t path_count, size_t i)
{
	size_t	current_node;
	size_t	len;
	size_t	x;
	t_path	paths;

	len = 2;
	current_node = nodes[info.start].edges[i];
	paths.data = ft_realloc(paths.data, 8 * (path_count + 1), 8 * path_count);
	paths.data[path_count] = (ssize_t *)malloc(sizeof(ssize_t)
			* info.node_count);
	paths.data[path_count][0] = info.start;
	paths.data[path_count][1] = current_node;
	while (current_node != info.end)
	{
		x = 0;
		while (nodes[current_node].flows[x] != 1)
			x++;
		if (x == nodes[current_node].edge_count)
			break ;
		paths.data[path_count][len] = nodes[current_node].edges[x];
		current_node = nodes[current_node].edges[x];
		len++;
	}
	paths.size = ft_realloc(paths.size, sizeof(ssize_t)
			* (path_count + 1), sizeof(ssize_t) * path_count);
	paths.size[path_count] = len;
	return (paths);
}

void	create_path(t_path paths[2], t_node *nodes, t_info info)
{
	size_t	path_count;
	size_t	i;

	path_count = 0;
	i = 0;
	while (i != nodes[info.start].edge_count)
	{
		if (nodes[info.start].flows[i] == 1)
		{
			paths[1] = alloc_path(nodes, info, path_count, i);
			path_count++;
		}
		i++;
	}
	paths[1].path_count = path_count;
	paths[1].latency = calculate_latency(paths[1].size,
			info.ant_count, path_count);
}

size_t	cmp_latency(size_t path_count, size_t *sizes, size_t *sizes_copy)
{
	size_t	x;
	size_t	latency;

	x = 1;
	latency = sizes_copy[0] + sizes[0];
	while (x != path_count)
	{
		if (latency < sizes_copy[x] + sizes[x])
			latency = sizes_copy[x] + sizes[x];
		x++;
	}
	return (latency);
}

