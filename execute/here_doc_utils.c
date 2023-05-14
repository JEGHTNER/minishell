/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 12:02:44 by joon-lee          #+#    #+#             */
/*   Updated: 2023/05/14 23:58:27 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*here_doc_parsing(t_cmd *cmd, char *line)
{
	char	*to_ret;
	size_t	idx;
	size_t	start;
	size_t	end_idx;

	if (!line)
		exit(0);
	to_ret = ft_strdup("");
	idx = 0;
	start = idx;
	end_idx = ft_strlen(line);
	while (idx < end_idx)
	{
		if (line[idx] == '$')
			to_ret = join_n_free(chop_n_trim(to_ret, line, &start, &idx), \
					find_n_convert(cmd, line, &idx, &start));
		else
			idx++;
		if (idx == end_idx)
			to_ret = chop_n_trim(to_ret, line, &start, &idx);
	}
	free(line);
	return (to_ret);
}
