/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_more.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrummuka <jrummuka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:54:33 by vkinnune          #+#    #+#             */
/*   Updated: 2022/10/21 14:06:52 by jrummuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n-- != 0)
		if (*((const unsigned char *)s1++) != *((const unsigned char *)s2++))
			return (*(const unsigned char *)--s1
				- *(const unsigned char *)--s2);
	else if (n && !*(const unsigned char *)s1 && !*(const unsigned char *)s2)
		return (0);
	return (0);
}

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

char	*ft_strdup(const char *s)
{
	void		*ns;
	uint64_t	len;

	len = ft_strlen((void *)s) + 1;
	ns = (char *)malloc(len);
	if (ns == 0)
		ft_out("ERROR");
	return ((char *)ft_memcpy(ns, s, len));
}

void	free_stuff(t_node *nodes, char *names, char *res, uint64_t node_count)
{
	uint64_t	i;

	i = 0;
	while (i != node_count)
	{
		free(nodes[i].edges);
		free(nodes[i].flows);
		i++;
	}
	free(names);
	free(res);
	free(nodes);
}
