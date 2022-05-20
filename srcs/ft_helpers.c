#include "lem-in.h"

int		ft_out(char *reason)
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
		if (!memcmp(p, "##start\n", 8))
			return (START);
		else if (!memcmp(p, "##end\n", 6))
			return (END);
		else
			ft_out("Bad command");
	}
	return (UNKNOWN);
}

