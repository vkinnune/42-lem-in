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
# include <stdio.h>

# define READ_SIZE 2000000
# define NAME_LENGTH 32


enum	e_type
{
	UNKNOWN,
	COMMENT,
	START,
	END,
	IGNORE
};

typedef struct s_node {
	size_t	edge_count;
	size_t	*edges;
	ssize_t	*in;
	ssize_t	*out;
	bool	visited;
	bool	flow;
	ssize_t	prev_node;
	ssize_t	depth;
}	t_node;

typedef struct s_info {
	size_t	ant_count;
	size_t	node_count;
	ssize_t	start;
	ssize_t	end;
	char	*global_names;
}	t_info;

typedef struct s_path {
	ssize_t	latency;
	ssize_t	**data;
	size_t	*size;
	size_t	*flow;
	size_t	path_count;
}	t_path;

typedef struct s_stack {
	size_t	*data;
	size_t	size;
}	t_stack;

void	read_input(char *input_str, int argc, char **argv);
void	parse_input(char *input_str, t_info *info,
			char **names, t_node **nodes);
char	*parse_ant_count(const char *input_str, t_info *info);
char	*ant_num(char *p, t_info *info);
t_node	*parse_edges(char *p, char *names, size_t node_count);
void	add_edges(size_t in, size_t out, t_node *nodes);
size_t	read_node_a(char **p, char *names, size_t node_count);
size_t	read_node_b(char **p, char *names, size_t node_count);
char	*parse_nodes(const char *input_str, t_info *info, char **names);
int		skip_comment_or_command(char **p, enum e_type line_type);
char	*save_name(char *p, char *save, char **names, size_t node_count);
char	*name_alloc(char **names, size_t node_count);
char	*skip_cords(char *p);

void	*ft_memcpy(void *dest, const void *src, size_t n);
size_t	ft_strlen(const char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *s, int c, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_out(char *reason);
char	*ft_strdup(const char *s);
int		comment_or_command(char *p);
void	check_last_type(enum e_type last_line_type,
			t_info *p_info, size_t *room_count);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strcat(char *dest, const char *src);
void	*ft_realloc(void *ptr, size_t new_size, size_t old_size);

t_path	find_augmenting_paths(t_node *nodes, t_info info);
void	create_path(t_path paths[2], t_node *nodes, t_info info);
ssize_t	find_edge_id(ssize_t current_node, ssize_t next_node, t_node *nodes);
ssize_t	go_deeper(t_node *nodes, t_info info, size_t current_node);
ssize_t	delete_from_queue(t_stack *queue);
char	*generate_result(t_info info, char *names, t_node *nodes);
ssize_t	calculate_latency(size_t *sizes, size_t ant_count, size_t path_count);
size_t	handle_nums(char *str, size_t ant);
char	*make_instruction(ssize_t pos, size_t ant, char *names, size_t *path);
char	*result_cat(char *str, char *ins);
char	*add_newline(char *str);
size_t	cmp_latency(size_t path_count, size_t *sizes, size_t *sizes_copy);
char	*build_result(t_path path, size_t ant_count, char *names);
t_path	stuff_ants(t_path path, t_info info);
int	add_to_queue(ssize_t current_node,
		ssize_t prev_node, t_node *nodes, t_stack *queue, t_info info);
size_t	get_depth(t_node *nodes, ssize_t current_node);
int		augment(t_node *nodes, t_info info);
void	convert(t_node *nodes, t_info info);

#endif

