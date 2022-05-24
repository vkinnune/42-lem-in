/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traverse_nodes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinnune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:31:56 by vkinnune          #+#    #+#             */
/*   Updated: 2022/05/24 15:37:30 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	traverse_nodes(t_room **pp_rooms, t_info info, t_bfs *p_traversal_data)
{
	size_t	current_node;

	current_node = info.start;
	(*pp_rooms)[current_node].distance = 1;
	while (current_node != info.end)
	{
		add_edges_to_queue(current_node, pp_rooms, p_traversal_data);
		p_traversal_data->visited_stack[p_traversal_data->visited_size++]
			= current_node;
		current_node = p_traversal_data->queue_stack[0];
		(*pp_rooms)[current_node].distance
			= get_distance(current_node, pp_rooms);
		if (!delete_first_element(p_traversal_data))
			return (0);
	}
	return (1);
}

size_t	get_distance(size_t current_node, t_room **pp_rooms)
{
	size_t	index_edges;
	size_t	edge_count;
	size_t	distance;
	size_t	*edges;
	size_t	res;

	edges = (*pp_rooms)[current_node].edges;
	edge_count = (*pp_rooms)[current_node].edge_count;
	index_edges = 0;
	res = INT_MAX;
	while (index_edges != edge_count)
	{
		if (not_in_path(pp_rooms, current_node, index_edges))
		{
			distance = (*pp_rooms)[edges[index_edges]].distance;
			if (distance < res && distance > 0)
				res = distance;
		}
		index_edges++;
	}
	return (res + 1);
}

int	not_in_path(t_room **pp_rooms, size_t current_node, size_t index_edges)
{
	size_t	*edges;
	size_t	x;

	x = 0;
	edges = (*pp_rooms)[current_node].edges;
	while (x != (*pp_rooms)[edges[index_edges]].edge_count)
	{
		if ((*pp_rooms)[edges[index_edges]].edges[x] == current_node)
		{
			if ((*pp_rooms)[edges[index_edges]].flows[x] == 0)
				return (1);
			else
				return (0);
			break ;
		}
		x++;
	}
	ft_out("Error");
	return (-1);
}

int	delete_first_element(t_bfs *p_traversal_data)
{
	size_t	i;

	i = 0;
	if (p_traversal_data->queue_size == 0)
		return (0);
	while (i != p_traversal_data->queue_size)
	{
		p_traversal_data->queue_stack[i] = p_traversal_data->queue_stack[i + 1];
		i++;
	}
	if (p_traversal_data->queue_size > 0)
		p_traversal_data->queue_size--;
	else
		ft_out("Error");
	return (1);
}
