#include "minishell.h"

static size_t	check_side_quotation(char *line, size_t start)
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

static char	*quotation_to_string(char *line, size_t *idx, char *data)
{
	char	*tmp;
	char	*before;
	size_t	start_idx;
	size_t	end_idx;

	if (data == 0)
		data = ft_strdup("");
	end_idx = check_side_quotation(line, *idx);
	start_idx = *idx + 1;
	tmp = strchop(line, start_idx, end_idx - 1);
	data = ft_strjoin(data, tmp);
	*idx = end_idx + 1;
    return (data);
}

static char	*check_remain(char *line, size_t *idx, char *data)
{
	size_t	start_idx;
	char	*tmp;

	start_idx = *idx;
	if (*idx == ft_strlen(line))
		return (data);
	while (line[*idx] && is_whitespace(line[*idx]) == NO)
	{
		if (line[*idx] == '\'' || line[*idx] == '\"')
		{
			tmp = strchop(line, start_idx, *idx - 1);
			data = ft_strjoin(tmp, quotation_to_string(line, idx, data));
			start_idx = *idx;
		}
		(*idx)++;
		if (*idx == ft_strlen(line))
		{
			tmp = strchop(line, start_idx, *idx - 1);
			data = ft_strjoin(data, tmp);
		}
	}
	return (data);
}

void	manage_quotation(t_cmd *cmd, char *line, size_t *idx)
{
    char	*data;

	data = 0;
    data = quotation_to_string(line, idx, data);
	data = check_remain(line, idx, data);
	insert_node(data, cmd);
}
