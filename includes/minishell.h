/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:08:23 by dagredan          #+#    #+#             */
/*   Updated: 2025/07/26 18:59:41 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>

# include "libft.h"

# include "signals.h"
# include "env.h"
# include "core.h"
# include "tokenize.h"
# include "parse.h"
# include "expand.h"
# include "pipes.h"
# include "execute.h"
# include "builtin.h"

#endif
