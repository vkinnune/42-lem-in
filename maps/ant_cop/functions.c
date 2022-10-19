
#include "ant_cop.h"

void	free_str_arr(char **arr)
{
	int	i = 0;

	while (arr[i])
		free (arr[i++]);
	free (arr);
}

void free_list(t_list *head)
{
	t_list *temp;

	while (head)
	{
		temp = head;
		free(head->room1);
		free(head->room2);
		head = head->next;
		free(temp);
	}
}

void add_to_list(t_list **head, char *rm1, char *rm2)
{
	t_list *temp;

	if(!(temp = malloc(sizeof(t_list))))
		exit(0);
	temp->room1 = strdup(rm1);
	temp->room2 = strdup(rm2);
	temp->next = *head;
	*head = temp;
}
