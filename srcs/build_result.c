/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_result.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinnune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:07:07 by vkinnune          #+#    #+#             */
/*   Updated: 2022/10/13 15:41:43 by vkinnune         ###   ########.fr       */
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
		char *names, uint64_t path_index, t_data data)
{
	int64_t	ant;
	int64_t	pos;

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

char	*build_result(t_path path, char *names)
{
	uint64_t	path_index;
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

char	*make_instruction(int64_t pos, uint64_t ant, char *names, int64_t *path)
{
	char	str[1000];
	uint64_t	i;

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
	uint64_t	oldlen;
	uint64_t	newlen;

	oldlen = ft_strlen(str);
	newlen = oldlen + (ft_strlen(ins) + 1);
	str = ft_realloc(str, newlen, oldlen);
	ft_strcpy(&str[oldlen], ins);
	free(ins);
	return (str);
}

