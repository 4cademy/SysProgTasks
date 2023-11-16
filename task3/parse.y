/* -*- indented-text -*- */

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "functions.h"
#include "myshell.h"

int yylex(void);
void yyerror (char const *s) {
   fprintf (stderr, "%s\n", s);
 }

char* args = "";
char* output = "";
char* input = "";

%}

%union {
       char *string;
}


%start cmd_line
%token <string> EXIT PIPE INPUT_REDIR OUTPUT_REDIR STRING NL BACKGROUND


%%
cmd_line    :
        | EXIT             {
                                exit(0);
                            }
        | pipeline back_ground
        ;

back_ground : BACKGROUND        {
                                execute(true);
                                }
        |                       {
                                execute(false);
                                }
        ;

simple      : command redir
        ;

command     : command STRING
                {
                add_argument($2);
		}
	| STRING
		{
		new_command($1);
		}
        ;

redir       : input_redir output_redir
        ;

output_redir:    OUTPUT_REDIR STRING
                {
                set_output($2);
                }
        |        /* empty */
				{
				}
        ;

input_redir:    INPUT_REDIR STRING
                {
                set_input($2);
                }
        |       /* empty */
                {
				}
        ;

pipeline    : pipeline PIPE simple
                {
                }
        | simple
                {
                }
        ;
%%

/* Declarations */
void set_input_string(const char* in);
void end_lexical_scan(void);

/* This function parses a string */
int parse_string(const char* in) {
  set_input_string(in);
  int rv = yyparse();
  end_lexical_scan();
  return rv;
}
