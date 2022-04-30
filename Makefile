NAME = lem-in

SRCS = 	main.c bfs.c parsing.c
		
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