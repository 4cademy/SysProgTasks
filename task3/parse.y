/* -*- indented-text -*- */

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "functions.h"

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

back_ground : BACKGROUND        { printf("background: background\n"); }
        |                       { printf("background: empty\n");  }
        ;

simple      : command redir
        ;

command     : command STRING
                {
                strcat(args, ":");
		strcat(args, $2);
		printf("command: %s\n", args);
		}
	| STRING
		{
		args = $1;
		printf("command: %s\n", args);
		}
        ;

redir       : input_redir output_redir
        ;

output_redir:    OUTPUT_REDIR STRING
                {
                output = $2;
                }
        |        /* empty */
				{
				output = "";
				}
        ;

input_redir:    INPUT_REDIR STRING
                {
                input = $2;
                }
        |       /* empty */
                {
                input = "";
				}
        ;

pipeline    : pipeline PIPE simple
                {
                }
        | simple
                {
                char** argv = Split(args, ':');
                ExecuteCommand(argv[0], argv, input, output);
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
