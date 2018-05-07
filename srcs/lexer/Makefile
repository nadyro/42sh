all:
	gcc -g -fsanitize=address -fno-omit-frame-pointer main.c lexer.c ../../libft/ft_memset.c -I../../includes

clean:
	rm a.out
	rm -rf a.out.dSYM
	
re: clean all
