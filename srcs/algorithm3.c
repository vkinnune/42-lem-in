#include "lem_in.h"

size_t	get_depth(t_node *nodes, ssize_t current_node)
{
	size_t	i;
	size_t	depth;

	i = 0;
	depth = INT_MAX;
	while (i != nodes[current_node].edge_count)
	{
		if (nodes[nodes[current_node].edges[i]].depth < depth
			&& nodes[nodes[current_node].edges[i]].visited == true
			&& nodes[nodes[current_node].edges[i]].flows
			[find_edge_id(current_node, nodes[current_node].edges[i],
					nodes)] != 1)
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

int	not_in_queue(t_stack *queue, ssize_t current_node)
{
	size_t	i;

	i = 0;
	while (i != queue->size)
	{
		if (queue->data[i] == current_node)
			return (0);
		i++;
	}
	return (1);
}

int	add_to_queue(ssize_t current_node,
		ssize_t prev_node, t_node *nodes, t_stack *queue, t_info info)
{
	size_t	i;
	i = 0;
	while (i != nodes[current_node].edge_count)
	{
		if (	nodes[nodes[current_node].edges[i]].visited == false && nodes[current_node].flows[i] == 0 && (prev_node == -1 || nodes[current_node].flow == false
			|| (nodes[nodes[current_node].edges[i]].flows[find_edge_id(nodes[current_node].edges[i], current_node, nodes)] == true
			&& nodes[nodes[current_node].edges[i]].flow == true) || nodes[prev_node].flow == true))
		{
			nodes[nodes[current_node].edges[i]].prev_node = current_node;
			queue->data[queue->size++] = nodes[current_node].edges[i];
		}
		i++;
	}
	if (queue->size == 0)
		return (0);
	else
		return (1);
}

