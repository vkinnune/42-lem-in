/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinnune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:30:49 by vkinnune          #+#    #+#             */
/*   Updated: 2022/10/14 13:46:39 by vkinnune         ###   ########.fr       */
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
	write (1, input_str, ft_strlen(input_str));
	info.global_names = names;
	res = generate_result(info, names, nodes);
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
	char			*copy;
	unsigned int	size;

	size = ft_strlen(input_str);
	copy = (char *)malloc(sizeof(char) * (size + 1));
	ft_memcpy(copy, input_str, sizeof(char) * size);
	copy[size] = 0;
	info->start = -1;
	info->end = -1;
	copy = parse_ant_count(copy, info);
	copy = parse_nodes(copy, info, names);
	if (*names == 0 || info->start == -1 || info->end == -1)
		ft_out("ERROR");
	*nodes = parse_edges(copy, *names, info->node_count);
}

char	*generate_result(t_info info, char *names, t_node *nodes)
{
	char	*res;
	t_path	path;

	path = find_augmenting_paths(nodes, info);
	path = stuff_ants(path, info);
	res = build_result(path, names);
	return (res);
}

t_path	stuff_ants(t_path path, t_info info)
{
	size_t	ant_count;
	size_t	i;
	size_t	save_index;

	ant_count = info.ant_count;
	path.flow = (ssize_t *)malloc(path.path_count * sizeof(size_t *));
	ft_bzero(path.flow, path.path_count * sizeof(size_t *));
	while (ant_count)
	{
		i = 0;
		save_index = 0;
		while (i != path.path_count)
		{
			if ((path.flow[save_index]
					+ path.size[save_index]) > (path.flow[i] + path.size[i]))
				save_index = i;
			i++;
		}
		path.flow[save_index]++;
		ant_count--;
	}
	return (path);
}
