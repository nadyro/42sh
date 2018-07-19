#include "lexer.h"
#include "parser.h"
#include "libft.h"
#include "builtins.h"
#include "sh_line_edit.h"
#include <stdio.h>

t_prompt	*prompt;
t_shell		g_shell;

static char	*get_pwd(t_shell *shell)
{
	int		i;
	t_shell *shell_ptr;
	char	*ptr;
	char	*ptr2;

	shell_ptr = shell;
	while (shell_ptr->list && ft_strcmp(shell_ptr->list->var, "PWD") != 0)
		shell_ptr->list = shell_ptr->list->next;
	if (shell_ptr->list == NULL)
	{
		ft_putstr("pwd error");
		exit(1);
	}
	i = ft_strlen(shell_ptr->list->val) - 1;
	while (i > 0 && (shell_ptr->list->val)[i - 1] != '/')
		i--;
	ptr = ft_strjoin("\x1b[36m[", (shell_ptr->list->val) + i);
	ptr2 = ft_strjoin(ptr, "]\x1b[0m ");
	free(ptr);
	return (ptr2);
}

static char	*line_mgmt(char *line)
{
	char *prompt;
	char *ret;
	char *tmp;

	if (line == NULL)
	{
		prompt = get_pwd(&g_shell);
		ret = line_edit_main_loop(prompt);
		free(prompt);
	}
	else
	{
		tmp = line_edit_main_loop("> ");
		ret = ft_strjoin(line, tmp);
		free(tmp);
		free(line);
	}
	return (ret);
}

void		main_loop(char *line)
{
	int		*token_tab;
	int		parsing_return;
	t_ast	*head;

	head = NULL;
	while (1)
	{
		line = line_mgmt(line);
		if ((token_tab = get_tokens(line)) != NULL)
		{
			parsing_return = parser_validation(token_tab);
			if (parsing_return != -1)
			{
				write(1, "parse error near '", 18);
				write(1, line + token_tab[parsing_return + 1], token_tab[parsing_return + 2]);
				write(1, "'\n", 2);
			}
			else
			{
				if (token_tab && token_tab[0])
					head = get_ast(line);
				else
					printf("error: no token table was compiled in main\n");
				//printf("TREE COMPILED, SENDING TO printLeafNodes\n\n\n");
				ast_loop(&g_shell, head);
			}
			free(line);
			line = NULL;
		}
		//else
		//	line[ft_strlen(line) - 1] = '\0';
	}
}

int			main(int argc, char **argv, char **env)
{
	t_shell	shell;
	char	*name_term;

	(void)argc;
	(void)argv;
	///////////////////////////////////
	g_shell.list = (env && env[0]) ? env_setup(env) : env_init();
	g_shell.envv = (shell.list) ? env_to_tab(shell.list) : NULL;
	g_shell.error = 0;
	///////////////////////////////////
	if ((name_term = getenv("TERM")) == NULL)
	{
		write(2, "Please set the environment variable TERM\n", 41);
		return (-1);
	}
	if (tgetent(NULL, name_term) == ERR)
		return (-1);
	main_loop(NULL);
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
