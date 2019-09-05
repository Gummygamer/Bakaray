%{
	#include <stdio.h>
	
	int triangulos = 1;
%}


%%
"var"(.+)"=" printf(" ");
"\"" printf(" ");
"," printf(" ");
"\";" printf("\n %d \n",triangulos);
";" { printf(" T "); triangulos++; }
%%

int yywrap()
{
	return 0;
}

int main()
{
	printf("T ");
	yylex();
	yywrap();
	return 0;
}
