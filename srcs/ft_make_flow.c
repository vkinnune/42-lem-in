/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_flow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinnune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:30:56 by vkinnune          #+#    #+#             */
/*   Updated: 2022/05/24 15:35:27 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	mark_flow(t_room **pp_rooms, t_info info)
{
	size_t	current_node;
	size_t	prev_node;

	current_node = info.end;
	while (current_node != (size_t)info.start)
	{
		prev_node = current_node;
		current_node = next_node(pp_rooms, current_node);
		add_flow(current_node, prev_node, pp_rooms);
	}
}

void	add_flow(size_t current_node, size_t prev_node, t_room **pp_rooms)
{
	size_t	i;
	size_t	edge_count;
	size_t	*edges;

	i = 0;
	edge_count = (*pp_rooms)[current_node].edge_count;
	edges = (*pp_rooms)[current_node].edges;
	while (i != edge_count)
	{
		if (edges[i] == prev_node)
		{
			negative_path(current_node, prev_node, pp_rooms);
			(*pp_rooms)[current_node].flows[i] = 1;
			return ;
		}
		i++;
	}
	ft_out("ERROR");
}

void	negative_path(size_t current_node, size_t prev_node, t_room **pp_rooms)
{
	size_t	*edges;
	ssize_t	*flows;
	size_t	edge_count;
	size_t	i;

	edges = (*pp_rooms)[prev_node].edges;
	flows = (*pp_rooms)[prev_node].flows;
	edge_count = (*pp_rooms)[prev_node].edge_count;
	i = 0;
	while (i != edge_count)
	{
		if (edges[i] == current_node)
		{
			if (flows[i] != 0)
				flows[i] = 2;
			break ;
		}
		i++;
	}
}

size_t	next_node(t_room **pp_rooms, size_t current_node)
{
	size_t	i;
	size_t	*edges;
	size_t	edge_count;
	size_t	res;

	i = 0;
	res = (*pp_rooms)[current_node].distance;
	edges = (*pp_rooms)[current_node].edges;
	edge_count = (*pp_rooms)[current_node].edge_count;
	while (i != edge_count)
	{
		if ((*pp_rooms)[edges[i]].distance == (res - 1))
			return (edges[i]);
		i++;
	}
	ft_out("ERROR");
	return (-1);
}
