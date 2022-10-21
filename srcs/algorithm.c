/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrummuka <jrummuka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:06:42 by vkinnune          #+#    #+#             */
/*   Updated: 2022/10/21 14:10:38 by jrummuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	alloc_flows(t_node *nodes, t_info info)
{
	uint64_t	i;

	i = 0;
	while (i != info.node_count)
	{
		nodes[i].flows = (int64_t *)ft_mc(sizeof(int64_t)
				* nodes[i].edge_count);
		nodes[i].path_id = -1;
		nodes[i].is_end = false;
		ft_bzero(nodes[i].flows, sizeof(int64_t) * nodes[i].edge_count);
		i++;
	}
	nodes[info.end].is_end = true;
	nodes[info.start].is_start = true;
}

t_path	find_augmenting_paths(t_node *nodes, t_info info)
{
	t_path		paths[2];
	uint64_t	i;

	ft_bzero(paths, sizeof(t_path) * 2);
	paths[0].latency = INT_MAX;
	alloc_flows(nodes, info);
	while (1)
	{
		i = 0;
		while (i != info.node_count)
		{
			nodes[i].visited = false;
			nodes[i].prev_node = -1;
			nodes[info.start].path_id = -1;
			nodes[info.end].path_id = -1;
			nodes[i].is_queue = false;
			i++;
		}
		if (!bfs(nodes, info))
			break ;
		augment(nodes, info);
		create_path(paths, nodes, info);
		paths[0] = free_paths(paths[0], paths[1]);
	}
	return (paths[0]);
}

t_path	init_alloc_path(t_info info, uint64_t path_count,
			uint64_t current_node, t_path paths)
{
	paths.data = ft_realloc(paths.data, 8 * (path_count + 1), 8 * path_count);
	paths.data[path_count] = (int64_t *)ft_mc(sizeof(int64_t)
			* info.node_count);
	paths.data[path_count][0] = info.start;
	paths.data[path_count][1] = current_node;
	return (paths);
}

t_path	alloc_path(t_node *nodes, t_info info,
			uint64_t path_count, t_path paths)
{
	int64_t		current_node;
	uint64_t	len;
	uint64_t	x;
	uint64_t	i;

	len = 2;
	i = info.i;
	current_node = nodes[info.start].edges[i];
	paths = init_alloc_path(info, path_count, current_node, paths);
	while (current_node != info.end)
	{
		x = 0;
		while (nodes[current_node].flows[x] != 1)
			x++;
		if (x == nodes[current_node].edge_count)
			break ;
		paths.data[path_count][len] = nodes[current_node].edges[x];
		current_node = nodes[current_node].edges[x];
		len++;
	}
	paths.size = ft_realloc(paths.size, sizeof(int64_t)
			* (path_count + 1), sizeof(int64_t) * path_count);
	paths.size[path_count] = len;
	return (paths);
}

void	create_path(t_path paths[2], t_node *nodes, t_info info)
{
	uint64_t	path_count;
	uint64_t	i;

	path_count = 0;
	i = 0;
	ft_bzero(&paths[1], sizeof(t_path));
	while (i != nodes[info.start].edge_count)
	{
		if (nodes[info.start].flows[i] == 1)
		{
			info.i = i;
			paths[1] = alloc_path(nodes, info, path_count, paths[1]);
			path_count++;
		}
		i++;
	}
	paths[1].path_count = path_count;
	paths[1].latency = calculate_latency(paths[1].size,
			info.ant_count, path_count);
}
