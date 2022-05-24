#include "lem-in.h"

int	ft_out(char *reason)
{
	char	*p;

	p = reason;
	while (*p)
	{
		write(1, p, 1);
		p++;
	}
	write(1, "\n", 1);
	exit(EXIT_FAILURE);
	return (EXIT_FAILURE);
}

int	comment_or_command(char *p)
{
	char	a;
	char	b;

	a = p[0];
	b = p[1];
	if (a == '#' && b != '#')
		return (COMMENT);
	else if (a == '#' && b == '#')
	{
		if (!ft_memcmp(p, "##start\n", 8))
			return (START);
		else if (!ft_memcmp(p, "##end\n", 6))
			return (END);
		else
			ft_out("Bad command");
	}
	return (UNKNOWN);
}

void	check_last_type(enum e_type last_line_type,
		t_info *p_info, size_t *room_count)
{
	if (last_line_type == START)
		p_info->start = *room_count;
	else if (last_line_type == END)
		p_info->end = *room_count;
	(*room_count)++;
}

char	*ft_strcpy(char *dest, const char *src)
{
	char	*ret;

	ret = dest;
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
	return (ret);
}

char	*ft_strcat(char *dest, const char *src)
{
	ft_strcpy(dest + ft_strlen (dest), src);
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

