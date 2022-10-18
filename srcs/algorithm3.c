/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinnune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:06:58 by vkinnune          #+#    #+#             */
/*   Updated: 2022/10/17 15:10:20 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int64_t	delete_from_queue(t_stack *queue)
{
	uint64_t	i;
	int64_t	ret;

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

int	super_long_if_statement(int64_t current_node,
		int64_t prev_node, t_node *nodes, uint64_t i)
{
	if (!(nodes[current_node].flow && nodes[nodes[current_node].edges[i]].flow
			&& nodes[current_node].path_id
			!= nodes[nodes[current_node].edges[i]].path_id)
		&& !(nodes[current_node].path_id
			== nodes[nodes[current_node].edges[i]].path_id
			&& !nodes[current_node].flow
			&& nodes[nodes[current_node].edges[i]].flow)
		&& !(nodes[nodes[current_node].edges[i]].prev_node != -1
			&& !nodes[nodes[current_node].edges[i]].flow)
		&& !nodes[nodes[current_node].edges[i]].visited
		&& !nodes[current_node].flows[i]
		&& (!nodes[current_node].flow
			|| (nodes[nodes[current_node].edges[i]].flow
				&& !nodes[prev_node].flow)
			|| (!nodes[nodes[current_node].edges[i]].flow
				&& nodes[prev_node].flow)))
		return (1);
	else
		return (0);
}

int	add_to_queue(int64_t current_node,
		int64_t prev_node, t_node *nodes, t_stack *queue)
{
	uint64_t	i;

	i = 0;
	while (i != nodes[current_node].edge_count)
	{
		if (super_long_if_statement(current_node, prev_node, nodes, i))
		{
			if (!(nodes[current_node].flow
					&& nodes[nodes[current_node].edges[i]].flow))
				nodes[current_node].visited = true;
			nodes[nodes[current_node].edges[i]].prev_node = current_node;
			queue->data[queue->size++] = nodes[current_node].edges[i];
			if (nodes[nodes[current_node].edges[i]].is_end)
				return (2);
		}
		i++;
	}
	if (queue->size <= 0)
		return (0);
	else
		return (1);
}

uint64_t	cmp_latency(uint64_t path_count, int64_t *sizes, int64_t *sizes_copy)
{
	uint64_t	x;
	int64_t	latency;

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

t_path	free_paths(t_path old_path, t_path new_path)
{
	uint64_t	i;
	t_path	temp;

	i = 0;
	if (new_path.latency > old_path.latency)
	{
		temp = new_path;
		new_path = old_path;
		old_path = temp;
	}
	if (old_path.path_count)
	{
		free(old_path.size);
		while (i != old_path.path_count)
		{
			free(old_path.data[i]);
			i++;
		}
		free(old_path.data);
	}
	return (new_path);
}

