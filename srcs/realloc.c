/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrummuka <jrummuka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:41:27 by vkinnune          #+#    #+#             */
/*   Updated: 2022/10/21 14:11:48 by jrummuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	afterstartorend(enum e_type line_type, enum e_type last_line_type)
{
	if ((last_line_type == START || last_line_type == END)
		&& line_type != UNKNOWN)
		ft_out("ERROR");
}

void	*ft_mc(size_t size)
{
	void	*mem;

	mem = (void *)malloc(size);
	if (!mem)
		ft_out("ERROR");
	ft_bzero(mem, size);
	return (mem);
}

void	*ft_realloc(void *ptr, size_t new_size, size_t old_size)
{
	void	*new_ptr;

	if (!old_size)
		new_ptr = malloc(new_size);
	else
	{
		new_ptr = (void *)malloc(new_size);
		ft_memcpy(new_ptr, ptr, old_size);
		free(ptr);
	}
	if (!new_ptr)
	{
		ft_out("ERROR");
	}
	return (new_ptr);
}

void	check_duplicate_edges(int64_t *edges, uint64_t edge_count, int64_t check)
{
	uint64_t	i;

	i = 0;
	while (i != edge_count)
	{
		if (edges[i] == check)
			ft_out("ERROR");
		i++;
	}
}
