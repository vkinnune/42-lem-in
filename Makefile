NAME = lem-in

SRCS = 	srcs/ft_main.c srcs/ft_parse_ant_count.c srcs/ft_parse_nodes.c srcs/ft_parse_edges.c srcs/ft_helpers.c srcs/ft_libft.c srcs/ft_libft_more.c srcs/algorithm.c srcs/ft_realloc.c srcs/algorithm2.c srcs/algorithm3.c srcs/build_result.c srcs/build_result2.c

FLAGS = -g
-fsanitize=address
OBJ = $(addprefix srcs/, $(SRCS:.c=.o))

all: $(NAME)

$(NAME):
	gcc -o $(NAME) $(FLAGS) $(SRCS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
