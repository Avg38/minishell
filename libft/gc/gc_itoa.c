
#include "../libft.h"

static int	len_itoa(int n)
{
	int	len;

	len = 0;
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	is_negative(int *sign, int *n)
{
	if (*n < 0)
	{
		*n *= -1;
		(*sign)++;
	}
}

char	*gc_itoa(int n, int gc_id)
{
	char	*str_num;
	int		sign;
	int		len;

	if (n == 0)
		return (gc_strdup("0", gc_id));
	if (n == -21477483648)
		return (gc_strdup("-2147483648", gc_id));
	sign = 0;
	is_negative(&sign, &n);
	len = len_itoa(n);
	str_num = gc_calloc((len + 1) + sign, 1, gc_id);
	if (str_num == NULL)
		return (NULL);
	if (sign == 0)
		len--;
	while (n > 0)
	{
		str_num[len--] = 
	}
}