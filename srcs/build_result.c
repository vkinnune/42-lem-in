#include "lem_in.h"

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

char	*loop_flows(t_path path, size_t tick, char *names, size_t path_index, char *str)
{
	size_t	ant;
	ssize_t	pos;

	ant = 1;
	while (ant <= path.flow[path_index]) {
		pos = tick - ant;
		if (pos > 0 && pos < path.size[path_index])
			str = result_cat(str,
					make_instruction(pos,
						ant + add_ants(path.flow,
							path_index), names, path.data[path_index]));
		ant++;
	}
	return (str);

}

char	*build_result(t_path path, size_t ant_count, char *names)
{
	size_t	tick;
	size_t	path_index;
	char	*str;

	tick = 0;
	//str = (char *)malloc(sizeof(char) * 50000);
	str = 0;
	while (tick <= path.latency - 1)
	{
		path_index = 0;
		while (path_index != path.path_count)
		{
			str = loop_flows(path, tick, names, path_index, str);
			path_index++;
		}
		str = add_newline(str);
		tick++;
	}
	return (str);
}

char	*make_instruction(ssize_t pos, size_t ant, char *names, size_t *path)
{
	char	str[1000];
	size_t	i;

	i = 0;
	str[i++] = 'L';
	i += handle_nums(&str[i], ant);
	str[i++] = '-';
	ft_strcpy(&str[i], &names[path[pos] * NAME_LENGTH]);
	i += ft_strlen(&names[path[pos] * NAME_LENGTH]);
	str[i++] = ' ';
	str[i] = 0;
	return (ft_strdup(str));
}

char	*result_cat(char *str, char *ins)
{
	size_t	oldlen;
	size_t	newlen;

	oldlen = ft_strlen(str);
	newlen = oldlen + (ft_strlen(ins) + 1);
	str = ft_realloc(str, newlen, oldlen);
	ft_strcpy(&str[oldlen], ins);
	free(ins);
	return (str);
}

