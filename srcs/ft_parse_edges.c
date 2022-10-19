/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_edges.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrummuka <jrummuka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:31:35 by vkinnune          #+#    #+#             */
/*   Updated: 2022/10/19 17:02:55 by jrummuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_node	*parse_edges(char *p, char *names, uint64_t node_count)
{
	t_node		*nodes;
	enum e_type	line_type;
	uint64_t	node_a;
	uint64_t	node_b;

	nodes = (t_node *)malloc(sizeof(t_node) * node_count);
	ft_bzero(nodes, sizeof(t_node) * node_count);
	while (*p != 0 && p[1] != 0)
	{
		line_type = comment_or_command(p);
		if (line_type == START || line_type == END)
			ft_out("ERROR");
		else if (line_type == COMMENT || line_type == IGNORE)
		{
			while (*p != '\n' && *p != '\0')
				p++;
			p++;
			continue ;
		}
		node_a = read_node_a(&p, names, node_count);
		node_b = read_node_b(&p, names, node_count);
		add_edges(node_a, node_b, nodes);
		add_edges(node_b, node_a, nodes);
	}
	return (nodes);
}

void	add_edges(uint64_t in, uint64_t out, t_node *nodes)
{
	int64_t	*edges;

	if (nodes[in].edge_count == 0)
	{
		nodes[in].edges = (int64_t *)malloc(sizeof(int64_t) * 1);
		ft_bzero(nodes[in].edges, sizeof(int64_t) * 1);
	}
	else
	{
		edges = (int64_t *)malloc(sizeof(int64_t) * (nodes[in].edge_count + 1));
		ft_bzero(edges, sizeof(int64_t) * (nodes[in].edge_count + 1));
		ft_memcpy(edges, nodes[in].edges, (nodes[in].edge_count
				* sizeof(int64_t)));
		free(nodes[in].edges);
		nodes[in].edges = edges;
	}
	nodes[in].edges[nodes[in].edge_count] = out;
	nodes[in].edge_count++;
}

uint64_t	read_node_a(char **p, char *names, uint64_t node_count)
{
	uint64_t	i;
	char		*save;
	uint64_t	size;

	i = 0;
	if (**p == '-')
		ft_out("ERROR");
	save = *p;
	while (**p != '-' && **p != 0)
		(*p)++;
	if (*p - save > NAME_LENGTH)
		ft_out("ERROR");
	**p = 0;
	size = (*p - save) + 1;
	while (ft_strncmp(save, &names[i * NAME_LENGTH], size)
		&& i != node_count)
		i++;
	**p = '\n';
	if (i == node_count)
		ft_out("ERROR");
	(*p)++;
	return (i);
}

uint64_t	read_node_b(char **p, char *names, uint64_t node_count)
{
	uint64_t	i;
	char		*save;
	uint64_t	size;

	i = 0;
	save = *p;
	while (**p != '\n' && **p != 0)
		(*p)++;
	if (*p - save > NAME_LENGTH || *p == save || **p != '\n')
		ft_out("ERROR");
	**p = 0;
	size = (*p - save) + 1;
	while (ft_strncmp(save, &names[i * NAME_LENGTH], size)
		&& i != node_count)
		i++;
	**p = '\n';
	if (i == node_count)
		ft_out("ERROR");
	(*p)++;
	return (i);
}
