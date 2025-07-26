/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:26:24 by dagredan          #+#    #+#             */
/*   Updated: 2025/07/26 18:59:42 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "types.h"

// Parser

typedef struct s_parser
{
	t_token		*token;		// Current token being parsed
	t_process	*process;	// New process being populated
	t_process	*processes;	// Provisional linked list of processes
}	t_parser;

// Validate

int			validate_syntax(t_pipeline *pipeline);

// Processes

t_process	*create_process(void);
void		append_process(t_process *new_process, t_process **processes);
void		free_processes(t_process **processes);
size_t		count_processes(t_process *processes);

// Redirects

t_redirect	*create_redirect(t_token *redir_operator, t_token *filename);
void		append_redirect(t_redirect *new_redirect, t_redirect **redirects);
void		free_redirects(t_redirect **redirects);

// Argv

char		**append_arg(char *new_arg, char **argv);
void		free_argv(char ***argv_addr);

// Parse

t_process	*parse_tokens(t_token *tokens);

// Parse utils

int			is_pipe(t_token *token);
int			is_redirection(t_token *token);
int			is_word(t_token *token);

#endif
