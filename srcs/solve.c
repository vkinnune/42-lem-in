#include "lem-in.h"

void	add_edges_to_queue(size_t current_node, t_room **pp_rooms, t_bfs *p_traversal_data);
int	not_visited(size_t edge, size_t *visited_stack, size_t visited_size);
int	delete_first_element(t_bfs *p_traversal_data);
size_t	get_distance(size_t current_node, t_room **pp_rooms, t_bfs *p_traversal_data);
int	traverse_nodes(t_room **pp_rooms, t_info info, t_bfs *p_traversal_data);
void	alloc_flows(t_room *p_rooms, size_t room_count);
void	mark_flow(t_room **pp_rooms, t_info info);
size_t	next_node(t_room **pp_rooms, size_t current_node);
void	add_flow(size_t current_node, size_t prev_node, t_room **pp_rooms);
t_path	*allocate_new_path(t_path *paths, size_t set_count);
int	edge_not_visited(t_stack *visited, size_t edge);
void	add_to_visited(t_stack *visited, size_t current_node);
void	add_to_path(t_path *paths, size_t current_node);
void	allocate_path_data(t_path *paths, size_t count);
ssize_t	next_flow_node(t_stack *visited, t_room **pp_rooms, size_t current_node);
int	mark_path(t_stack *visited, t_room **pp_rooms, t_info info, t_path *paths);
void	clear_distance(t_room **pp_rooms, size_t room_count);
t_path	*save_paths(t_room **pp_rooms, t_info info, t_path *paths, size_t set_count);
int	not_in_path(t_room **pp_rooms, size_t current_node, size_t index_edges);
void	negative_path(size_t current_node, size_t prev_node, t_room **pp_rooms);
t_path	*make_paths(t_path *paths, size_t *set_count, t_info info, t_room *p_rooms);
void	calculate_latency(t_info info, t_path *paths, size_t set_count);
size_t	get_set(t_path *paths, size_t set_count);
char	*construct_instructions(t_path *paths, size_t set_count, char *p_names, t_info info);
size_t	*get_flow(t_path *path, size_t ant_count);
size_t	add_ants(size_t *flow, size_t path_index);
char	*build_str(size_t ant, char *name, char *str);

char	*move_ants(t_info info, char *p_names, t_room *p_rooms)
{
	t_path	*paths;
	size_t	set_count;
	char	*res;

	set_count = 0;
	paths = make_paths(paths, &set_count, info, p_rooms);
	res = construct_instructions(paths, set_count, p_names, info);
	free(paths);
	return (res);
}

char	*construct_instructions(t_path *paths, size_t set_count, char *p_names, t_info info)
{
	char	*str;
	size_t	*flow;
	size_t	set;
	size_t	i;
	size_t	ant;
	size_t	res;
	size_t	tick;
	size_t	pos;

	i = 0;
	tick = 1;
	set = get_set(paths, set_count);
	flow = get_flow(&paths[set], info.ant_count);
	str = 0;
	while (1)
	{
		i = 0;
		res = 0;
		while (i != paths[set].count)
		{
			ant = 1;
			while (ant <= flow[i])
			{
				pos = tick - ant;
				if (pos >= 0 && pos < paths[set].sizes[i])
					str = build_str(ant + add_ants(flow, i), &p_names[paths[set].data[i][pos] * NAME_LENGTH], str);
				else
					res++;
				if (res >= info.ant_count)
					return (str);
				ant++;
			}
			i++;
		}
		{
			char *p;

			p = str;
			while (*p != 0)
				p++;
			p--;
			*p = '\n';
		}
		tick++;
	}
}

char	*build_str(size_t ant, char *name, char *str)
{
	char	buf[1000];
	char	*p;

	{
		p = buf;
		*p = 'L';
		p++;
		{
			char	num[100];
			char	*p_num;

			p_num = &num[100 - 1];
			*p_num = 0;
			p_num--;
			while (ant)
			{
				*p_num = (ant % 10) + '0';
				ant /= 10;
				p_num--;
			}
			p_num++;
			strcpy(p, p_num);
			while (*p != 0)
				p++;
		}
		*p = '-';
		p++;
		strcpy(p, name);
		while (*p != 0)
			p++;
		*p = ' ';
		p++;
		*p = 0;
	}
	{
		char	*cpy;

		if (str == 0)
		{
			str = (char *)malloc(((strlen(buf)) + 1)* sizeof(char));
			strcpy(str, buf);
		}
		else
		{
			cpy = (char *)malloc(((strlen(str) + strlen(buf) + 1) * sizeof(char)));
			strcpy(cpy, str);
			strcat(cpy, buf);
			free(str);
			str = cpy;
		}
	}
	return (str);
}

size_t	add_ants(size_t *flow, size_t path_index)
{
	size_t	res;
	size_t	i;

	res = 0;
	i = 0;
	while (i != path_index)
	{
		res += flow[i];
		i++;
	}
	return (res);
}

size_t	*get_flow(t_path *path, size_t ant_count)
{
	size_t	*flow;
	size_t	path_count;
	size_t	save_index;
	size_t	*sizes;
	size_t	i;

	sizes = path->sizes;
	path_count = path->count;
	flow = (size_t *)malloc(path_count * sizeof(size_t));
	bzero(flow, path_count * sizeof(size_t));
	while (ant_count)
	{
		i = 0;
		save_index = 0;
		while (i != path_count)
		{
			if ((flow[save_index] + sizes[save_index]) > (flow[i] + sizes[i]))
				save_index = i;
			i++;
		}
		flow[save_index]++;
		ant_count--;
	}
	return (flow);
}

size_t	get_set(t_path *paths, size_t set_count)
{
	ssize_t	latency;
	ssize_t	save_i;
	size_t	i;

	latency = INT_MAX;
	i = 0;
	save_i = -1;
	while (i != set_count)
	{
		if (paths[i].latency < latency && paths[i].latency >= 0)
		{
			latency = paths[i].latency;
			save_i = i;
		}
		i++;
	}
	if (save_i == -1)
		ft_out("Error on getting a set");
	return (save_i);
}

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

t_path	*save_paths(t_room **pp_rooms, t_info info, t_path *paths, size_t set_count)
{
	t_stack	visited;
	size_t	path_count;

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
		bzero(paths->sizes, sizeof(size_t *));
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

int	mark_path(t_stack *visited, t_room **pp_rooms, t_info info, t_path *paths)
{
	ssize_t	current_node;

	current_node = (ssize_t)info.start;
	while (current_node != info.end)
	{
		add_to_visited(visited, current_node);
		if (current_node != info.start)
			add_to_path(paths, current_node);
		current_node = next_flow_node(visited, pp_rooms, current_node);
		if (current_node == -1)
			return (0);
	}
	add_to_path(paths, current_node);
	return (1);
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
		memcpy(cpy, paths->data[count], sizeof(size_t) * paths->sizes[count]);
		free(paths->data[count]);
		paths->data[count] = cpy;
	}
	paths->data[count][paths->sizes[count]] = current_node;
	paths->sizes[count]++;
}

ssize_t	next_flow_node(t_stack *visited, t_room **pp_rooms, size_t current_node)
{
	size_t	i;
	size_t	*edges;
	size_t	*flows;
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

void	add_to_visited(t_stack *visited, size_t current_node)
{
	size_t	*cpy;

	if (visited->size == 0)
		visited->data = (size_t *)malloc(sizeof(size_t) * 1);
	else
	{
		cpy = (size_t *)malloc(sizeof(size_t) * (visited->size + 1));
		memcpy(cpy, visited->data, sizeof(size_t) * visited->size);
		free(visited->data);
		visited->data = cpy;
	}
	visited->data[visited->size] = current_node;
	visited->size++;
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

void	mark_flow(t_room **pp_rooms, t_info info)
{
	size_t	current_node;
	size_t	prev_node;

	current_node = info.end;
	while (current_node != info.start)
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
	ft_out("Error adding flow");
}

void	negative_path(size_t current_node, size_t prev_node, t_room **pp_rooms)
{
	size_t	*edges;
	size_t	*flows;
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
	ft_out("Error finding next node");
	return (-1);
}

void	alloc_flows(t_room *p_rooms, size_t room_count)
{
	size_t	i;
	size_t	edge_count;

	i = 0;
	while (i != room_count)
	{
		edge_count = p_rooms[i].edge_count;
		p_rooms[i].flows = (size_t *)malloc(sizeof(size_t) * edge_count);
		bzero(p_rooms[i].flows, sizeof(size_t) * edge_count);
		i++;
	}
}

int	traverse_nodes(t_room **pp_rooms, t_info info, t_bfs *p_traversal_data)
{
	size_t	current_node;

	current_node = info.start;
	(*pp_rooms)[current_node].distance = 1;
	while (current_node != info.end)
	{
		add_edges_to_queue(current_node, pp_rooms, p_traversal_data);
		p_traversal_data->visited_stack[p_traversal_data->visited_size++] = current_node;
		current_node = p_traversal_data->queue_stack[0];
		(*pp_rooms)[current_node].distance = get_distance(current_node, pp_rooms, p_traversal_data);
		if (!delete_first_element(p_traversal_data))
			return (0);
	}
	return (1);
}

size_t	get_distance(size_t current_node, t_room **pp_rooms, t_bfs *p_traversal_data)
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
	size_t	edge_count;
	size_t	*edges;
	size_t	x;

	x = 0;
	edge_count = (*pp_rooms)[current_node].edge_count;
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
	ft_out("Bad happen in not in path");
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
		ft_out("Error solving");
	return (1);
}

void	add_edges_to_queue(size_t current_node, t_room **pp_rooms, t_bfs *p_traversal_data)
{
	size_t	edge_count;
	size_t	*edges;
	size_t	*flows;
	size_t	i;

	edge_count = (*pp_rooms)[current_node].edge_count;
	edges = (*pp_rooms)[current_node].edges;
	flows = (*pp_rooms)[current_node].flows;
	i = 0;
	while (i != edge_count)
	{
		if (flows[i] == 0 && not_visited(edges[i], p_traversal_data->visited_stack, p_traversal_data->visited_size) &&
				not_visited(edges[i], p_traversal_data->queue_stack, p_traversal_data->queue_size))
		{
			p_traversal_data->queue_stack[p_traversal_data->queue_size] = edges[i];
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

