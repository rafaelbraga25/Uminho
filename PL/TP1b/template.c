#include <stdio.h>
#include <string.h>

char* Fli(char* ele)
{
	char BUF[10000];
	int j = 0;
	j += sprintf(BUF + j, "<li> %s </li>\n");
	strdup(BUF);
}


char* Fhtml(char* tit, char* tit, char* MAP, char* Fli, char* comp, char* items)
{
	char BUF[10000];
	int j = 0;
	j += sprintf(BUF + j, "<html>\n");
	j += sprintf(BUF + j, "	<head><title>%s</title></head>\n");
	j += sprintf(BUF + j, "<body>\n");
	j += sprintf(BUF + j, "	<h1>%s</h1>\n");
	j += sprintf(BUF + j, "	<ul>%s</ul>\n");
	j += sprintf(BUF + j, "</body>\n");
	j += sprintf(BUF + j, "</html>\n");
	strdup(BUF);
}


int main(){
	char * a[]={"expressões regulares","parsers","compiladores"};
	printf("%s\n",Fhtml("Conteudo programático", 3, a));
}
