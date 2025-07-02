/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:08:23 by dagredan          #+#    #+#             */
/*   Updated: 2025/06/24 14:16:22 by datienza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <readline/readline.h>
#include <readline/readline.h>
#include <readline/history.h>

# include "libft.h"
# include "env.h"
# include "lexer.h"
# include "parser.h"
# include "pipes.h"
# include "execute.h"
# include "builtin.h"

extern char	*g_current_pwd;//TODO

#endif
