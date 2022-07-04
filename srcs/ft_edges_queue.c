/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_edges_queue.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinnune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:30:26 by vkinnune          #+#    #+#             */
/*   Updated: 2022/07/04 16:47:59 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	add_edges_to_queue(size_t current_node,
			t_room **pp_rooms, t_bfs *p_traversal_data)
{
	size_t	edge_count;
	size_t	*edges;
	ssize_t	*flows;
	size_t	i;

	edge_count = (*pp_rooms)[current_node].edge_count;
	edges = (*pp_rooms)[current_node].edges;
	flows = (*pp_rooms)[current_node].flows;
	i = 0;
	while (i != edge_count)
	{
		if (flows[i] <= 0 && not_visited(edges[i],
				p_traversal_data->visited_stack,
				p_traversal_data->visited_size)
			&& not_visited(edges[i], p_traversal_data->queue_stack,
				p_traversal_data->queue_size)
			&& (((*pp_rooms)[edges[i]].visited == true && flows[i] == -1)
			|| ((*pp_rooms)[edges[i]].visited == false && flows[i] == 0)))
		{
			p_traversal_data->queue_stack[p_traversal_data->queue_size]
				= edges[i];
			p_traversal_data->queue_size++;
		}
		i++;
	}
}

int	not_visited(size_t edge, size_t *visited_stack, size_t visited_size)
{
	size_t	i;

	i = 0;
	while (i != visited_size)
	{
		if (edge == visited_stack[i])
			return (0);
		i++;
	}
	return (1);
}
