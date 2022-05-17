#include "lem-in.h"

void	allocate_path_data(t_path *paths, size_t count);
t_path	*allocate_new_path(t_path *paths, size_t set_count);
void	mark_flow(t_room **pp_rooms, t_info info);
void	add_flow(size_t current_node, size_t prev_node, t_room **pp_rooms);
void	negative_path(size_t current_node, size_t prev_node, t_room **pp_rooms);
size_t	next_node(t_room **pp_rooms, size_t current_node);
int	mark_path(t_stack *visited, t_room **pp_rooms, t_info info, t_path *paths);

t_path	*save_paths(t_room **pp_rooms, t_info info, t_path *paths, size_t set_count)
{
	t_stack	visited;

	bzero(&visited, sizeof(t_stack));
	paths = allocate_new_path(paths, set_count);
	while (1)
	{
		allocate_path_data(&paths[set_count], paths[set_count].count);
		if (!mark_path(&visited, pp_rooms, info, &paths[set_count]))
			break ;
		paths[set_count].count++;
	}
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
		bzero(paths->data, sizeof(size_t *));
		bzero(paths->sizes, sizeof(size_t));
	}
	else
	{
		cpy_data = (size_t **)malloc((count + 1) * sizeof(size_t *));
		cpy_sizes = (size_t *)malloc((count + 1) * sizeof(size_t));
		bzero(cpy_data, sizeof(size_t *) * (count + 1));
		bzero(cpy_sizes, sizeof(size_t *) * (count + 1));
		memcpy(cpy_data, paths->data, sizeof(size_t *) * count);
		memcpy(cpy_sizes, paths->sizes, sizeof(size_t) * count);
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
		bzero(paths, sizeof(t_path) * 1);
	}
	else
	{
		cpy = (t_path *)malloc(sizeof(t_path) * (set_count + 1));
		bzero(cpy, sizeof(t_path) * (set_count + 1));
		memcpy(cpy, paths, sizeof(t_path) * set_count);
		free(paths);
		paths = cpy;
	}
	return (paths);
}
