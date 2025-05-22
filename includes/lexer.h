/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:42:43 by dagredan          #+#    #+#             */
/*   Updated: 2025/05/22 13:20:03 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "types.h"

/* tokens.c */
t_token	*create_token(char *line, t_lexer *lexer);
void	append_token(t_token *new_token, t_token **tokens);
void	free_tokens(t_token **tokens);

/* lexer.c */
t_token	*tokenize_line(char *line);

/* utils.c */
int		is_operator(char c);
int		is_blank(char c);
int		is_special(char c);
int		is_quote(char c);

#endif