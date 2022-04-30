#include "lem-in.h"

int		delete_first_element(t_stack *queue);
int		not_searched(int edge, t_stack *visited);
int		find_path(t_global *g, t_stack *visited, t_stack *queue);
int		get_depth(t_global *g, int current_node);
void	search_edges(t_room node, t_stack *visited, t_stack *queue, t_global *g);
void	create_path(t_global *g, t_stack visited, int depth);

int find_paths(int maxedges, t_global *g)
{
	t_stack	visited;
	t_stack	queue;
	int		i;
	unsigned int		depth;

	i = 0;
	depth = 0;
	visited.data = (unsigned int *)malloc((maxedges * g->room_count) * sizeof(unsigned int));
	queue.data = (unsigned int *)malloc((maxedges * g->room_count) * sizeof(unsigned int));
	g->paths = (t_path *)malloc(sizeof(t_path) * maxedges); //TODO Remember to free
	while (i != maxedges)
	{
		visited.size = 0;
		queue.size = 0;
		depth = find_path(g, &visited, &queue);
		if (!depth)
			break ;
		create_path(g, visited, (int)depth);
		i++;
	}
	free(visited.data);
	free(queue.data);
	return (i);
}

void	create_path(t_global *g, t_stack visited, int depth)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	current_node;

	g->paths[g->path_count].data = (unsigned int *)malloc(sizeof(unsigned int) * depth); //remember to free
	g->paths[g->path_count].visited = (unsigned int *)malloc(sizeof(unsigned int) * depth); //remember to free
	bzero(g->paths[g->path_count].visited, sizeof(unsigned int) * depth);
	g->paths[g->path_count].size = depth - 2;
	current_node = g->end;
	g->paths[g->path_count].data[depth - 2] = current_node;
	while (1)
	{
		j = 0;
		i = 0;
		while (1)
		{
			if (g->rooms[current_node].edges[i] == visited.data[j] && g->rooms[visited.data[j]].depth < (unsigned int)depth)
				break ;
			if (i == (g->rooms[current_node].edge_count - 1))
			{
				j++;
				i = 0;
				continue ;
			}
			i++;
		}
		current_node = g->rooms[current_node].edges[i];
		g->paths[g->path_count].data[depth - 3] = current_node; //TODO this is really bad thing fix this :(
		depth--;
		if ((int)current_node == g->start)
			break ;
		g->rooms[current_node].visited = true;
	}
	g->path_count++;
}

int	find_path(t_global *g, t_stack *visited, t_stack *queue)
{
	int	current_node;

	current_node = g->start;
	g->rooms[current_node].depth = 1;
	while (current_node != g->end)
	{
		//printf("name: %s depth: %d\n", g->names[current_node], g->rooms[current_node].depth);
		if (visited->size == g->room_count)
			return (0);
		visited->data[visited->size++] = current_node;
		search_edges(g->rooms[current_node], visited, queue, g);
		current_node = delete_first_element(queue);
		g->rooms[current_node].depth = get_depth(g, current_node);
	}
	return (g->rooms[current_node].depth);
}

int	get_depth(t_global *g, int current_node)
{
	unsigned int	i;
	unsigned int	save;

	i = 0;
	save = INT_MAX;
	while(i != g->rooms[current_node].edge_count)
	{
		if (g->rooms[g->rooms[current_node].edges[i]].depth != 0 && 
				g->rooms[g->rooms[current_node].edges[i]].depth < save && g->rooms[g->rooms[current_node].edges[i]].visited == false)
			save = g->rooms[g->rooms[current_node].edges[i]].depth;
		i++;
	}
	return (save + 1);
}

int	delete_first_element(t_stack *queue)
{
	unsigned int	i;
	unsigned int	save_first;

	i = 0;
	save_first = queue->data[0];
	while (i != queue->size)
	{
		queue->data[i] = queue->data[i + 1];
		i++;
	}
	queue->size--;
	return (save_first);
}

void	search_edges(t_room node, t_stack *visited, t_stack *queue, t_global *g)
{
	unsigned int	i;

	i = 0;
	while (i != node.edge_count)
	{
		if (not_searched(node.edges[i], visited) && g->rooms[node.edges[i]].visited == false)
			queue->data[queue->size++] = node.edges[i];
		i++;
	}
}

int	not_searched(int edge, t_stack *visited)
{
	unsigned int	i;

	i = 0;
	while (i != visited->size)
	{
		if ((unsigned int)edge == visited->data[i])
			return (0);
		i++;
	}
	return (1);
}
