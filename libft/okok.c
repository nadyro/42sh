#include <stdio.h>
#include "libft.h"

int	main()
{
	int k = 1;

	while (k++ < 1000000)
	{
		ft_putnbr_fd(k, 1);
		write(1, "\n", 1);
	}	
}
