/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:26:24 by dagredan          #+#    #+#             */
/*   Updated: 2025/05/23 23:24:08 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "types.h"

/* process.c */
t_process	*create_process(void);
void		append_process(t_process *new_process, t_process **processes);
void		free_processes(t_process **processes);

/* redirect.c */
t_redirect	*create_redirect(t_token *redir_operator, t_token *filename);
void		append_redirect(t_redirect *new_redirect, t_redirect **redirects);
void		free_redirects(t_redirect **redirects);

/* args.c */
char		**append_arg(char *new_arg, char **args);
void		free_args(char ***args_addr);

/* parser.c */
t_process	*parse_tokens(t_token *tokens);

/* validation.c */
int 		validate_syntax(t_data *data);

/* utils.c */
int 		is_pipe(t_token *token);
int 		is_redirection(t_token *token);
int 		is_word(t_token *token);

#endif
