#include "lem-in.h"

char	*build_str(size_t ant, char *name, char *str);
size_t	add_ants(size_t *flow, size_t path_index);
size_t	*get_flow(t_path *path, size_t ant_count);
size_t	get_set(t_path *paths, size_t set_count);

char	*construct_instructions(t_path *paths, size_t set_count, char *p_names, t_info info)
{
	char	*str;
	size_t	*flow;
	size_t	set;
	size_t	i;
	size_t	ant;
	size_t	res;
	size_t	tick;
	ssize_t	pos;

	i = 0;
	tick = 1;
	set = get_set(paths, set_count);
	flow = get_flow(&paths[set], info.ant_count);
	str = 0;
	while (1)
	{
		i = 0;
		res = 0;
		while (i != paths[set].count)
		{
			ant = 1;
			while (ant <= flow[i])
			{
				pos = tick - ant;
				if (pos >= 0 && pos < (ssize_t)paths[set].sizes[i])
					str = build_str(ant + add_ants(flow, i), &p_names[paths[set].data[i][pos] * NAME_LENGTH], str);
				else
					res++;
				if (res >= info.ant_count)
				{
					free(flow);
					return (str);
				}
				ant++;
			}
			i++;
		}
		{
			char *p;

			p = str;
			while (*p != 0)
				p++;
			p--;
			*p = '\n';
		}
		tick++;
	}
}

char	*build_str(size_t ant, char *name, char *str)
{
	char	buf[1000];
	char	*p;

	{
		p = buf;
		*p = 'L';
		p++;
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
			while (*p != 0)
				p++;
		}
		*p = '-';
		p++;
		strcpy(p, name);
		while (*p != 0)
			p++;
		*p = ' ';
		p++;
		*p = 0;
	}
	{
		char	*cpy;

		if (str == 0)
		{
			str = (char *)malloc(((strlen(buf)) + 1)* sizeof(char));
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

size_t	*get_flow(t_path *path, size_t ant_count)
{
	size_t	*flow;
	size_t	path_count;
	size_t	save_index;
	size_t	*sizes;
	size_t	i;

	sizes = path->sizes;
	path_count = path->count;
	flow = (size_t *)malloc(path_count * sizeof(size_t));
	bzero(flow, path_count * sizeof(size_t));
	while (ant_count)
	{
		i = 0;
		save_index = 0;
		while (i != path_count)
		{
			if ((flow[save_index] + sizes[save_index]) > (flow[i] + sizes[i]))
				save_index = i;
			i++;
		}
		flow[save_index]++;
		ant_count--;
	}
	return (flow);
}

size_t	get_set(t_path *paths, size_t set_count)
{
	ssize_t	latency;
	ssize_t	save_i;
	size_t	i;

	latency = INT_MAX;
	i = 0;
	save_i = -1;
	while (i != set_count)
	{
		if (paths[i].latency < 0)
			paths[i].latency *= -1;
		if (paths[i].latency < latency && paths[i].latency >= 0)
		{
			latency = paths[i].latency;
			save_i = i;
		}
		i++;
	}
	if (save_i == -1)
		ft_out("Error on getting a set");
	return (save_i);
}

