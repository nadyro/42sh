/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 14:38:42 by antoipom          #+#    #+#             */
/*   Updated: 2018/08/16 18:54:45 by tcanaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "heredoc.h"

static void		*get_cwd_prompt_next(char *pwd)
{
	int		i;
	char	*ptr;
	char	*ptr2;

	i = ft_strlen(pwd) - 1;
	while (i > 0 && pwd[i - 1] != '/')
		i--;
	ptr = ft_strjoin("\x1b[36m[", pwd + i);
	ptr2 = ft_strjoin(ptr, "]\x1b[0m ");
	free(ptr);
	return (ptr2);
}

static char		*get_cwd_prompt(t_shell shell)
{
	char	pwd[1024];
	t_env	*tmp;

	ft_bzero(pwd, 1024);
	tmp = shell.list;
	while (tmp)
	{
		if (!(ft_strcmp(tmp->var, "PWD")))
		{
			ft_strcpy(pwd, tmp->val);
			break ;
		}
		tmp = tmp->next;
	}
	if (pwd[0] == '\0' && getcwd(pwd, 1024) == NULL)
	{
		ft_putendl_fd("pwd error", 2);
		return (ft_strcpy(ft_strnew(2), "> "));
	}
	return (get_cwd_prompt_next(pwd));
}

static char		*line_mgmt(char *line, t_node *history, t_shell shell)
{
	char *prompt;
	char *ret;
	char *tmp;

	ret = NULL;
	if (line == NULL)
	{
		prompt = get_cwd_prompt(shell);
		ret = line_edit_main_loop(prompt, history, 1);
		free(prompt);
	}
	else
	{
		tmp = line_edit_main_loop("> ", history, 1);
		if (tmp != NULL)
			ret = ft_strjoin(line, tmp);
		free(tmp);
		free(line);
	}
	return (ret);
}

static void		main_exec(t_shell *shell, char **line)
{
	int		parser_ret;
	t_ast	*head;

	head = NULL;
	if ((parser_ret = parser_validation(shell->tok, *line)) == 1)
	{
		shell->line = ft_strdup(*line);
		if (shell->tok && shell->tok[0])
		{
			shell->history = add_to_history(*line, shell->history);
			head = get_ast(shell);
			shell->to_add++;
			shell->history_length++;
		}
		ast_evaluate(head, shell);
		free_ast(head);
		shell->last_hd = -1;
		ft_strdel(line);
		ft_strdel(&(shell->line));
	}
	else if (parser_ret == 0)
		ft_strdel(line);
}

void			main_loop(char *line, t_shell shell)
{
	t_node	*history;
	char	*tmp;

	history = NULL;
	tmp = getenv("HOME");
	if (tmp != NULL)
		shell.home_env = ft_strjoin(tmp, "/.42sh_history");
	history = fill_history_file(history, &shell);
	shell.history = history;
	heredoc_manager(0);
	while (1)
	{
		line = line_mgmt(line, shell.history, shell);
		history_m(0, shell.history);
		heredoc_manager(2);
		if (line && (shell.tok = get_tokens(&line)) != NULL)
		{
			main_exec(&shell, &line);
			if (shell.tok)
			{
				free(shell.tok);
				shell.tok = NULL;
			}
		}
	}
}
