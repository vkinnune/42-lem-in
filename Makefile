NAME = lem-in

SRCS = 	srcs/ft_construct_instructions.c srcs/ft_main.c srcs/ft_mark_flow.c srcs/ft_make_paths.c srcs/ft_mark_path.c srcs/ft_save_paths.c srcs/ft_traverse_nodes.c srcs/ft_edges_queue.c srcs/ft_build_str.c srcs/ft_parse_ant_count.c srcs/ft_parse_nodes.c srcs/ft_parse_edges.c srcs/ft_helpers.c srcs/ft_libft.c srcs/ft_libft_more.c

FLAGS = -Wall -Werror -Wextra -g

OBJ = $(addprefix srcs/, $(SRCS:.c=.o))

all: $(NAME)

$(NAME):
	gcc -o $(NAME) $(FLAGS) $(SRCS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
