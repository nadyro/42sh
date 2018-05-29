#include "lexer.h"
#include "libft.h"
#include <stdio.h>

typedef struct	s_ast
{
	int						*tok;
	char					*arg;
	int						depth;	//0 = original, 1 = split ;, 2 = split by && / ||, 3 = split by |, 4 = simple command
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

static t_ast	*fill_leftast(t_ast *parent, int size, int depth)
{
	t_ast	*left = NULL;

	if (!(left = (t_ast *)malloc(sizeof(t_ast))))
		return (NULL);
	left->parent = parent;
	left->arg = ft_strndup(parent->arg, size);
	left->depth = depth;
	left->tok = get_tokens(left->arg);
	left->left = NULL;
	left->right = NULL;
	printf("in fill_leftast, left->arg = %s\n", left->arg);
	return (left);
}

static t_ast	*fill_rightast(t_ast *parent, int start, int size, int depth)
{
	t_ast	*right = NULL;
	char	*str;

	if (!(right = (t_ast *)malloc(sizeof(t_ast))))
		return (NULL);
	right->parent = parent;
	str = parent->arg + start;
	right->arg = ft_strndup(str, size);
	right->depth = depth;
	right->tok = get_tokens(right->arg);
	printf("right->tok[0]=%d\nright->tok[1]=%d\nright->tok[2]=%d\n", right->tok[0], right->tok[1], right->tok[2]);
	right->left = NULL;
	right->right = NULL;
	printf("in fill_rightast, right->arg = %s\nSENDING TO RECURSION\n", right->arg);
	return (right);
}

static t_ast	*init_ast(char ***argv)
{
	t_ast	*head;
	char	**tab = *argv;
	printf("DEBUG init1\n");
	if (!(head = (t_ast *)malloc(sizeof(t_ast))))
			return (NULL);
	printf("DEBUG init2\n");		
	head->parent = NULL;
	head->depth = 0;
	printf("*argv[1] = %s\nstrlen av1 = %zu\n", tab[1], ft_strlen(tab[1]));
	head->arg = (tab[1]) ? ft_strndup(tab[1], ft_strlen(tab[1])) : NULL;
	printf("DEBUG init3\n");	
	head->tok = get_tokens(head->arg);
	printf("DEBUG init4\n");
	head->left = NULL;
	head->right = NULL;
	printf("DEBUG init5\n");	
	return (head);
}

static void		ast_loop(t_ast *head)
{
	int		i = 0;
	t_ast	*tmp = head;
	char	*str = tmp->arg;
	char	*chr = NULL;
	int		start = 0;

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
		printf("DEBUG 5, depth = %d\ni = %d\ntmp->tok[i] = %d\n", tmp->depth, i, tmp->tok[i]);
		if (tmp->tok[i] == 10)
		{
			printf("DEBUG 6, i = %d\n", i);
			tmp->left = fill_leftast(tmp, tmp->tok[i+1], 1);
			printf("DEBUG 7, i = %d\ntmp->tok[i + 3] = %d\n", i, tmp->tok[i+3]);
			i += 3;
			while (tmp->tok[i] == 12)
				i += 3;
			if (tmp->tok[i] && tmp->tok[i] != 1 && tmp->tok[i] != 16)
			{
				printf("BEFORE filling tmp->right, i = %d\ntoken values should be: 0 = %d\n1 = %d\n2 = %d\n", i, tmp->tok[i], tmp->tok[i+1], tmp->tok[i+2]);
				tmp->right = fill_rightast(tmp, tmp->tok[i+1], ft_strlen(tmp->arg) - tmp->tok[i+1], 1);
				ast_loop(tmp->right);
				break ;
			}
			else
				tmp->right = NULL;
			printf("DEBUG 8\n");
		}
		else
			i += 3;
		while (tmp->tok[i] == 12)
			i += 3;
		printf("DEBUG 9, i = %d\n", i);
		//recursion here? tmp = tmp->left or tmp=tmp->right w conditions?
	}
	printf("DEBUG 10\n");
}

static t_ast	*get_ast(int **tab, char ***argv)
{
	char	*str = NULL;
	t_ast	*head;
	t_ast	*tmp;

	printf("DEBUG 2\n");
	head = (*tab[0] && *tab[0] != 16) ? init_ast(argv) : NULL;
	tmp = head;
	printf("DEBUG 3\n");
	ast_loop(tmp);
	printf("DEBUG 4\n");
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
		printf("DEBUG 1\n");
		head = get_ast(&tab, &argv);
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
