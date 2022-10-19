/*
*******ANT_COP 1.0*******
        _.---._
     .-' ((O)) '-.
      \ _.\_/._ /
       /..___..\
       ;-.___.-;
      (| e ) e |)     .;.
       \  /_   /      ||||
       _\__-__/_    (\|'-|
     /` / \V/ \ `\   \ )/
    /   \  Y  /   \  /=/
   /  |  \ | / {}  \/ /
  /  /|   `|'   |\   /
  \  \|    |.   | \_/
   \ /\    |.   |
    \_/\   |.   |
    /)_/   |    |
   // ',__.'.__,'
  //   |   |   |
 //    |   |   |
(/     |   |   |
       |   |   |
       | _ | _ |
       |   |   |
       |   |   |
       |   |   |
       |___|___|
       /  J L  \
      (__/   \__)
*************************
*/

#include "ant_cop.h"

int valid_path(char *rm_prev, char *rm_cur, t_list *head)
{
	int a;
	int b;
	int c;
	int d;

	while(head)
	{
		a = strcmp(head->room1, rm_prev);
		b = strcmp(head->room1, rm_cur);
		c = strcmp(head->room2, rm_prev);
		d = strcmp(head->room2, rm_cur);
		if ((!a && !d) || (!b && !c))
			return (1);
		head = head->next;
	}
	return (0);
}

void add_to_arr(char *line, char **arr, int *ants_arr, int num_ants, char *start, char *end, t_list *head, int *flag)
{
	char **ln;
	char **ant_room;
	int i = 0;
	int j;
	char *temp;
	

	j = 0;
	while (j < num_ants)
	{
		ants_arr[j] = 0;
		j++;
	}
	ln = ft_strsplit(line, ' ');
	while (ln[i])
	{
		ant_room = ft_strsplit(ln[i], '-');
		//printf("ant_room[0] %s\n", &ant_room[0][1]);
		if (!ant_room[0][1])
		{
			printf("\x1b[31mERROR: EMPTY ANT\x1b[0m\n");
			printf("%s\n", ln[i]);
			exit(0);
		}
		if (ants_arr[atoi(&ant_room[0][1]) - 1])
		{
			printf("\x1b[31mERROR: same ant on same line\x1b[0m\n");
			//exit(0);
			*flag = 1;
		}
		ants_arr[atoi(&ant_room[0][1]) - 1] = 1;
		if (!valid_path(arr[atoi(&ant_room[0][1]) - 1], ant_room[1], head))
		{
				printf("%s %s\n",arr[atoi(&ant_room[0][1]) - 1], ant_room[1]);
				printf("\x1b[31mERROR: invalid path\x1b[0m\n");
				//exit (0);
				*flag = 1;
		}
		
		j = 0;
		while (j < num_ants)
		{
			if (strcmp(ant_room[1], start) && strcmp(ant_room[1], end))
			{
				if (ant_room[1][0] == arr[j][0])
				{
					if (!strcmp(ant_room[1], arr[j]))
					{
						printf("\x1b[31m%s -> %s\x1b[0m\n", ant_room[1], arr[j] );
						printf("%s\n", line);
						
						printf("\x1b[31mERROR: same room on same line\x1b[0m\n");
						//exit(0);
						*flag = 1;
					}
				}
			}
			j++;
		}
		temp = arr[atoi(&ant_room[0][1]) - 1];
		arr[atoi(&ant_room[0][1]) - 1] = strdup(ant_room[1]);
		free(temp);
		free_str_arr(ant_room);
		i++;
	}
	free_str_arr(ln);
}

int	main()
{
	char *line = NULL;
	size_t n = 0;
	int num_ants;
	int line_count = 0;
	char **arr;
	int *ants_arr;
	int i = 0;
	char *p;
	char *start;
	char *end;
	char **start_end;
	t_list *head = NULL;
	char **link;
	int flag = 0;

	
	getline(&line, &n, stdin);
	//printf("line in AC: %s\n", line);
	if (!line || !strcmp(line, "ERROR\n"))
	{
		printf("\x1b[31mERROR in map\x1b[0m\n");
		free(line);
		return (0);
	}
	num_ants = atoi(line);
	ants_arr = malloc(sizeof(int) * num_ants);
	arr = malloc(sizeof(char *) * num_ants + 1);
	while (getline(&line, &n, stdin) > 0)
	{
		if((p = strchr(line, '\n')))
			*p = '\0';
		if (line[0] == '#')
		{
			if (!strcmp(line, "##start"))
			{
				getline(&line, &n, stdin);
				if((p = strchr(line, '\n')))
					*p = '\0';
				start_end = ft_strsplit(line, ' ');
				start = strdup(start_end[0]);
				while (i < num_ants)
					arr[i++] = strdup(start);
				free_str_arr(start_end);
				continue ;
			}
			else if (!strcmp(line, "##end"))
			{
				getline(&line, &n, stdin);
				if((p = strchr(line, '\n')))
					*p = '\0';
				start_end = ft_strsplit(line, ' ');
				end = strdup(start_end[0]);
				free_str_arr(start_end);
				continue ;
			}
		}
		else if (line[0] != 'L' && strchr(line, '-') && !strchr(line, ' '))
		{
			link = ft_strsplit(line, '-');
			add_to_list(&head, link[0], link[1]);
			free_str_arr(link);
		}
		else if (line[0] == 'L')
		{
			//flag = 0;
			add_to_arr(line, arr, ants_arr, num_ants, start, end, head, &flag);
			line_count++;
		}
	}
	i = 0;
	while (i < num_ants)
	{
		if (strcmp(end, arr[i]))
		{
			printf("\x1b[31mERROR: not all ants at end\x1b[0m\n");
			//exit(0);
			flag = 2;
		}
		i++;
	}

	if (!flag)
	{
		printf("\x1b[32mALL TESTS PASSED\n");
		printf("line count => %d\n\x1b[0m", line_count);
	}
	else if (flag == 2)
	{
		i = 0;
		printf("final location of ants:\n");
		while (i < num_ants)
		{
			if (strcmp(end, arr[i]))
				printf("\x1b[31m%s \x1b[0m", arr[i]);
			else
				printf("%s ", arr[i]);
				if (i % 12 == 11)
					printf("\n");
			i++;
		}
	}
//	free(line);
//	free(start);
//free(end);
	//free_str_arr(arr);
//	free(ants_arr);
//	free_list(head);
	return (0);
}

//./generator --big-superposition > test.map && ./lem-in < test.map | ../ant_cop/./ant_cop