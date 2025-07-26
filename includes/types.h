/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 23:13:03 by dagredan          #+#    #+#             */
/*   Updated: 2025/07/26 17:52:46 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stddef.h>
# include <fcntl.h>

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

typedef struct s_pipeline
{
	char		*line;				// User input
	t_token		*tokens;			// Linked list of tokens extracted from line
	t_process	*processes;			// Linked list of processes to execute
	size_t		process_count;
	int			**pipes;
}	t_pipeline;

typedef struct s_data
{
	t_env		*env_list;
	char		*current_pwd;
	int			last_exit_status;
}	t_data;

#endif
