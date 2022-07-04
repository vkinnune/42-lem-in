/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinnune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:33:02 by vkinnune          #+#    #+#             */
/*   Updated: 2022/05/24 15:43:11 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>
# include <fcntl.h>

# define BUFF_SIZE 1000000
# define NAME_LENGTH 32

enum	e_type
{
	UNKNOWN,
	COMMENT,
	START,
	END,
	IGNORE
};

typedef struct s_stack {
	size_t	*data;
	size_t	size;
}	t_stack;

typedef struct s_path {
	size_t	**data;
	size_t	*sizes;
	ssize_t	latency;
	size_t	count;
}	t_path;

typedef struct s_room {
	size_t	*edges;
	ssize_t	*flows;
	size_t	distance;
	size_t	edge_count;
	bool	visited;
}	t_room;

typedef struct s_bfs {
	size_t	*visited_stack;
	size_t	visited_size;
	size_t	*queue_stack;
	size_t	queue_size;
}	t_bfs;

typedef struct s_ins {
	size_t	*flow;
	size_t	set;
	size_t	i;
	size_t	ant;
	size_t	*res;
	size_t	tick;
	ssize_t	pos;
}	t_ins;

typedef struct s_info {
	size_t	ant_count;
	size_t	room_count;
	ssize_t	start;
	ssize_t	end;
	t_ins	ins;
}	t_info;

int		ft_out(char *reason);
int		comment_or_command(char *p);
size_t	parse_ant_count(const char *p_buf, t_info *info);
size_t	parse_nodes(const char *p_buf, t_info *p_info, char **pp_names);
t_room	*parse_edges(char *p, char *p_names, size_t room_count);
char	*move_ants(t_info info, char *p_names, t_room *p_rooms);

char	*ft_strcpy(char *dest, const char *src);
size_t	ft_strlen(const char *str);
char	*ft_strcat(char *dest, const char *src);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_isdigit(int c);
int		ft_isascii(int c);

char	*allocate_more(char *str, char *buf);
void	handle_nums(char *p, size_t ant);

size_t	get_set(t_path *paths, size_t set_count);
size_t	*get_flow(t_path *path, size_t ant_count);
int		loop_flows(t_info info, char *p_names, t_path *paths, char **str);
int		loop_paths(t_info info, char *p_names, t_path *paths, char **str);
size_t	add_ants(size_t *flow, size_t path_index);
char	*build_str(size_t ant, char *name, char *str);

int		not_visited(size_t edge, size_t *visited_stack, size_t visited_size);

void	read_input(char *p_buf, int argc, char **argv);
void	parse_input(char *p_buf, t_info *p_info,
			char **pp_names, t_room **pp_rooms);
char	*move_ants(t_info info, char *p_names, t_room *p_rooms);
t_path	*make_paths(t_path *paths,
			size_t *set_count, t_info info, t_room *p_rooms);
char	*construct_instructions(t_path *paths,
			size_t set_count, char *p_names, t_info info);
void	free_edges(t_room *p_rooms, size_t room_count);

void	add_flow(size_t current_node, size_t prev_node, t_room **pp_rooms);
void	negative_path(size_t current_node, size_t prev_node, t_room **pp_rooms);
size_t	next_node(t_room **pp_rooms, size_t current_node);

int		traverse_nodes(t_room **pp_rooms, t_info info, t_bfs *p_traversal_data);
void	alloc_flows(t_room *p_rooms, size_t room_count);
void	calculate_latency(t_info info, t_path *paths, size_t set_count);
void	clear_distance(t_room **pp_rooms, size_t room_count);
void	mark_flow(t_room **pp_rooms, t_info info);
t_path	*save_paths(t_room **pp_rooms,
			t_info info, t_path *paths, size_t set_count);

void	add_to_visited(t_stack *visited, size_t current_node);
ssize_t	next_flow_node(t_stack *visited, t_room **pp_rooms,
			size_t current_node);
void	add_to_path(t_path *paths, size_t current_node);
int		edge_not_visited(t_stack *visited, size_t edge);

char	*ant_num(char *p_str, t_info *info);

void	add_edges(size_t in, size_t out, t_room *p_rooms);
size_t	read_room_a(char **p, char *p_names, size_t room_count);
size_t	read_room_b(char **p, char *p_names, size_t room_count);

void	check_last_type(enum e_type last_line_type,
			t_info *p_info, size_t *room_count);
char	*save_name(char *p, char *p_save, char **pp_names, size_t room_count);
char	*skip_cords(char *p);
int		skip_comment_or_command(char **p, enum e_type line_type);
char	*name_alloc(char **pp_names, size_t room_count);

void	allocate_path_data(t_path *paths, size_t count);
t_path	*allocate_new_path(t_path *paths, size_t set_count);
void	mark_flow(t_room **pp_rooms, t_info info);
void	add_flow(size_t current_node, size_t prev_node, t_room **pp_rooms);
void	negative_path(size_t current_node, size_t prev_node, t_room **pp_rooms);
size_t	next_node(t_room **pp_rooms, size_t current_node);
int		mark_path(t_stack *visited,
			t_room **pp_rooms, t_info info, t_path *paths);

size_t	get_distance(size_t current_node, t_room **pp_rooms);
void	add_edges_to_queue(size_t current_node, t_room **pp_rooms,
			t_bfs *p_traversal_data);
int		not_in_path(t_room **pp_rooms, size_t current_node, size_t index_edges);
int		delete_first_element(t_bfs *p_traversal_data);

#endif
