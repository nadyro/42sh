#include "lexer.h"
#include "libft.h"
#include <stdio.h>

typedef struct	s_ast
{
	int						*tok;
	char					*arg;
	int						split_by;
	//int						depth;	//0 = original, 1 = split ;, 2 = split by && / ||, 3 = split by |, 4 = simple command
	struct s_ast			*parent;
	struct s_ast			*left;
	struct s_ast			*right;
}				t_ast;

static char		*ft_strndup(const char *s1, size_t n)
{
	char		*str;
	size_t		i;

	i = 0;
	if (str)
	{
		if (!(str = (char *)malloc(sizeof(char) * n + 1)))
			return (NULL);
		while (s1[i] && i < n)
		{
			str[i] = s1[i];
			i++;
		}
		str[i] = '\0';
	}
	return (str);
}

size_t	ft_strlen(const char *s)
{
	size_t len;

	len = 0;
	while (*(s++))
		len++;
	return (len);
}

static t_ast	*fill_leftast(t_ast *parent, int size, int split_by)
{
	t_ast	*left = NULL;

	if (!(left = (t_ast *)malloc(sizeof(t_ast))))
		return (NULL);
	left->parent = parent;
	left->arg = ft_strndup(parent->arg, size);
	left->split_by = split_by;
	left->tok = get_tokens(left->arg);
	left->left = NULL;
	left->right = NULL;
	printf("in fill_leftast, left->arg = %s\n", left->arg);
	return (left);
}

static t_ast	*fill_rightast(t_ast *parent, int start, int size, int split_by)
{
	t_ast	*right = NULL;
	char	*str;

	if (!(right = (t_ast *)malloc(sizeof(t_ast))))
		return (NULL);
	right->parent = parent;
	str = parent->arg + start;
	right->arg = ft_strndup(str, size);
	right->split_by = split_by;
	right->tok = get_tokens(right->arg);
	right->left = NULL;
	right->right = NULL;
	printf("in fill_rightast, right->arg = %s\n", right->arg);
	return (right);
}

static t_ast	*init_ast(char ***argv)
{
	t_ast	*head;
	char	**tab = *argv;
	if (!(head = (t_ast *)malloc(sizeof(t_ast))))
			return (NULL);	
	head->parent = NULL;
	head->split_by = 0;
	head->arg = (tab[1]) ? ft_strndup(tab[1], ft_strlen(tab[1])) : NULL;
	head->tok = get_tokens(head->arg);
	head->left = NULL;
	head->right = NULL;	
	return (head);
}

static void		ast_loop_pipe(t_ast *head, int *depth)
{
	int		i = 0;
	t_ast	*tmp = head;
	char	*str = tmp->arg;
	int		split_by = 0;

	printf("entering ast_loop_and_or\n");
	while (tmp->tok[i] != -1)
	{
		printf("i = %d\n", i);
		if (tmp->tok[i] == TK_PIPE)
		{
			split_by = tmp->tok[i];
			tmp->left = fill_leftast(tmp, tmp->tok[i+1], split_by);
			i += 3;
			while (tmp->tok[i] == TK_SPACE)
				i += 3;
			if (tmp->tok[i] && tmp->tok[i] != 1 && tmp->tok[i] != TK_END)
			{
				tmp->right = fill_rightast(tmp, tmp->tok[i+1], ft_strlen(tmp->arg) - tmp->tok[i+1], split_by);
				printf("\nrecursively calling ast_loop_PIPE\n");
				ast_loop_pipe(tmp->right, depth);
				break ;
			}
			else
				tmp->right = NULL;
		}
		else
			i += 3;
		while (tmp->tok[i] == TK_SPACE)	//skips spaces in token table to find proper starting point before recreating another token table later
			i += 3;
		//recursion here? tmp = tmp->left or tmp=tmp->right w conditions?
	}
//	*depth = 3;
}

static void		ast_loop_and_or(t_ast *head, int *depth)
{
	int		i = 0;
	t_ast	*tmp = head;
	char	*str = tmp->arg;
	int		split_by = 0;

	printf("entering ast_loop_and_or\n");
	while (tmp->tok[i] != -1)
	{
		printf("i = %d\n", i);
		if (tmp->tok[i] == TK_AND_IF || tmp->tok[i] == TK_OR_IF)
		{
			split_by = tmp->tok[i];
			tmp->left = fill_leftast(tmp, tmp->tok[i+1], split_by);
			i += 3;
			while (tmp->tok[i] == TK_SPACE)
				i += 3;
			if (tmp->tok[i] && tmp->tok[i] != 1 && tmp->tok[i] != TK_END)
			{
				tmp->right = fill_rightast(tmp, tmp->tok[i+1], ft_strlen(tmp->arg) - tmp->tok[i+1], split_by);
				printf("\nrecursively calling ast_loop_and_or\n");
				ast_loop_and_or(tmp->right, depth);
				break ;
			}
			else
				tmp->right = NULL;
		}
		else
			i += 3;
		while (tmp->tok[i] == TK_SPACE)	//skips spaces in token table to find proper starting point before recreating another token table later
			i += 3;
		//recursion here? tmp = tmp->left or tmp=tmp->right w conditions?
	}
//	*depth = 3;
}

static void		ast_loop_semi(t_ast *head, int *depth)
{
	int		i = 0;
	t_ast	*tmp = head;
	char	*str = tmp->arg;

/*	printf("\n printing token table \n");
	while (tmp->tok[i] != -1)
	{
		printf("i = %d\ntmp->tok[i] = %d\n", i, tmp->tok[i]);
		i++;
	}
	printf("\n\n");
	i = 0;
*/	while (tmp->tok[i] != -1)
	{
		if (tmp->tok[i] == TK_SEMI)
		{
			tmp->left = fill_leftast(tmp, tmp->tok[i+1], TK_SEMI);
			i += 3;
			while (tmp->tok[i] == TK_SPACE)
				i += 3;
			if (tmp->tok[i] && tmp->tok[i] != 1 && tmp->tok[i] != 16)
			{
				tmp->right = fill_rightast(tmp, tmp->tok[i+1], ft_strlen(tmp->arg) - tmp->tok[i+1], TK_SEMI);
				printf("\nrecursively calling ast_loop_semi\n");
				if (tmp->right)
					ast_loop_semi(tmp->right, depth);
				break ;
			}
			else
				tmp->right = NULL;
		}
		else
			i += 3;
		while (tmp->tok[i] == TK_SPACE)	//skips spaces in token table to find proper starting point before recreating another token table later
			i += 3;
		//recursion here? tmp = tmp->left or tmp=tmp->right w conditions?
	}
	*depth = 2;
	printf("finished ast_loop_semi, depth = %d\n", *depth);
}

static void		traverse_ast(t_ast *head, int depth)
{
	t_ast	*tmp = NULL;

	tmp = head;
	while (tmp->left)
		tmp = tmp->left;
	printf("should be at left-most node in traverse ast, send to recursive funciton before recursively calling traverse_ast with parent->right\n");
	if (depth == 1)
		ast_loop_semi(tmp, &depth);
	if (depth == 2)
	{
		printf("should enter depth 2 loop of traverse ast\n");
		tmp = head;
		while (tmp->left)
			tmp = tmp->left;
		printf("starting and_or loop from taverse ast with str = %s\nparent = %s\ndepth = %d\n", tmp->arg, tmp->parent->arg, depth);
		ast_loop_and_or(tmp, &depth);
	}
	if (depth == 3)
	{
		printf("entering ast_loop_PIPE from traverse_ast\n");
		ast_loop_pipe(tmp, &depth);
	}
	/*
	else if (depth == 3)
		ast_loop_pipe(tmp);
	else if (depth == 4)
		redirection recursions
	else if (depth == 5)
		execution
	else if (depth = 6)
		free list
	*/	
	if (tmp->parent && tmp->parent->right && tmp->parent->right->left)	//i.e. if we've added to an existing tree, call recursively to analyze all nodes of tree
	{
		printf("recursive call to traverse_ast with str = %s\ndepth = %d\n", tmp->parent->right->arg, depth);
		traverse_ast(tmp->parent->right, depth);
	}
	printf("finished traverse ast\n");
}

static t_ast	*get_ast(int **tab, char ***argv)
{
	char	*str = NULL;
	t_ast	*head;
	t_ast	*tmp;

	head = (*tab[0] && *tab[0] != 16) ? init_ast(argv) : NULL;
	tmp = head;
	//ast_loop(tmp);
	traverse_ast(tmp, 1);
	return (head);
}

int				main(int argc, char **argv)
{
	int *tab;
	int i = 0;
	t_ast	*head = NULL;

	if (argc == 2)
	{
		printf("%s\n", argv[1]);
		tab = get_tokens(argv[1]);
		head = get_ast(&tab, &argv);
		printf("trying to call traverse_ast to analyze pipes\n");
		traverse_ast(head, 3);
		/*while (tab[i] != -1)
		{
			printf("i = %d\n", i);
			switch(tab[i])
			{
				case TK_WORD:
					printf("WORD \n, tab[i] = %d\ntab[i+1] = %d\ntab[i+2] = %d\n", tab[i], tab[i+1], tab[i+2]);
					break;
				case TK_NEWLINE:
					printf("NEWLINE \n, tab[i] = %d\ntab[i+1] = %d\ntab[i+2] = %d\n", tab[i], tab[i+1], tab[i+2]);
					break;
				case TK_IO_NUMBER:
					printf("IO_NUMBER \n, tab[i] = %d\ntab[i+1] = %d\ntab[i+2] = %d\n", tab[i], tab[i+1], tab[i+2]);
					break;
				case TK_GREAT:
					printf("GREAT \n, tab[i] = %d\ntab[i+1] = %d\ntab[i+2] = %d\n", tab[i], tab[i+1], tab[i+2]);
					break;
				case TK_DGREAT:
					printf("DGREAT \n, tab[i] = %d\ntab[i+1] = %d\ntab[i+2] = %d\n", tab[i], tab[i+1], tab[i+2]);
					break;
				case TK_GREATAND:
					printf("GREATAND \n, tab[i] = %d\ntab[i+1] = %d\ntab[i+2] = %d\n", tab[i], tab[i+1], tab[i+2]);
					break;
				case TK_LESS:
					printf("LESS \n, tab[i] = %d\ntab[i+1] = %d\ntab[i+2] = %d\n", tab[i], tab[i+1], tab[i+2]);
					break;
				case TK_DLESS:
					printf("DLESS \n, tab[i] = %d\ntab[i+1] = %d\ntab[i+2] = %d\n", tab[i], tab[i+1], tab[i+2]);
					break;
				case TK_LESSAND:
					printf("LESSAND \n, tab[i] = %d\ntab[i+1] = %d\ntab[i+2] = %d\n", tab[i], tab[i+1], tab[i+2]);
					break;
				case TK_PIPE:
					printf("PIPE \n, tab[i] = %d\ntab[i+1] = %d\ntab[i+2] = %d\n", tab[i], tab[i+1], tab[i+2]);
					break;
				case TK_SEMI:
					printf("SEMI \n, tab[i] = %d\ntab[i+1] = %d\ntab[i+2] = %d\n", tab[i], tab[i+1], tab[i+2]);
					break;
				case TK_COMMENT:
					printf("COMMENT \n, tab[i] = %d\ntab[i+1] = %d\ntab[i+2] = %d\n", tab[i], tab[i+1], tab[i+2]);
					break;
				//case TK_SPACE:
				//	printf("SPACE ");
				//	break;
				case TK_AND:
					printf("AND \n, tab[i] = %d\ntab[i+1] = %d\ntab[i+2] = %d\n", tab[i], tab[i+1], tab[i+2]);
					break;
				case TK_AND_IF:
					printf("AND_IF \n, tab[i] = %d\ntab[i+1] = %d\ntab[i+2] = %d\n", tab[i], tab[i+1], tab[i+2]);
					break;
				case TK_OR_IF:
					printf("OR_IF \n, tab[i] = %d\ntab[i+1] = %d\ntab[i+2] = %d\n", tab[i], tab[i+1], tab[i+2]);
					break;
				case TK_END:
					printf("END \n, tab[i] = %d\ntab[i+1] = %d\ntab[i+2] = %d\n", tab[i], tab[i+1], tab[i+2]);
					break;
				case TK_PROGRAM:
					printf("PROGRAM \n, tab[i] = %d\ntab[i+1] = %d\ntab[i+2] = %d\n", tab[i], tab[i+1], tab[i+2]);
					break;
				case TK_QUOTED_WORD:
					printf("QUOTED_WORD \n, tab[i] = %d\ntab[i+1] = %d\ntab[i+2] = %d\n", tab[i], tab[i+1], tab[i+2]);
					break;
				case TK_DQUOTED_WORD:
					printf("DQUOTED_WORD \n, tab[i] = %d\ntab[i+1] = %d\ntab[i+2] = %d\n", tab[i], tab[i+1], tab[i+2]);
					break;
			}
			i += 3;
		}*/
		printf("\n");
	} 
	return (0);
}
