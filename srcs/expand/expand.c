/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 15:35:08 by dagredan          #+#    #+#             */
/*   Updated: 2025/07/22 20:08:02 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_variable_name(t_token *token, t_expan *expan)
{
	size_t	i;

	expan->name_start = ft_strcspn(token->value, "$") + 1;
	i = expan->name_start;
	if (!ft_isalpha(token->value[i]) && token->value[i] != '_')
		return (0);
	while (ft_isalnum(token->value[i]) || token->value[i] == '_')
		i++;
	expan->name_len = i - expan->name_start;
	expan->name = ft_substr(token->value, expan->name_start, expan->name_len);
	if (!expan->name)
		return (perror_return("malloc", -1));
	return (0);
}

static void	replace_variable(t_token *token, t_expan *expan)
{
	char	*new;
	int		i;

	expan->srcs[0] = token->value;
	expan->sizes[0] = expan->name_start;
	expan->srcs[1] = expan->value;
	expan->sizes[1] = expan->sizes[0] + ft_strlen(expan->value);
	expan->srcs[2] = token->value + expan->name_start + expan->name_len;
	expan->sizes[2] = expan->sizes[1] + ft_strlen(expan->srcs[2]);
	new = ft_calloc(expan->sizes[2], sizeof(char));
	if (!new) // TODO: Handle error
		return ;
	i = 0;
	while (i < 3)
	{
		ft_strlcat(new, expan->srcs[i], expan->sizes[i]);
		i++;
	}
	free(token->value);
	token->value = new;
}

int	expand_words(t_token *token_list, t_env *env_list)
{
	t_expan	expan;
	t_token	*curr_token;

	curr_token = token_list;
	while (curr_token)
	{
		while (curr_token->type == WORD && ft_strchr(curr_token->value, '$'))
		{
			ft_memset(&expan, 0, sizeof(t_expan));
			if (get_variable_name(curr_token, &expan) < 0)
				return (0);
			if (!expan.name)
				return (0);
			expan.value = search_env(expan.name, env_list);
			if (!expan.value)
				expan.value = ft_strdup("");
			if (!expan.value)
				return (perror_return("malloc", -1));
			replace_variable(curr_token, &expan);
		}
		curr_token = curr_token->next;
	}
	return (0);
}
