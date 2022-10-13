/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_result.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinnune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:07:07 by vkinnune          #+#    #+#             */
/*   Updated: 2022/10/13 15:06:53 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*loop_flows(t_path path,
		char *names, size_t path_index, t_data data)
{
	size_t	ant;
	ssize_t	pos;

	ant = 1;
	while (ant <= path.flow[path_index])
	{
		pos = data.tick - ant;
		if (pos > 0 && pos < path.size[path_index])
			data.str = result_cat(data.str,
					make_instruction(pos,
						ant + add_ants(path.flow,
							path_index), names, path.data[path_index]));
		ant++;
	}
	return (data.str);
}

char	*build_result(t_path path, size_t ant_count, char *names)
{
	size_t	path_index;
	t_data	data;

	data.tick = 0;
	data.str = 0;
	while (data.tick <= path.latency - 1)
	{
		path_index = 0;
		while (path_index != path.path_count)
		{
			data.str = loop_flows(path, names, path_index, data);
			path_index++;
		}
		data.str = add_newline(data.str);
		data.tick++;
	}
	return (data.str);
}

char	*make_instruction(ssize_t pos, size_t ant, char *names, ssize_t *path)
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
