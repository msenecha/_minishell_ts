/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msenecha <msenecha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:49:29 by tscasso           #+#    #+#             */
/*   Updated: 2023/12/06 17:06:44 by msenecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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