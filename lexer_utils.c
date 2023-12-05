/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tscasso <tscasso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:49:29 by tscasso           #+#    #+#             */
/*   Updated: 2023/11/24 02:41:01 by tscasso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	get_type(char c, t_lexer *lx)
{
	char	quotes;

	quotes = c;
	if (quotes == '\"')
		lx->quotes = IN_DOUBLE_QUOTES;
	else
		lx->quotes = IN_SINGLE_QUOTES;
	return (quotes);
}