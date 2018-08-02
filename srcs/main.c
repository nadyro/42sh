#include "lexer.h"
#include "parser.h"
#include "libft.h"
#include "builtins.h"
#include "sh_line_edit.h"
#include "heredoc.h"
#include <stdio.h>

t_prompt	*prompt;

 char  *get_pwd(void)
{
	int    i;
	char  pwd[1024];
	char  *ptr;
	char  *ptr2;

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

int			main()
{
	char	*name_term;

	if ((name_term = getenv("TERM")) == NULL)
	{
		write(2, "Please set the environment variable TERM\n", 41);
		return (-1);
	}
	if (tgetent(NULL, name_term) == ERR)
		return (-1);

	char *str = "io1 io2\n";
	int token1[] = {0, 0, 3};
	int token2[] = {0, 4, 3};
	heredoc_manager(0);
	heredoc_add(token1, str);
	heredoc_add(token2, str);
	heredoc_fill();
	for (int i = 0; i < heredoc_manager(1); i++)
		printf("DOC[%d]= '%s'\n", i, heredoc_get(i));
	heredoc_manager(2);
}

