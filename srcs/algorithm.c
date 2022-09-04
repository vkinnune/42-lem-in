#include "lem_in.h"

t_path	find_augmenting_paths(t_node *nodes, t_info info)
{
	t_path	paths[2];
	size_t	i;

	i = 0;
	ft_bzero(paths, sizeof(t_path) * 2);
	paths[0].latency = INT_MAX;
	while (i != info.node_count)
	{
		nodes[i].flows = (ssize_t *)malloc(sizeof(ssize_t) * nodes[i].edge_count);
		ft_bzero(nodes[i].flows, sizeof(ssize_t) * nodes[i].edge_count);
		i++;
	}
	while (1)
	{
		i = 0;
		while (i != info.node_count)
		{
			nodes[i].depth = 0;
			nodes[i].visited = false;
			i++;
		}
		if (!augment_path(nodes, info))
			break ;
		convert_route_to_flow(nodes, info);
		create_path(paths, nodes, info);
		if (paths[1].latency < paths[0].latency)
			paths[0] = paths[1];
	}
	return (paths[0]);
}

void	create_path(t_path paths[2], t_node *nodes, t_info info)
{
	size_t	path_count;
	size_t	i;
	size_t	x;
	size_t	current_node;
	size_t	len;

	path_count = 0;
	i = 0;
	while (i != nodes[info.start].edge_count)
	{
		if (nodes[info.start].flows[i] == 1)
		{
			current_node = nodes[info.start].edges[i];
			len = 2;
			paths[1].data = ft_realloc(paths[1].data, sizeof(ssize_t *) * (path_count + 1), sizeof(ssize_t *) * path_count);
			paths[1].data[path_count] = (ssize_t *)malloc(sizeof(ssize_t) * info.node_count);
			paths[1].data[path_count][0] = info.start;
			paths[1].data[path_count][1] = current_node;
			while (current_node != info.end)
			{
				x = 0;
				while (nodes[current_node].flows[x] != 1)
					x++;
				paths[1].data[path_count][len] = nodes[current_node].edges[x];
				current_node = nodes[current_node].edges[x];
				len++;
			}
			paths[1].size = ft_realloc(paths[1].size, sizeof(ssize_t) * (path_count + 1), sizeof(ssize_t) * path_count);
			paths[1].size[path_count] = len;
			path_count++;
		}
		i++;
	}
	paths[1].path_count = path_count;
	paths[1].latency = calculate_latency(paths[1].size, info.ant_count, path_count);
}

ssize_t	calculate_latency(size_t *sizes, size_t ant_count, size_t path_count)
{
	size_t	i;
	size_t	x;
	size_t	save;
	size_t	latency;
	size_t	*sizes_copy;

	i = 0;
	save = 0;
	sizes_copy = (size_t *)malloc(sizeof(size_t *) * path_count);
	ft_bzero(sizes_copy, sizeof(size_t *) * path_count);
	while (i != ant_count)
	{
		x = 0;
		while (x != path_count)
		{
			if (sizes_copy[x] + sizes[x] < sizes_copy[save] + sizes[save])
				save = x;
			x++;
		}
		sizes_copy[save]++;
		i++;
	}
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

void	convert_route_to_flow(t_node *nodes, t_info info)
{
	ssize_t current_node;
	ssize_t next_node;

	current_node = info.end;
	while (current_node != info.start)
	{
		nodes[current_node].flow = true;
		next_node = go_deeper(nodes, info, current_node);
		nodes[next_node].flows[find_edge_id(current_node, next_node, nodes)] = 1;
		if (nodes[current_node].flows[find_edge_id(next_node, current_node, nodes)] == 1)
		{
			nodes[current_node].flows[find_edge_id(next_node, current_node, nodes)] = -1;
			nodes[next_node].flows[find_edge_id(current_node, next_node, nodes)] = -1;
		}
		current_node = next_node;
	}
}

ssize_t	find_edge_id(ssize_t current_node, ssize_t next_node, t_node *nodes)
{
	size_t	i;

	i = 0;
	while (i != nodes[next_node].edge_count)
	{
		if (nodes[next_node].edges[i] == current_node)
			break ;
		i++;
	}
	return (i);
}

ssize_t	go_deeper(t_node *nodes, t_info info, size_t current_node)
{
	size_t	i;

	i = 0;
	while (i != nodes[current_node].edge_count)
	{
		if (nodes[nodes[current_node].edges[i]].depth == (nodes[current_node].depth - 1))
			break ;
		i++;
	}
	return (nodes[current_node].edges[i]);
}

int	augment_path(t_node *nodes, t_info info)
{
	ssize_t	current_node;
	t_stack	visited;
	t_stack	queue;
	ssize_t	prev_node;

	queue.data = (size_t *)malloc((sizeof(size_t) * info.node_count * 100));
	queue.size = 0;
	current_node = info.start;
	prev_node = -1;
	while (1)
	{
		nodes[current_node].depth = get_depth(nodes, current_node);
		nodes[current_node].visited = true;
		if (current_node == info.end)
			break ;
		if (!add_to_queue(current_node, prev_node, nodes, &queue))
			return (0);
		prev_node = current_node;
		current_node = delete_from_queue(&queue);
	}
	return (1);
}

size_t	get_depth(t_node *nodes, ssize_t current_node)
{
	size_t	i;
	size_t	depth;

	i = 0;
	depth = INT_MAX;
	while (i != nodes[current_node].edge_count)
	{
		if (nodes[nodes[current_node].edges[i]].depth < depth && nodes[nodes[current_node].edges[i]].visited == true &&
				nodes[nodes[current_node].edges[i]].flows[find_edge_id(current_node, nodes[current_node].edges[i], nodes)] != 1)
			depth = nodes[nodes[current_node].edges[i]].depth;
		i++;
	}
	if (depth == INT_MAX)
		return (0);
	else
		return (depth + 1);
}

ssize_t	delete_from_queue(t_stack *queue)
{
	size_t	i;
	ssize_t	ret;

	i = 0;
	ret = queue->data[0];
	while (i != (queue->size - 1))
	{
		queue->data[i] = queue->data[i + 1];
		i++;
	}
	queue->size--;
	return (ret);
}

int	add_to_queue(ssize_t current_node, ssize_t prev_node, t_node *nodes, t_stack *queue)
{
	size_t	i;

	i = 0;
	while (i != nodes[current_node].edge_count)
	{
		if (nodes[current_node].flows[i] == 0 && nodes[nodes[current_node].edges[i]].visited == false)
			queue->data[queue->size++] = nodes[current_node].edges[i];
		i++;
	}
	if (queue->size == 0)
		return (0);
	else
		return (1);
}

