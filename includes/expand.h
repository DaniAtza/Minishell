/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 01:42:47 by dagredan          #+#    #+#             */
/*   Updated: 2025/07/27 01:42:49 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "types.h"

// Segment type

typedef enum e_segm_type
{
	TEXT,		// Regular text segment
	PARAMETER,	// Parameter segment, like $VAR or $?
	QUOTE		// Quote character, like ' or "
}	t_segm_type;

// Segment

typedef struct s_segm
{
	struct s_segm	*next;			// Next segment, or NULL
	char			*start;			// Pointer to start of the segment
	size_t			len;			// Length of the segment excluding null char
	int				double_quoted;	// Bool flag if the segment is double quoted
	int				single_quoted;	// Bool flag if the segment is single quoted
	t_segm_type		type;			// Type of the segment
}	t_segm;

// Word

typedef struct s_word
{
	struct s_word	*next;		// Next word element, or NULL
	char			*string;	// String of the word being expanded
	t_segm			*segments;	// Linked list of segments of the word
}	t_word;

// Segments

t_word	*create_word(char *word);
t_segm	*create_segment(char *start, size_t len, t_segm_type type);
void	append_segment(t_segm *new_segment, t_word *word);
void	concat_word_segments(t_word *word);

void	identify_segments(t_word *word);
void	identify_quoted_segments(t_word *word);

// Expand

int		expand_words(t_process *processes, t_data *data);
char	*expand_heredoc_line(char *line, t_data *data);
void	expand_parameters(t_word *word, t_data *data);
void	remove_quotes(t_word *word);

int		is_valid_name_first_char(char c);
int		is_valid_name_char(char c);
int		is_param_start(char c);
int		contains_parameters(char *string);
int		contains_quotes(char *string);

#endif
