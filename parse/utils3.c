#include "minishell.h"

int for_chunk(char bite)
{
    if (bite == '$' || bite == '>' || bite == '<' || bite == '>'
        || bite == '\'' || bite == '\"' || bite == '|'
        || is_whitespace(bite) == YES)
        return (0);
    return (1);
}