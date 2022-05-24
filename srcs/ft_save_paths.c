/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinnune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:31:43 by vkinnune          #+#    #+#             */
/*   Updated: 2022/05/24 15:37:17 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_path	*save_paths(t_room **pp_rooms, t_info info,
		t_path *paths, size_t set_count)
{
	t_stack	visited;
	size_t	max_count;

	ft_bzero(&visited, sizeof(t_stack));
	paths = allocate_new_path(paths, set_count);
	max_count = (*pp_rooms)[info.start].edge_count;
	while (paths[set_count].count != max_count)
	{
		allocate_path_data(&paths[set_count], paths[set_count].count);
		if (!mark_path(&visited, pp_rooms, info, &paths[set_count]))
			break ;
		paths[set_count].count++;
	}
	free(visited.data);
	return (paths);
}

void	allocate_path_data(t_path *paths, size_t count)
{
	size_t	**cpy_data;
	size_t	*cpy_sizes;

	if (count == 0)
	{
		paths->data = (size_t **)malloc(1 * sizeof(size_t *));
		paths->sizes = (size_t *)malloc(1 * sizeof(size_t));
		ft_bzero(paths->data, sizeof(size_t *));
		ft_bzero(paths->sizes, sizeof(size_t));
	}
	else
	{
		cpy_data = (size_t **)malloc((count + 1) * sizeof(size_t *));
		cpy_sizes = (size_t *)malloc((count + 1) * sizeof(size_t));
		ft_bzero(cpy_data, sizeof(size_t *) * (count + 1));
		ft_bzero(cpy_sizes, sizeof(size_t *) * (count + 1));
		ft_memcpy(cpy_data, paths->data, sizeof(size_t *) * count);
		ft_memcpy(cpy_sizes, paths->sizes, sizeof(size_t) * count);
		free(paths->data);
		free(paths->sizes);
		paths->data = cpy_data;
		paths->sizes = cpy_sizes;
	}
}

t_path	*allocate_new_path(t_path *paths, size_t set_count)
{
	t_path	*cpy;

	if (set_count == 0)
	{
		paths = (t_path *)malloc(sizeof(t_path) * 1);
		ft_bzero(paths, sizeof(t_path) * 1);
	}
	else
	{
		cpy = (t_path *)malloc(sizeof(t_path) * (set_count + 1));
		ft_bzero(cpy, sizeof(t_path) * (set_count + 1));
		ft_memcpy(cpy, paths, sizeof(t_path) * set_count);
		free(paths);
		paths = cpy;
	}
	return (paths);
}

