#include "lem-in.h"

char	*ant_num(char *p_str, t_info *info);

size_t	parse_ant_count(const char *p_buf, t_info *info)
{
	enum e_type	line_type;
	char		*p_str;

	p_str = (char *)p_buf;
	info->ant_count = 0;
	while (1)
	{
		line_type = comment_or_command(p_str);
		if (line_type == COMMENT)
		{
			while (*p_str != '\n')
				p_str++;
			continue ;
		}
		break ;
	}
	p_str = ant_num(p_str, info);
	if (*p_str != '\n')
		ft_out("Error on ant number");
	p_str++;
	return (p_str - p_buf);
}

char	*ant_num(char *p_str, t_info *info)
{
	while (isdigit(*p_str))
	{
		info->ant_count *= 10;
		info->ant_count += *p_str - '0';
		p_str++;
	}
	return (p_str);
}

