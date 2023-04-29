#include "minishell.h"

size_t	check_side_quotation(char *line, size_t start)
{
	size_t	idx;
	size_t	end;
	char	quote;

	idx = start;
	quote = line[start];
	end = ft_strlen(line);
	if (ft_strlen(line) == 1)
		ft_exit_with_error("syntax error: quotation can't find the match", 0);
	while (idx < end)
	{
		if (start != idx && line[idx] == quote)
			break ;
		idx++;
	}
	if (idx == end)
		ft_exit_with_error("syntax error: quotation can't find the match", 0);
	return (idx);
}

char	*quote_to_string(t_cmd *cmd, char *line, size_t *idx, size_t *st)
{
	if (line[*idx] == '\"')
		return (double_quote_to_string(cmd, line, idx, st));
	else
		return (single_quote_to_string(line, idx, st));
}

t_macro	nothing_to_ret(char **tmp, size_t *idx, size_t end_idx)
{
	char	*ret;

	*tmp = 0;
	if(*idx == end_idx)
	{
		ret = ft_strdup("");
		(*idx)++;
		return (YES);
	}
	return (NO);
}
