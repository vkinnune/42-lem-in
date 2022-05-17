#include "lem-in.h"

void	alloc_flows(t_room *p_rooms, size_t room_count);
void	calculate_latency(t_info info, t_path *paths, size_t set_count);
void	clear_distance(t_room **pp_rooms, size_t room_count);
int	traverse_nodes(t_room **pp_rooms, t_info info, t_bfs *p_traversal_data);
void	mark_flow(t_room **pp_rooms, t_info info);
t_path	*save_paths(t_room **pp_rooms, t_info info, t_path *paths, size_t set_count);

t_path	*make_paths(t_path *paths, size_t *set_count, t_info info, t_room *p_rooms)
{
	t_bfs	traversal_data;

	traversal_data.visited_stack = (size_t *)malloc(sizeof(size_t) * info.room_count);
	traversal_data.queue_stack = (size_t *)malloc(sizeof(size_t) * info.room_count);
	alloc_flows(p_rooms, info.room_count);
	while (1)
	{
		traversal_data.visited_size = 0;
		traversal_data.queue_size = 0;
		if (!traverse_nodes(&p_rooms, info, &traversal_data))
			break ;
		mark_flow(&p_rooms, info);
		paths = save_paths(&p_rooms, info, paths, *set_count);
		calculate_latency(info, paths, *set_count);
		clear_distance(&p_rooms, info.room_count);
		(*set_count)++;
	}
	free(traversal_data.visited_stack);
	free(traversal_data.queue_stack); //remember to free flows
	return (paths);

}

void	calculate_latency(t_info info, t_path *paths, size_t set_count)
{
	size_t	latency;
	size_t	*sizes;
	size_t	ant_count;
	size_t	path_count;
	size_t	i;

	i = 0;
	latency = 0;
	sizes = paths[set_count].sizes;
	ant_count = info.ant_count;
	path_count = paths[set_count].count;
	while (i != path_count)
	{
		latency += sizes[i];
		i++;
	}
	latency = ant_count - latency;
	paths[set_count].latency = latency;
}

void	clear_distance(t_room **pp_rooms, size_t room_count)
{
	size_t	i;

	i = 0;
	while (i != room_count)
	{
		(*pp_rooms)[i].distance = 0;
		i++;
	}
}

void	alloc_flows(t_room *p_rooms, size_t room_count)
{
	size_t	i;
	size_t	edge_count;

	i = 0;
	while (i != room_count)
	{
		edge_count = p_rooms[i].edge_count;
		p_rooms[i].flows = (ssize_t *)malloc(sizeof(ssize_t) * edge_count);
		bzero(p_rooms[i].flows, sizeof(ssize_t) * edge_count);
		i++;
	}
}

