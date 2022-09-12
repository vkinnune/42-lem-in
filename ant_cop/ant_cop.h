#ifndef ANT_COP_H
# define ANT_COP_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_list
{
	char *room1;
	char *room2;
	struct s_list *next;
}				t_list;

char	**ft_strsplit(char const *s, char c);
void	free_str_arr(char **arr);
void	free_list(t_list *head);
void	add_to_list(t_list **head, char *rm1, char *rm2);

#endif