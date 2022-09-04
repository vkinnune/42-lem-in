/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinnune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:30:49 by vkinnune          #+#    #+#             */
/*   Updated: 2022/07/06 16:27:03 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	main(int argc, char **argv)
{
	t_info	info;
	t_node	*nodes;
	char	*names;
	char	input_str[READ_SIZE];
	char	*res;

	read_input(input_str, argc, argv);
	parse_input(input_str, &info, &names, &nodes);
	res = generate_result(info, names, nodes);
	//write (1, input_str, ft_strlen(input_str));
	write (1, res, ft_strlen(res));
}

void	read_input(char *input_str, int argc, char **argv)
{
	int	size;
	int	fd;

	fd = 0;
	if (argc >= 2)
		fd = open(argv[1], O_RDONLY);
	size = read(fd, input_str, READ_SIZE);
	if (size <= 0 || read(fd, 0, 0) != 0)
		ft_out("ERROR");
	input_str[size] = '\n';
	input_str[size + 1] = '\0';
}

void	parse_input(char *input_str, t_info *info,
		char **names, t_node **nodes)
{
	info->start = -1;
	info->end = -1;
	input_str = parse_ant_count(input_str, info);
	input_str = parse_nodes(input_str, info, names);
	if (*names == 0 || info->start == -1 || info->end == -1)
		ft_out("ERROR");
	*nodes = parse_edges(input_str, *names, info->node_count);
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


char	*build_result(t_path path, size_t ant_count, char *names)
{
	size_t	tick;
	size_t	path_index;
	size_t	ant;
	ssize_t	pos;
	char	*str;

	tick = 0;
	str = 0;
	while (tick <= path.latency - 1)
	{
		path_index = 0;
		while (path_index != path.path_count)
		{
			ant = 1;
			while (ant <= path.flow[path_index])
			{
				pos = tick - ant;
				if (pos > 0 && pos < path.size[path_index])
					str = result_cat(str, make_instruction(pos, ant + add_ants(path.flow, path_index), names, path.data[path_index]));
				ant++;
			}
			path_index++;
		}
		str = add_newline(str);
		tick++;
	}
	return (str);
}

char	*add_newline(char *str)
{
	size_t	size;

	if (str == 0)
		return (0);
	size = ft_strlen(str) + 1;
	str = ft_realloc(str, size + 1, size);
	str[size - 2] = '\n';
	str[size - 1] = 0;
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

size_t	handle_nums(char *str, size_t ant)
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
	ft_strcpy(str, p_num);
	return (ft_strlen(p_num));
}

t_path	stuff_ants(t_path path, t_info info)
{
	size_t	ant_count;
	size_t	i;
	size_t	save_index;

	ant_count = info.ant_count;
	path.flow = (size_t *)malloc(path.path_count * sizeof(size_t *));
	ft_bzero(path.flow, path.path_count * sizeof(size_t *));
	while (ant_count)
	{
		i = 0;
		save_index = 0;
		while (i != path.path_count)
		{
			if ((path.flow[save_index] + path.size[save_index]) > (path.flow[i] + path.size[i]))
				save_index = i;
			i++;
		}
		path.flow[save_index]++;
		ant_count--;
	}
	return (path);
}

char	*generate_result(t_info info, char *names, t_node *nodes)
{
	char	*res;
	t_path	path;

	path = find_augmenting_paths(nodes, info);
	path = stuff_ants(path, info);
	res = build_result(path, info.ant_count, names);
	return (res);
}

