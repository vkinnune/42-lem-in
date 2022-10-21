/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrummuka <jrummuka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:33:02 by vkinnune          #+#    #+#             */
/*   Updated: 2022/10/21 14:21:40 by jrummuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdint.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
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
	uint64_t	edge_count;
	int64_t		*edges;
	int64_t		*flows;
	bool		visited;
	bool		flow;
	int64_t		prev_node;
	int64_t		path_id;
	bool		is_end;
	bool		is_start;
	bool		is_queue;
}	t_node;

typedef struct s_info {
	uint64_t	ant_count;
	uint64_t	node_count;
	int64_t		start;
	int64_t		end;
	uint64_t	i;
	char		*names;
}	t_info;

typedef struct s_path {
	int64_t		latency;
	int64_t		**data;
	int64_t		*size;
	int64_t		*flow;
	uint64_t	path_count;
}	t_path;

typedef struct s_stack {
	uint64_t	*data;
	uint64_t	size;
}	t_stack;

typedef struct s_data {
	char	*str;
	int64_t	tick;
	int64_t	allocated;
	int64_t	len;
	int64_t	newlen;
	int64_t	*path;
}	t_data;

void		read_input(char *input_str, int argc, char **argv);
void		parse_input(char *input_str, t_info *info,
				char **names, t_node **nodes);
char		*parse_ant_count(const char *input_str, t_info *info);
char		*ant_num(char *p, t_info *info);
t_node		*parse_edges(char *p, char *names, uint64_t node_count);
void		add_edges(uint64_t in, uint64_t out, t_node *nodes);
char		*parse_nodes(const char *input_str, t_info *info,
				char **names, uint64_t node_count);
int			skip_comment_or_command(char **p, enum e_type line_type);
char		*save_name(char *p, char *save, char **names, uint64_t node_count);
char		*name_alloc(char **names, uint64_t node_count);
char		*skip_cords(char *p);
void		*ft_memcpy(void *dest, const void *src, size_t n);
size_t		ft_strlen(const char *str);
void		ft_bzero(void *s, size_t n);
void		*ft_memset(void *s, int c, size_t n);
int64_t		find_edge_id(int64_t current_node,
				int64_t next_node, t_node *nodes);
int64_t		delete_from_queue(t_stack *queue);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_out(char *reason);
char		*ft_strdup(const char *s);
int			comment_or_command(char *p);
void		check_last_type(enum e_type last_line_type,
				t_info *p_info, uint64_t *room_count);
char		*ft_strcpy(char *dest, const char *src);
char		*ft_strcat(char *dest, const char *src);
void		*ft_realloc(void *ptr, size_t new_size, size_t old_size);

char		*make_instruction(int64_t pos, uint64_t ant,
				char *names, t_data *data);
t_path		find_augmenting_paths(t_node *nodes, t_info info);
void		create_path(t_path paths[2], t_node *nodes, t_info info);
char		*generate_result(t_info info, char *names, t_node *nodes);
char		*result_cat(char *str, char *ins, t_data *data);
char		*add_newline(char *str);
char		*build_result(t_path path, char *names);
t_path		stuff_ants(t_path path, t_info info);
int			bfs(t_node *nodes, t_info info);
void		augment(t_node *nodes, t_info info);
int			add_to_queue(int64_t current_node,
				int64_t prev_node, t_node *nodes, t_stack *queue);
int64_t		calculate_latency(int64_t *sizes,
				uint64_t ant_count, uint64_t path_count);
t_path		free_paths(t_path old_path, t_path new_path);
void		free_stuff(t_node *nodes, char *names,
				char *res, uint64_t node_count);
void		afterstartorend(enum e_type line_type, enum e_type last_line_type);
void		*ft_mc(size_t size);
uint64_t	read_node_a(char **p, char *names, uint64_t node_count);
uint64_t	read_node_b(char **p, char *names, uint64_t node_count);
uint64_t	handle_nums(char *str, uint64_t ant);
uint64_t	cmp_latency(uint64_t path_count,
				int64_t *sizes, int64_t *sizes_copy);
void		check_duplicate_edges(int64_t *edges, uint64_t edge_count,
				int64_t check);
#endif
