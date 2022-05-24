/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mark_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinnune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:31:21 by vkinnune          #+#    #+#             */
/*   Updated: 2022/05/24 16:31:55 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	mark_path(t_stack *visited, t_room **pp_rooms, t_info info, t_path *paths)
{
	ssize_t	current_node;

	current_node = (ssize_t)info.start;
	while (current_node != (ssize_t)info.end)
	{
		add_to_visited(visited, current_node);
		if (current_node != (ssize_t)info.start)
			add_to_path(paths, current_node);
		current_node = next_flow_node(visited, pp_rooms, current_node);
		if (current_node == -1)
			return (0);
	}
	add_to_path(paths, current_node);
	return (1);
}

void	add_to_visited(t_stack *visited, size_t current_node)
{
	size_t	*cpy;

	if (visited->size == 0)
		visited->data = (size_t *)malloc(sizeof(size_t) * 1);
	else
	{
		cpy = (size_t *)malloc(sizeof(size_t) * (visited->size + 1));
		ft_memcpy(cpy, visited->data, sizeof(size_t) * visited->size);
		free(visited->data);
		visited->data = cpy;
	}
	visited->data[visited->size] = current_node;
	visited->size++;
}

ssize_t	next_flow_node(t_stack *visited, t_room **pp_rooms, size_t current_node)
{
	size_t	i;
	size_t	*edges;
	ssize_t	*flows;
	size_t	edge_count;

	i = 0;
	edge_count = (*pp_rooms)[current_node].edge_count;
	edges = (*pp_rooms)[current_node].edges;
	flows = (*pp_rooms)[current_node].flows;
	while (i != edge_count)
	{
		if (flows[i] == 1 && edge_not_visited(visited, edges[i]))
			return ((ssize_t)edges[i]);
		i++;
	}
	return (-1);
}

void	add_to_path(t_path *paths, size_t current_node)
{
	size_t	count;
	size_t	*cpy;

	count = paths->count;
	if (paths->sizes[count] == 0)
		paths->data[count] = (size_t *)malloc(sizeof(size_t) * 1);
	else
	{
		cpy = (size_t *)malloc(sizeof(size_t) * (paths->sizes[count] + 1));
		ft_memcpy(cpy, paths->data[count],
			sizeof(size_t) * paths->sizes[count]);
		free(paths->data[count]);
		paths->data[count] = cpy;
	}
	paths->data[count][paths->sizes[count]] = current_node;
	paths->sizes[count]++;
}

int	edge_not_visited(t_stack *visited, size_t edge)
{
	size_t	i;

	i = 0;
	while (i != visited->size)
	{
		if (visited->data[i] == edge)
			return (0);
		i++;
	}
	return (1);
}
