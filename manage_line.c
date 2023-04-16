#include "minishell.h"

void	manage_pipe(t_cmd *cmd, char *line, size_t *idx, size_t *quote)
{
	t_list *tmp;


	if (cmd->chunk_head == 0)
		ft_exit_with_error("syntax error near unexpected token", "`|'");	
	else
	{
		if (line[*idx + 1] == '|')
			ft_exit_with_error("syntax error", "||");
		if (line[*idx + 1] == '\0')
			ft_exit_with_error("syntax error for pipe", 0);
		tmp = ft_lstnew((char *)"|");
		if (!tmp)
			ft_exit_with_error("malloc error", 0);
		ft_lstadd_back(&(cmd->chunk_head), tmp);
	}
}

void	manage_quotation(t_cmd *cmd, char *line, size_t *idx, size_t *pipe)
{

	//쌍따옴표 안에서 환경변수($), 한따옴표만 특수 처리, 나머지 문자열 출력
	//한따옴표 안의 한따옴표는 따옴표 출력 안 하고 나머지는 문자열로 출력하기
	//따옴표 갯수 쌍 맞는지 확인
}

void	manage_chunk(t_cmd *cmd, char *line, size_t *idx)
{
	
}
