NAME = lem-in

SRCS = 	srcs/ft_construct_instructions.c srcs/ft_main.c srcs/ft_make_flow.c srcs/ft_make_paths.c srcs/ft_mark_path.c srcs/ft_parsing.c srcs/ft_save_paths.c srcs/ft_traverse_nodes.c

INC = lem-in.h

FLAGS = -Wall -Werror -Wextra -g

OBJ = $(addprefix srcs/, $(SRCS:.c=.o))

all: $(NAME)

$(NAME):
	@gcc -o $(NAME) $(FLAGS) $(SRCS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
