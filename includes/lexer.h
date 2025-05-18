/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:42:43 by dagredan          #+#    #+#             */
/*   Updated: 2025/05/17 12:52:06 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "types.h"

/* tokens.c */
t_token	*create_token(char *line, t_lexer *lexer, t_token_type type);
void	append_token(t_data *data, t_token *token);
void	free_tokens(t_data *data);

/* lexer.c */
void	tokenize_line(t_data *data, char *line);

/* utils.c */
int		is_operator(char c);
int		is_blank(char c);
int		is_special(char c);
int		is_quote(char c);

#endif
