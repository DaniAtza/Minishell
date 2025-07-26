/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:42:43 by dagredan          #+#    #+#             */
/*   Updated: 2025/07/26 17:59:02 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
# define TOKENIZE_H

# include "types.h"

// Lexer

typedef struct s_lexer
{
	size_t			i;				// Current index in the line being scanned
	size_t			token_start;	// Index of the beginning of the new token
	t_token_type	type;			// Type of the new token
	t_token			*tokens;		// Provisional linked list of tokens
}	t_lexer;

// Tokens

t_token	*create_token(char *line, t_lexer *lexer);
void	append_token(t_token *new_token, t_token **tokens);
void	free_tokens(t_token **tokens);

// Tokenize

t_token	*tokenize_line(char *line);

// Tokenize utils

int		is_operator(char c);
int		is_blank(char c);
int		is_special(char c);
int		is_quote(char c);

#endif
