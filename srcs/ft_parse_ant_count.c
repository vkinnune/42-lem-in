#include "lem-in.h"

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
	while (isdigit(*p_str))
	{
		info->ant_count *= 10;
		info->ant_count += *p_str - '0';
		p_str++;
	}
	if (*p_str != '\n')
		ft_out("Error on ant number");
	p_str++;
	return (p_str - p_buf);
}

