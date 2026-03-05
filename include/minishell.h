/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by marvin            #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

/* ======================== SINGLE GLOBAL ======================== */

extern volatile sig_atomic_t	g_signal;

/* ======================== TOKEN ======================== */

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

/* ======================== REDIR ======================== */

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_HEREDOC,
	REDIR_APPEND,
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*filename;
	int				heredoc_fd;
	struct s_redir	*next;
}	t_redir;

/* ======================== COMMAND ======================== */

typedef struct s_cmd
{
	char			**args;
	int				arg_count;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

/* ======================== ENV ======================== */

typedef struct s_env
{
	char			*key;
	char			*value;
	int				has_value;
	struct s_env	*next;
}	t_env;

/* helper used internally to create nodes */
t_env	*env_new_node(const char *key, const char *val, int hv);

/* ======================== SHELL ======================== */

typedef struct s_shell
{
	t_env	*env;
	int		exit_status;
	int		running;
}	t_shell;

/* ======================== LEXER ======================== */

t_token	*lexer(char *input);
t_token	*new_token(t_token_type type, char *value);
void	token_add_back(t_token **lst, t_token *new_tok);

/* ======================== PARSER ======================== */

t_cmd	*parser(t_token *tokens);
int		check_syntax(t_token *tokens);
t_cmd	*new_cmd(void);
void	cmd_add_arg(t_cmd *cmd, char *word);
void	cmd_add_redir(t_cmd *cmd, t_redir_type type, char *fname);

/* ======================== EXPANDER ======================== */

void	expander(t_cmd *cmds, t_shell *sh);
char	*expand_word(char *w, t_shell *sh);
char	*str_append(char *dst, const char *src);
char	*str_append_char(char *dst, char c);
char	*expand_var(char *s, int *i, t_shell *sh);
int		is_var_start(char *w, int i, int st);
int		update_quote_state(char c, int *st);

/* ======================== EXECUTOR ======================== */

void	executor(t_cmd *cmds, t_shell *sh);
void	exec_single_builtin(t_cmd *cmd, t_shell *sh);
void	exec_pipeline(t_cmd *cmds, t_shell *sh);
void	exec_child(t_cmd *cmd, t_shell *sh, int in_fd, int *pfd);
void	exec_child_proc(t_cmd *cmd, t_shell *sh, int in_fd, int *pfd);
char	*resolve_path(char *cmd, t_shell *sh);
int		apply_redirections(t_cmd *cmd);
int		setup_heredocs(t_cmd *cmds, t_shell *sh);
void	close_heredocs(t_cmd *cmds);
int		has_quotes(const char *s);
char	*strip_quotes(const char *s);

/* ======================== BUILTINS ======================== */

int		is_builtin(char *cmd);
int		exec_builtin(t_cmd *cmd, t_shell *sh);
int		builtin_echo(t_cmd *cmd);
int		builtin_cd(t_cmd *cmd, t_shell *sh);
int		builtin_pwd(void);
int		builtin_export(t_cmd *cmd, t_shell *sh);
int		builtin_unset(t_cmd *cmd, t_shell *sh);
int		builtin_env(t_shell *sh);
int		builtin_exit(t_cmd *cmd, t_shell *sh);
int		builtin_history(void);
int		is_valid_identifier(const char *s);
int		env_count(t_env *env);
t_env	*env_find_min(t_env *env, t_env **visited, int v_count);
void	print_one_export(t_env *min);

/* ======================== ENV ======================== */

t_env	*env_init(char **envp);
char	*env_get(t_env *env, const char *key);
int		env_set(t_env **env, const char *key, const char *val, int hv);
int		env_unset(t_env **env, const char *key);
char	**env_to_array(t_env *env);
void	env_free_list(t_env *env);
void	env_free_array(char **arr);
int		env_size(t_env *env);

/* ======================== SIGNALS ======================== */

void	setup_signals_interactive(void);
void	setup_signals_child(void);
void	setup_signals_heredoc(void);
void	setup_signals_ignore(void);

/* ======================== UTILS ======================== */

void	print_error(char *cmd, char *arg, char *msg);
void	free_tokens(t_token *tokens);
void	free_cmds(t_cmd *cmds);
void	free_shell(t_shell *sh);
char	*ft_strjoin3(const char *a, const char *b, const char *c);
char	*ft_strdup(const char *s);
char	*ft_strndup(const char *s, size_t n);
int		ft_strcmp(const char *a, const char *b);
char	**ft_split(const char *s, char c);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
int		ft_isdigit(int c);
char	*ft_itoa(int n);
size_t	ft_strlen(const char *s);
void	print_tokens_table(t_token *tokens);
void	print_cmds_table(t_cmd *cmds, const char *title);

#endif
