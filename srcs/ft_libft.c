/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinnune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:54:33 by vkinnune          #+#    #+#             */
/*   Updated: 2022/05/24 15:54:35 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	d = dest;
	s = src;
	if (n == 0 || dest == src)
		return (dest);
	while (n--)
		*d++ = *s++;
	return (dest);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = s;
	while (n-- > 0)
		*ptr++ = c;
	return (s);
}

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	while (n-- != 0)
		if (*((const unsigned char *)s1++) != *((const unsigned char *)s2++))
			return (*(const unsigned char *)--s1
				- *(const unsigned char *)--s2);
	return (0);
}
