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

typedef struct s_expan
{
	char	*name;
	char	*value;
	size_t	name_start;
	size_t	name_len;
	char	*srcs[3];
	size_t	sizes[3];
}	t_expan;

// Expand

int		expand_words(t_token *token_list, t_env *env_list);

#endif
