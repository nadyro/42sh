#include "lexer.h"
#include "parser.h"
#include "libft.h"
#include "builtins.h"
#include "sh_line_edit.h"
#include <stdio.h>

t_prompt	*prompt;

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

static char	*line_mgmt(char *line, t_shell shell, t_node *history)
{
	char *prompt;
	char *ret;
	char *tmp;

	if (line == NULL)
	{
		prompt = get_pwd(&shell);
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

void		main_loop(char *line, t_shell shell)
{
	//int		*token_tab;
	int		parser_ret;
	t_ast	*head;
	t_node	*history;

	head = NULL;
	history = NULL;
	//Nadir's part! Do not touch ! >=E
	history = fill_history_file(history, &shell);
	shell.history = history;         				
	//End of Nadir's part.	
	while (1)
	{
		line = line_mgmt(line, shell, history);
		if ((shell.tok = get_tokens(line)) != NULL)
		{
			//test_tokens(shell.tok);
			if ((parser_ret = parser_validation(shell.tok, line)) == 1)
			{
				shell.line = ft_strdup(line);
				if (shell.tok && shell.tok[0])
				{
					history = add_to_history(line, history);
					head = get_ast(&shell);
					//Nadir's part! Do not touch ! >=E					
					shell.history_length++;
					//End of Nadir's part.
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
	shell.history_length = 0;
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

/*static void	test_tokens(int *tok)
{
	int		i = 0;

	while (tok[i] != -1)
	{
		switch(tok[i])
		{
			case TK_WORD:
				printf("WORD \n");
				break;
			case TK_FILENAME:
				printf("FILENAME \n");
				break;
			case TK_CMD:
				printf("COMMAND \n");
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
			//case TK_AND:
			//	printf("AND \n");
			//	break;
			case TK_AND_IF:
				printf("AND_IF \n");
				break;
			case TK_OR_IF:
				printf("OR_IF \n");
				break;
			case TK_END:
				printf("END \n");
				break;
		}
		i += 3;
	}
}*/







//TESTS/////////////////////////////////////////////////////////////////////////
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
