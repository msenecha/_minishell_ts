/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msenecha <msenecha@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 23:47:45 by tscasso           #+#    #+#             */
/*   Updated: 2023/12/06 19:28:49 by msenecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	tokenize_last_word(t_lexer *lx)
{
	char	*token;

	token = strndup(lx->line + lx->start, lx->index - lx->start);
	//printf("\033[1;34mToken:\033[0m \033[1;32m%s\033[0m\n", token);
	add_token(lx, token);
}

void	cut_token(t_lexer *lx)
{
	char	*token;

	token = strndup(lx->line + lx->quote_start + 1, lx->quote_end - lx->quote_start - 1);
	//printf("\033[1;34mToken:\033[0m \033[1;32m%s\033[0m\n", token);
	add_token(lx, token);
}

// void cut_token(t_lexer *lx) {
//     char *token;
//     int start = lx->quote_start + 1;
//     int end = lx->quote_end - 1;

//     // Vérifier si le début de la chaîne n'est pas le début de la ligne
//     if (lx->quote_start > 0 && !isspace(lx->line[lx->quote_start - 1])) {
//         while (start > 0 && !isspace(lx->line[start - 1])) {
//             start--;
//         }
//     }

//     // Vérifier si la fin de la chaîne n'est pas la fin de la ligne
//     if (lx->quote_end < (int)strlen(lx->line) - 1 && !isspace(lx->line[lx->quote_end + 1])) {
//         while (end < (int)strlen(lx->line) - 1 && !isspace(lx->line[end + 1])) {
//             end++;
//         }
//     }

//     token = strndup(lx->line + start, end - start + 1);
//     printf("token: %s\n", token);
//     add_token(lx, token);

// }

void	process_quotes(t_lexer *lx)
{
	char	current;

	while ((current = lx->line[lx->index]) != '\0')
	{
		if (get_type(current, lx) == '\'' || get_type(current, lx) == '\"')
		{
			if (lx->state == START)
			{
				lx->state = IN_WORD;
				lx->quote_type = current;
				lx->quote_start = lx->index;
			}
			else if (lx->state == IN_WORD && current == lx->quote_type)
			{
				lx->state = START;
				lx->quote_end = lx->index;
				if ((lx->quote_type == '\"' || lx->quote_type == '\'') && lx->quote_end > lx->quote_start + 1)
					cut_token(lx);
				lx->start = lx->index + 1;
				return;
			}
		}
		lx->index++;
	}
}

void	process_no_quotes(t_lexer *lx)
{
	char	*token;

	token = strndup(lx->line + lx->start, lx->end - lx->start);
	//printf("\033[1;34mToken:\033[0m \033[1;32m%s\033[0m\n", token);
	add_token(lx, token);
}

t_list	*lexer(char *line)
{
	t_lexer	*lx;

	lx = malloc(sizeof(t_lexer));
	init_lexer(lx, line);
	while(lx->line[++lx->index] != '\0')
	{
		if (lx->line[lx->index] == '\'' || lx->line[lx->index] == '\"')
				process_quotes(lx);
		else if (lx->line[lx->index] == ' ' || lx->line[lx->index] == '\n')
		{
			lx->end = lx->index;
			if (lx->state == START)
			{
				if (lx->end > lx->start && lx->end < (int)strlen(lx->line)) // a voir
					process_no_quotes(lx);
				lx->start = lx->index + 1;
			}
		}
	}
	if (lx->state == START && lx->index > lx->start)
		tokenize_last_word(lx);
	//free(lx); // a voir
	return (lx->token_list);
}

// void	lexer(t_list *tokens_list)
// {
// 	operators(tokens_list);
// 	env_variables(tokens_list);
// 	handle_quotes(tokens_list);
// 	classify_tokens(tokens_list);
// }
