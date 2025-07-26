/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 23:13:03 by dagredan          #+#    #+#             */
/*   Updated: 2025/07/26 18:09:19 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stddef.h>
# include <fcntl.h>

// Token type

typedef enum e_token_type
{
	LESS,	// "<"
	GREAT,	// ">"
	DLESS,	// "<<"
	DGREAT,	// ">>"
	VLINE,	// "|"
	WORD,	// Everything else
}	t_token_type;

// Token

typedef struct s_token
{
	struct s_token	*next;	// Next element, or NULL
	char			*value;	// Zero terminated string if WORD type, or NULL
	t_token_type	type;	// Type of the token
}	t_token;

// Redirect

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

// Process

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

// Pipeline

typedef struct s_pipeline
{
	char		*line;			// User input
	t_token		*tokens;		// Linked list of tokens extracted from line
	t_process	*processes;		// Linked list of processes to execute
	size_t		process_count;	// Number of processes in the pipeline
	int			**pipes;
}	t_pipeline;

// Env

typedef struct s_env
{
	struct s_env	*next;	// Next element, or NULL
	char			*name;	// Name of the environment variable
	char			*value;	// Value of the environment variable
}	t_env;

// Data

typedef struct s_data
{
	t_env		*env_list;			// Linked list of environment variables
	char		*current_pwd;		// Current working directory
	int			last_exit_status;	// Exit status of the last executed pipeline
}	t_data;

#endif
