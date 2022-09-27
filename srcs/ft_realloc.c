#include "lem_in.h"

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
	return (new_ptr);
}
