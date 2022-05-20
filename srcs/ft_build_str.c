#include "lem-in.h"

char	*allocate_more(char *str, char *buf);
void	handle_nums(char *p, size_t ant);

char	*build_str(size_t ant, char *name, char *str)
{
	char	buf[1000];
	char	*p;

	p = buf;
	*p = 'L';
	p++;
	handle_nums(p, ant);
	while (*p != 0)
		p++;
	*p = '-';
	p++;
	strcpy(p, name);
	while (*p != 0)
		p++;
	*p = ' ';
	p++;
	*p = 0;
	str = allocate_more(str, buf);
	return (str);
}

void	handle_nums(char *p, size_t ant)
{
	char	num[100];
	char	*p_num;

	p_num = &num[100 - 1];
	*p_num = 0;
	p_num--;
	while (ant)
	{
		*p_num = (ant % 10) + '0';
		ant /= 10;
		p_num--;
	}
	p_num++;
	strcpy(p, p_num);
}

char	*allocate_more(char *str, char *buf)
{
	char	*cpy;

	if (str == 0)
	{
		str = (char *)malloc(((strlen(buf)) + 1) * sizeof(char));
		strcpy(str, buf);
	}
	else
	{
		cpy = (char *)malloc(((strlen(str) + strlen(buf) + 1) * sizeof(char)));
		strcpy(cpy, str);
		strcat(cpy, buf);
		free(str);
		str = cpy;
	}
	return (str);
}

size_t	add_ants(size_t *flow, size_t path_index)
{
	size_t	res;
	size_t	i;

	res = 0;
	i = 0;
	while (i != path_index)
	{
		res += flow[i];
		i++;
	}
	return (res);
}

