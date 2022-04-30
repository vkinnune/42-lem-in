# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <ctype.h>
# include <fcntl.h>
# include <string.h>
# include <limits.h>
# include <stdbool.h>

# define BUFF_SIZE 4096

enum	e_type
{
	UNKNOWN,
	COMMENT,
	START,
	END
};

typedef struct s_room {
	unsigned int		edges[1000];
	unsigned int		edge_count;
	unsigned int		depth;
	bool	visited;
}	t_room;

typedef struct s_cords {
		int	x;
		int	y;
}	t_cords;

typedef struct s_stack {
		unsigned int	*data;
		unsigned int	size;
}	t_stack;

typedef struct s_path {
		unsigned int	*data;
		unsigned int	*visited;
		unsigned int	size;
}	t_path;

typedef struct s_global {
	unsigned int	ant_count;
	unsigned int	room_count;
	char			names[1000][20];
	t_room			rooms[1000];
	t_cords			cords[1000];
	int				start;
	int				end;
	t_path			*paths;
	int				path_count;
	int				*ants_path;
	bool			is_space;
}	t_global;

int		bfs(t_global *g);
char	*parse_ant_count(t_global *g, char *p);
char	*parse_nodes(t_global *g, char *p);
char	*parse_edges(t_global *g, char *p);

int		comment_or_command(char *p);
int		ft_out(char *reason);

int		find_paths(int maxedges, t_global *g);
int		check_dup(int *room_history, int depth, int edge);
//int		find_path(t_global *g);
