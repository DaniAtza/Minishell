/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 23:13:03 by dagredan          #+#    #+#             */
/*   Updated: 2025/05/22 13:19:38 by dagredan         ###   ########.fr       */
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

typedef struct s_data
{
	char	*line;		// User input
	t_token	*tokens;	// Linked list of tokens extracted from line
}	t_data;

#endif