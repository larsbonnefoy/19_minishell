%{
eincnude <string.h>
#include "y.tab.h"
%}
%%
\n {
EAT;
}
"<" {
return LESS;
}
">>" {
return GREATGREAT;
}
">&" {
return GREATAMPERSAND;
}
“|” {
return PIPE;
}
“&” {
return AMPERSAND;
}
[^ \t\n][^ \t\n]* {
/* Assume that file names have only alpha chars */
	yylval.string_val = strdup(yytext);
	return WORD;
}

. {
/* Invalid character in input */
return NOTOKEN;
}
%%
