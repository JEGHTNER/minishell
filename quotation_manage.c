#include "minishell.h"

static size_t	check_side_quotation(char *line, size_t start)
{
	size_t	idx;
	size_t	end;
	char	quote;
	int 	flag;

	quote = line[start];
	end = ft_strlen(line);
	if (line[start] == '\'')
		flag = 0;
	else
		flag = 1;
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

static char *quotation_to_string(char *line, size_t *idx)
{
	char	*data;
	char	*env;
	size_t	start_idx;
	size_t	end_idx;

	end_idx = check_side_quotation(line, *idx);
	start_idx = *idx + 1;
	while (*idx <= end_idx)
	{
		if (line[end_idx] == '\"' && line[*idx] == '$')
		{
			data = strchop(line, start_idx, *idx - 1);
			env = find_env(*idx, &start_idx);
			if (env)
				data = ft_strjoin(data, env);
			if (start_idx == ft_strlen(line) - 1)
				return (data);
		}
		*idx++;
		if (*idx == end_idx)
			data = strchop(line, start_idx, *idx - 1);
	}
    return (data);
}

static char	*check_remain(char *line, size_t *idx, char *data)
{
	*idx++;
	if (*idx == ft_strlen(line))
		return ;
	if (is_whitespace(line[*idx]) == NO)
	{
		while (is_whitespace(line[*idx]) == NO)
		{
			if (line[*line] == '\'' || line[*line] == '\"')
                data = quotation_to_string(line, idx);
			*idx++;
		}
	}
	else
		return (data);
}

void	manage_quotation(t_cmd *cmd, char *line, size_t *idx)
{
    char *data;

    data = quotation_to_string(line, idx);
	data = check_remain(line, idx, data);
	insert_node(data, cmd);
}