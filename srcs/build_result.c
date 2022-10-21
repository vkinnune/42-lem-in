/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_result.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrummuka <jrummuka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:07:07 by vkinnune          #+#    #+#             */
/*   Updated: 2022/10/21 14:11:00 by jrummuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

uint64_t	add_ants(int64_t *flow, uint64_t path_index)
{
	uint64_t	res;
	uint64_t	i;

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
		char *names, uint64_t path_index, t_data *data)
{
	int64_t	ant;
	int64_t	pos;

	ant = 1;
	while (ant <= path.flow[path_index])
	{
		pos = data->tick - ant;
		data->path = path.data[path_index];
		if (pos > 0 && pos < path.size[path_index])
			data->str = result_cat(data->str,
					make_instruction(pos,
						ant + add_ants(path.flow,
							path_index), names, data), data);
		ant++;
	}
	return (data->str);
}

char	*build_result(t_path path, char *names)
{
	uint64_t	path_index;
	t_data		data;

	data.tick = 2;
	data.allocated = 10000;
	data.len = 0;
	data.str = (char *)ft_mc(10000);
	while (data.tick <= path.latency - 1)
	{
		path_index = 0;
		while (path_index != path.path_count)
		{
			data.str = loop_flows(path, names, path_index, &data);
			path_index++;
		}
		if (data.len)
			data.str[data.len - 1] = '\n';
		data.tick++;
	}
	return (data.str);
}

char	*make_instruction(int64_t pos, uint64_t ant, char *names, t_data *data)
{
	char		str[1000];
	uint64_t	i;

	i = 0;
	str[i++] = 'L';
	i += handle_nums(&str[i], ant);
	str[i++] = '-';
	ft_strcpy(&str[i], &names[data->path[pos] * NAME_LENGTH]);
	i += ft_strlen(&names[data->path[pos] * NAME_LENGTH]);
	str[i++] = ' ';
	str[i] = 0;
	data->newlen = i;
	return (ft_strdup(str));
}

char	*result_cat(char *str, char *ins, t_data *data)
{
	int64_t	oldalloc;

	if ((data->len + data->newlen) > data->allocated)
	{
		oldalloc = data->allocated;
		data->allocated *= 2;
		str = ft_realloc(str, data->allocated, oldalloc);
	}
	ft_strcpy(&str[data->len], ins);
	data->len += data->newlen;
	free(ins);
	return (str);
}
