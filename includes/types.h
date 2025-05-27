/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 23:13:03 by dagredan          #+#    #+#             */
/*   Updated: 2025/05/24 19:46:22 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stddef.h>

typedef enum e_token_type
{
	LESS,	// "<"
	GREAT,	// ">"
	DLESS,	// "<<"
	DGREAT,	// ">>"
	VLINE,	// "|"
	WORD,	// Everything else
}	t_token_type;

typedef struct s_token
{
	struct s_token	*next;	// Next element, or NULL
	char			*value;	// Zero terminated string if WORD type, or NULL
	t_token_type	type;	// Type of the token
}	t_token;

typedef struct s_lexer
{
	size_t			i;				// Current index in the line being scanned
	size_t			token_start;	// Index of the beginning of the new token
	t_token_type	type;			// Type of the new token
	t_token			*tokens;		// Provisional linked list of tokens
}	t_lexer;

typedef struct s_redirect
{
	struct s_redirect	*next;		// Next element, or NULL
	char				*filename;	// 'pathname' value for open()
	int					flags;		// 'flags' value for open()
	mode_t				mode;		// 'mode' value for open()
	int					target_fd;	// 'newfd' value for dup2()
	int					is_heredoc;	// Boolean flag if '<<' found
	char				*delimiter;	// The word after '<<', or NULL
}	t_redirect;

typedef struct s_process
{
	struct s_process	*next;			// Next element, or NULL
	pid_t				pid;			// Child process PID, assigned on fork()
	int					pipe_read_fd;	// Read end of the pipe to read from
	int					pipe_write_fd;	// Write end of the pipe to write to
	t_redirect			*redirects;		// Linked list of redirections to make
	char				*pathname;		// 'pathname' value for execve()
	char				**argv;			// 'argv' value for execve()
}	t_process;

typedef struct s_parser
{
	t_token		*token;		// Current token being parsed
	t_process	*process;	// New process being populated
	t_process	*processes;	// Provisional linked list of processes
}	t_parser;

typedef struct s_data
{
	char		*line;				// User input
	t_token		*tokens;			// Linked list of tokens extracted from line
	t_process	*processes;			// Linked list of processes to execute
	size_t		processes_count;
	int	**pipes;
}	t_data;

#endif
