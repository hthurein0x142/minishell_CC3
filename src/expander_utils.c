/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by marvin            #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_append(char *dst, const char *src)
{
	char	*result;
	int		dlen;
	int		slen;

	if (!src)
		return (dst);
	if (dst)
		dlen = ft_strlen(dst);
	else
		dlen = 0;
	slen = ft_strlen(src);
	result = malloc(dlen + slen + 1);
	if (!result)
		return (dst);
	if (dst)
		memcpy(result, dst, dlen);
	memcpy(result + dlen, src, slen);
	result[dlen + slen] = '\0';
	free(dst);
	return (result);
}

char	*str_append_char(char *dst, char c)
{
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	return (str_append(dst, tmp));
}

char	*expand_var(char *s, int *i, t_shell *sh)
{
	int		start;
	char	*name;
	char	*val;

	(*i)++;
	if (s[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(sh->exit_status));
	}
	if (!s[*i] || (!ft_isalpha(s[*i]) && s[*i] != '_'))
		return (ft_strdup("$"));
	start = *i;
	while (s[*i] && (ft_isalnum(s[*i]) || s[*i] == '_'))
		(*i)++;
	name = ft_strndup(s + start, *i - start);
	val = env_get(sh->env, name);
	free(name);
	if (val)
		return (ft_strdup(val));
	return (ft_strdup(""));
}

int	is_var_start(char *w, int i, int st)
{
	return (w[i] == '$' && st != 1 && w[i + 1]
		&& (ft_isalpha(w[i + 1]) || w[i + 1] == '_'
			|| w[i + 1] == '?'));
}

char	*expand_word(char *w, t_shell *sh)
{
	char	*res;
	char	*val;
	int		i;
	int		st;
	int		changed;

	res = ft_strdup("");
	i = 0;
	st = 0;
	while (w[i])
	{
		changed = update_quote_state(w[i], &st);
		if (!changed && is_var_start(w, i, st))
		{
			val = expand_var(w, &i, sh);
			res = str_append(res, val);
			free(val);
			continue ;
		}
		if (!changed)
			res = str_append_char(res, w[i]);
		i++;
	}
	return (res);
}
