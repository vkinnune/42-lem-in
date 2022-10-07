#include "lem_in.h"
ssize_t	delete_from_queue(t_stack *queue) {
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

int	add_to_queue(ssize_t current_node,
		ssize_t prev_node, t_node *nodes, t_stack *queue, t_info info)
{
	size_t	i;
	i = 0;

	while (i != nodes[current_node].edge_count)
	{
		if (!(nodes[nodes[current_node].edges[i]].prev_node != -1 && nodes[nodes[current_node].edges[i]].flow == false) && nodes[nodes[current_node].edges[i]].visited == false && nodes[current_node].flows[i] == 0
		&& (nodes[current_node].flow == false || (nodes[nodes[current_node].edges[i]].flow == true && nodes[prev_node].flow == false)
		|| (nodes[nodes[current_node].edges[i]].flow == false && nodes[prev_node].flow == true)))
		{
			if (!(nodes[current_node].flow && nodes[nodes[current_node].edges[i]].flow))
				nodes[current_node].visited = true;
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

