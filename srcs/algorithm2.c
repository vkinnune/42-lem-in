/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinnune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:06:52 by vkinnune          #+#    #+#             */
/*   Updated: 2022/10/17 15:12:36 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdio.h>

int64_t	calculate_latency(int64_t *sizes, uint64_t ant_count, uint64_t path_count)
{
	uint64_t	i;
	uint64_t	x;
	uint64_t	save;
	uint64_t	latency;
	int64_t	*sizes_copy;

	i = 0;
	save = 0;
	sizes_copy = (int64_t *)malloc(sizeof(uint64_t *) * path_count);
	ft_bzero(sizes_copy, sizeof(uint64_t *) * path_count);
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
	free(sizes_copy);
	return (latency);
}

void	augment(t_node *nodes, t_info info)
{
	int64_t	current_node;
	int64_t	next_node;
	int64_t	path_id;

	current_node = info.end;
	path_id = nodes[current_node].prev_node;
	while (current_node != info.start)
	{
		nodes[current_node].path_id = path_id;
		next_node = nodes[current_node].prev_node;
		nodes[current_node].flow = true;
		nodes[next_node].flows[find_edge_id(current_node,
				next_node, nodes)] = 1;
		if (nodes[current_node].flows[find_edge_id(next_node,
					current_node, nodes)] == 1)
		{
			nodes[current_node].flows[find_edge_id(next_node,
					current_node, nodes)] = -1;
			nodes[next_node].flows[find_edge_id(current_node,
					next_node, nodes)] = -1;
		}
		current_node = next_node;
	}
}

int64_t	find_edge_id(int64_t current_node, int64_t next_node, t_node *nodes)
{
	uint64_t	i;

	i = 0;
	while (i != nodes[next_node].edge_count)
	{
		if (nodes[next_node].edges[i] == current_node)
			break ;
		i++;
	}
	return (i);
}

void	init_bfs(t_node *nodes, t_info info, int64_t *current_node)
{
	*current_node = info.start;
	nodes[*current_node].prev_node = info.start;
	nodes[*current_node].path_id = info.start;
}

int	bfs(t_node *nodes, t_info info)
{
	int64_t	current_node;
	t_stack	queue;
	int64_t	prev_node;
	int		ret;

	queue.data = (uint64_t *)malloc((sizeof(uint64_t) * info.node_count * 300));
	queue.size = 0;
	init_bfs(nodes, info, &current_node);
	prev_node = -1;
	ret = 0;
	while (ret != 2)
	{
		prev_node = nodes[current_node].prev_node;
		if (!(nodes[current_node].flow == true
				&& nodes[prev_node].flow == false))
			nodes[current_node].path_id = nodes[prev_node].path_id;
		ret = add_to_queue(current_node, prev_node, nodes, &queue, info);
		if (ret == 0)
			break ;
		current_node = delete_from_queue(&queue);
	}
	free(queue.data);
	if (ret == 0)
		return (0);
	return (1);
}

