#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <ctype.h>
# include <fcntl.h>
# include <string.h>
# include <limits.h>
# include <stdbool.h>

/*
   One megabyte allocated for reading
   */

# define BUFF_SIZE 1000000
# define NAME_LENGTH 32

enum	e_type
{
	UNKNOWN,
	COMMENT,
	START,
	END
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
	size_t	start;
	size_t	end;
	t_ins	ins;
}	t_info;

int	ft_out(char *reason);
size_t	parse_ant_count(const char *p_buf, t_info *info);
size_t	parse_nodes(const char *p_buf, t_info *p_info, char **pp_names);
t_room	*parse_edges(char *p, char *p_names, size_t room_count);
char	*move_ants(t_info info, char *p_names, t_room *p_rooms);
int	comment_or_command(char *p);

#endif

