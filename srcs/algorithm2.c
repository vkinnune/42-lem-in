#include "lem_in.h"

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
	latency = cmp_latency(path_count, sizes, sizes_copy);
	return (latency);
}

void	convert(t_node *nodes, t_info info)
{
	ssize_t	current_node;
	ssize_t	next_node;

	current_node = info.end;
	while (current_node != info.start)
	{
		nodes[current_node].flow = true;
		next_node = go_deeper(nodes, info, current_node);
		nodes[next_node].in[find_edge_id(current_node,
				next_node, nodes)] = 1; //confirms flow
		if (nodes[current_node].out[find_edge_id(next_node,
					current_node, nodes)] == 1)
		{
			nodes[current_node].out[find_edge_id(next_node,
					current_node, nodes)] = 0;
			nodes[next_node].out[find_edge_id(current_node,
					next_node, nodes)] = 0;
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
		if (nodes[current_node].depth - 1 == nodes[nodes[current_node].edges[i]].depth)
			break ;
		i++;
	}
	if (i == nodes[current_node].edge_count)
		ft_out("ERROR");
	return (nodes[current_node].edges[i]);
}

int	augment(t_node *nodes, t_info info)
{
	ssize_t	current_node;
	t_stack	visited;
	t_stack	queue;
	ssize_t	prev_node;

	queue.data = (size_t *)malloc((sizeof(size_t) * info.node_count * 300));
	queue.size = 0;
	current_node = info.start;
	nodes[current_node].prev_node = info.start;
	prev_node = -1;
	while (1)
	{
		nodes[current_node].depth = get_depth(nodes, current_node);
		if (current_node == info.end)
			break ;
		prev_node = nodes[current_node].prev_node;
		if (!add_to_queue(current_node, prev_node, nodes, &queue, info))
			return (0);
		current_node = delete_from_queue(&queue);
		nodes[nodes[current_node].prev_node].out[find_edge_id(nodes[current_node].prev_node, current_node, nodes)] = 1;
	}
	free(queue.data);
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
		if (nodes[nodes[current_node].edges[i]].depth < depth && nodes[nodes[current_node].edges[i]].depth == -1 &&
				nodes[nodes[current_node].edges[i]].in[find_edge_id(current_node, nodes[current_node].edges[i], nodes)] != 1)
			depth = nodes[nodes[current_node].edges[i]].depth;
		i++;
	}
	if (depth == INT_MAX)
		return (0);
	else
		return (depth + 1);
}

