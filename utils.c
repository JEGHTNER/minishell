#include "minishell.h"

t_macro	is_whitespace(char tmp)
{
	if ((*str >= 9 && *str <= 13) || *str == 32)
		return (YES);
	else
		return (NO);
}
