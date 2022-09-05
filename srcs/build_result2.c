#include "lem_in.h"

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

