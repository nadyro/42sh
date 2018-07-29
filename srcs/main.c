#include "lexer.h"
#include "parser.h"
#include "libft.h"
#include "builtins.h"
#include "sh_line_edit.h"
#include <stdio.h>

t_prompt	*prompt;

char	*get_pwd(void)
{
	int		i;
	char	pwd[1024];
	char	*ptr;
	char	*ptr2;

	if (getcwd(pwd, 1024) == NULL)
	{
		ft_putendl_fd("pwd error", 2);
		return (ft_strcpy(ft_strnew(2), "> "));
	}
	i = ft_strlen(pwd) - 1;
	while (i > 0 && pwd[i - 1] != '/')
		i--;
	ptr = ft_strjoin("\x1b[36m[", pwd + i);
	ptr2 = ft_strjoin(ptr, "]\x1b[0m ");
	free(ptr);
	return (ptr2);
}

static char	*line_mgmt(char *line, t_node *history)
{
	char *prompt;
	char *ret;
	char *tmp;

	if (line == NULL)
	{
		prompt = get_pwd();
		ret = line_edit_main_loop(prompt, history);
		free(prompt);
	}
	else
	{
		tmp = line_edit_main_loop("> ", history);
		ret = ft_strjoin(line, tmp);
		free(tmp);
		free(line);
	}
	return (ret);
}

t_node		*init_nonvoid_history(char *cmd, t_node *history)
{
	t_node	*new;

	if (!(new = malloc(sizeof(*new))))
		exit(1);
	if (!(new->cmd = ft_strdup(cmd)))
		exit(1);
	new->next = history;
	new->prev = NULL;
	free(cmd);
	cmd = NULL;
	if (history)
		history->prev = new;
	history = new;
	return (history);
}

t_node		*fill_history_file(t_node *history)
{
	int		i;
	char	*c;
	int		gnl;

	c = NULL;
	gnl = 0;
	i = open(".history", O_RDWR | S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (i >= 0)
	{
		while ((gnl = get_next_line(i, &c)) == 1)
			history = init_nonvoid_history(c, history);
		close(i);
	}
	return (history);
}

void		main_loop(char *line, t_shell shell)
{
	//int		*token_tab;
	int		parser_ret;
	t_ast	*head;
	t_node	*history;
	
	head = NULL;
	history = NULL;
	history = fill_history_file(history);
	while (1)
	{
		line = line_mgmt(line, history);
		if ((shell.tok = get_tokens(line)) != NULL)
		{
			if ((parser_ret = parser_validation(shell.tok, line)) == 1)
			{
				shell.line = ft_strdup(line);
				if (shell.tok && shell.tok[0])
				{
					history = add_to_history(line, history);
					head = get_ast(&shell);
					shell.history = history;										
				}
				else
					printf("error: no token table was compiled in main\n");
				//printf("TREE COMPILED, SENDING TO printLeafNodes\n\n\n");
				ast_loop(&shell, head);
				ft_strdel(&line);
				ft_strdel(&(shell.line));
			}
			else if (parser_ret == 0)
				ft_strdel(&line);
		}
	}
}

int			main(int argc, char **argv, char **env)
{
	t_shell	shell;
	char	*name_term;

	(void)argc;
	(void)argv;
	///////////////////////////////////
	shell.list = (env && env[0]) ? env_setup(env) : env_init();
	shell.envv = (shell.list) ? env_to_tab(shell.list) : NULL;
	shell.error = 0;
	///////////////////////////////////
	if ((name_term = getenv("TERM")) == NULL)
	{
		write(2, "Please set the environment variable TERM\n", 41);
		return (-1);
	}
	if (tgetent(NULL, name_term) == ERR)
		return (-1);
	main_loop(NULL, shell);
	return (0);
}

//TESTS/////////////////////////////////////////////////////////////////////////
		//print_leaf_nodes(head);
//		printf("trying to call traverse_ast to analyze pipes\n");
//		traverse_ast(head, 3);
	/*	while (tab[i] != -1)
		{
			switch(tab[i])
			{
				case TK_WORD:
					printf("WORD \n");
					break;
				case TK_NEWLINE:
					printf("NEWLINE \n");
					break;
				case TK_IO_NUMBER:
					printf("IO_NUMBER \n");
					break;
				case TK_GREAT:
					printf("GREAT \n");
					break;
				case TK_DGREAT:
					printf("DGREAT \n");
					break;
				case TK_GREATAND:
					printf("GREATAND \n");
					break;
				case TK_LESS:
					printf("LESS \n");
					break;
				case TK_DLESS:
					printf("DLESS \n");
					break;
				case TK_LESSAND:
					printf("LESSAND \n");
					break;
				case TK_PIPE:
					printf("PIPE \n");
					break;
				case TK_SEMI:
					printf("SEMI \n");
					break;
				case TK_COMMENT:
					printf("COMMENT \n");
					break;
				//case TK_SPACE:
				//	printf("SPACE ");
				//	break;
				case TK_AND:
					printf("AND \n");
					break;
				case TK_AND_IF:
					printf("AND_IF \n");
					break;
				case TK_OR_IF:
					printf("OR_IF \n");
					break;
				case TK_END:
					printf("END \n");
					break;
				case TK_PROGRAM:
					printf("PROGRAM \n");
					break;
				case TK_QUOTED_WORD:
					printf("QUOTED_WORD \n");
					break;
				case TK_DQUOTED_WORD:
					printf("DQUOTED_WORD \n");
					break;
			}
			i += 3;
		}
		*/
	//if (ac >= 1 && av)
	//		ash_loop(&shell);
	//if (shell.list && shell->var && shell->var[0])
	//		free_env(shell.list);
///////////////////////////////////////////////////////////////////////////////
