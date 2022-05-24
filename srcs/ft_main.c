/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinnune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:30:49 by vkinnune          #+#    #+#             */
/*   Updated: 2022/05/24 15:34:45 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	main(int argc, char **argv)
{
	char	p_buf[BUFF_SIZE];
	char	*p_names;
	t_room	*p_rooms;
	t_info	info;
	char	*res;

	if (argc < 2)
		ft_out("Give a file");
	else if (argc > 2)
		ft_out("Too many files");
	read_input(argv, p_buf);
	parse_input(p_buf, &info, &p_names, &p_rooms);
	res = move_ants(info, p_names, p_rooms);
	write(1, p_buf, ft_strlen(p_buf));
	write(1, "\n", 1);
	write(1, res, ft_strlen(res));
	free_edges(p_rooms, info.room_count);
	free(p_names);
	free(p_rooms);
	free(res);
}

void	read_input(char **av, char *p_buf)
{
	int	fd;
	int	size;

	fd = open(av[1], O_RDONLY);
	if (fd <= 0)
		ft_out("Wrong file");
	size = read(fd, p_buf, BUFF_SIZE);
	if (size <= 0)
		ft_out("Error reading");
	if (read(fd, 0, 0) != 0)
		ft_out("File too big");
	p_buf[size] = '\0';
}

void	parse_input(char *p_buf, t_info *p_info,
		char **pp_names, t_room **pp_rooms)
{
	size_t	bytes_parsed;

	bytes_parsed = parse_ant_count(p_buf, p_info);
	bytes_parsed += parse_nodes(&p_buf[bytes_parsed],
			p_info, pp_names);
	*pp_rooms = parse_edges(&p_buf[bytes_parsed],
			*pp_names, p_info->room_count);
}

char	*move_ants(t_info info, char *p_names, t_room *p_rooms)
{
	t_path	*paths;
	size_t	set_count;
	char	*res;
	size_t	i;

	paths = 0;
	set_count = 0;
	paths = make_paths(paths, &set_count, info, p_rooms);
	res = construct_instructions(paths, set_count, p_names, info);
	while (set_count)
	{
		i = 0;
		while (i != paths[set_count - 1].count)
		{
			free(paths[set_count - 1].data[i]);
			i++;
		}
		free(paths[set_count - 1].sizes);
		free(paths[set_count - 1].data);
		set_count--;
	}
	free(paths);
	return (res);
}

void	free_edges(t_room *p_rooms, size_t room_count)
{
	size_t	i;

	i = 0;
	while (i != room_count)
	{
		free(p_rooms[i].edges);
		free(p_rooms[i].flows);
		i++;
	}
}
