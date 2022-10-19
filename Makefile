NAME			=	lem-in

H_FOLDER		=	includes
C_FOLDER		=	srcs
OBJ_FOLDER		=	obj
FOLDER_LIST		=	$(H_FOLDER) $(C_FOLDER) $(OBJ_FOLDER)

H_FILES			=	lem_in.h
C_FILES			=	ft_main.c ft_parse_ant_count.c ft_parse_nodes.c ft_parse_edges.c ft_helpers.c ft_libft.c ft_libft_more.c algorithm.c ft_realloc.c algorithm2.c algorithm3.c build_result.c build_result2.c
H_PATHS			=	$(addprefix $(H_FOLDER)/, $(H_FILES))
C_PATHS			=	$(addprefix $(C_FOLDER)/, $(C_FILES))
OBJ_PATHS		=	$(addprefix $(OBJ_FOLDER)/, $(patsubst %.c, %.o, $(C_FILES)))

C_FLAGS			=	-g -Wall -Wextra -Werror

.PHONY: all
all: $(NAME)

$(NAME): pre_requisites $(OBJ_PATHS)
	cc $(C_FLAGS) -I $(H_FOLDER) -o $@ $(OBJ_PATHS)

$(OBJ_PATHS): $(OBJ_FOLDER)/%.o:$(C_FOLDER)/%.c $(H_PATHS)
	cc $(C_FLAGS) -I $(H_FOLDER) -c $< -o $@

pre_requisites: $(FOLDER_LIST) $(H_PATHS) $(C_PATHS)

$(FOLDER_LIST):
	@mkdir $@

$(H_PATHS):
	@touch $@

$(C_PATHS):
	@touch $@

.PHONY: print_files
print_files:
	@echo "H paths:   $(H_PATHS)"
	@echo "C paths:   $(C_PATHS)"
	@echo "OBJ paths: $(OBJ_PATHS)"
	@echo "C flags:   $(C_FLAGS)"
	@echo ""

.PHONY: clean
clean:
	-@rm -fd $(OBJ_PATHS)
	@echo "All object files are removed!"

.PHONY: fclean
fclean: clean
	-@rm -f $(NAME)
	-@rm -fd $(OBJ_FOLDER)
	@echo "$(NAME) file is removed!"

.PHONY: re
re: fclean all
