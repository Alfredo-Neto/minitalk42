#include "libft.h"

void	ft_super_free(void **ptr)
{
	if(*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}
