// lexer.h : performs lexical analysis on a source code file, transforms it into tokens
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "types.h"
#include "error.h"
#include "id_table.h"

#define MAX_SYMBOL_TABLE_SIZE 100
#define NB_KEYWORDS 16

FILE * source;
int flag, line = 1;

int symbol_table_size = 0;
struct Symbol* symbol_table[MAX_SYMBOL_TABLE_SIZE];

int is_keyword(char *buffer) {
	char keywords[NB_KEYWORDS][MAX_LENGTH] = {
        "program","var","integer","char","begin","end","if","then",
        "else","while","do","read","readln","write","writeln"
	};
	int i, flag = -1;
	for(i = 0; i < NB_KEYWORDS; i++) {
		// printf("%s\t%s\n", buffer, keywords[i]);
		if (strcmp(keywords[i], buffer) == 0){
			// printf("its a keyword!\n");
            flag = i;
            break;
        }
	}
	return flag; // if -1 then not keyword, else index of 
}

void add_symbol(int type, int attr, int pos) {
	struct Symbol* item = (struct Symbol*)malloc(sizeof(struct Symbol));
	item->type = type;
	item->attr = attr;
	item->line = pos;
	symbol_table[symbol_table_size] = item;
    symbol_table_size++; 
}

void next_symbol() {
	int ch;
	int type, attr, pos;
	read_char:
	while((ch = fgetc(source)) != EOF) {
		switch(ch) {
	        case ' ': case '\t': goto read_char;
	        case '\n': ++line; goto read_char;
	        case EOF: type = DOLLAR; attr = 0; break;
	        case '+': type = OPADD; attr = ADD; break;
	        case '-': type = OPADD; attr = SUB; break;
	        case '*': type = OPMUL; attr = MUL; break;
	        case '/': type = OPMUL; attr = DIV; break;  
	        case '%': type = OPMUL; attr = MOD; break;     
	        case '(': type = OPP; attr = 0; break;
	        case ')': type = CLP; attr = 0; break;
	        case ';': type = SEMCOL; attr = 0; break;
	      	case '.': type = PT; attr = 0; break;
	        case ',': type = COMMA; attr = 0; break;
	        case ':': 
	        	// check next char, if = then OPAFF else go back and DP
	        	if((ch = fgetc(source)) == '=') {
	        		type = OPAFF; attr = 0;
	        	} else {
	        		type = DBPT; attr = 0;
	        		// go back one char
	        		ungetc(ch, source);
	        	}
	        	break;
	        case '=':
	        	// check next char, if = then OPEREL EQ, else lexical error??
	        	if((ch = fgetc(source)) == '=') {
	        		type = OPEREL; attr = EQ;
	        	} else {
	        		fatal_error("lexical error", "invalid character encountered after =");
	        	}
	        	break;
	        case '<':
	            // check next char, if = then OPEL INF_EQ, if > then OPEREL DIFF, else go back and OPEREL INF
	        	if((ch = fgetc(source)) == '=') {
	        		type = OPEREL; attr = INF_EQ;
	        	} else if (ch == '>') {
	        		type = OPEREL; attr = NE;
	        	} else {
	        		type = OPEREL; attr = INF;
	        		// go back one char
	        		ungetc(ch, source);
	        	}
	        	break;
	        case '>':
	            // check next char, if = then OPEREL SUP_EQ, else go back and OPEREL SUP
	            if((ch = fgetc(source)) == '=') {
	        		type = OPEREL; attr = SUP_EQ;
	        	} else {
	        		type = OPEREL; attr = SUP;
	        		// go back one char
	        		ungetc(ch, source);
	        	}
	        	break;
	        case '|':
	        	// check next char, if | then OPADD OR, else lexical error??
	        	if ((ch = fgetc(source)) == '|') {
	        		type = OPADD; attr = OR;
	        	} else {
	        		fatal_error("lexical error", "invalid character encountered after |");
	        	}
	        	break;
	        case '&':
	        	// check next char, if & then OPMUL AND, else lexical error???
	        	if ((ch = fgetc(source)) == '&') {
	        		type = OPMUL; attr = AND;
	        	} else {
	        		fatal_error("lexical error", "invalid character encountered after &");
	        	}
	        	break;
	        default:
	        	// if isalpha, loop while isalpha or isdigit, check if its keyword then keyword else isdigit
	        	if(isalpha(ch)) {
	        		// either id or keyword
	        		char * word = malloc(MAX_LENGTH*sizeof(char));
	        		int len = 0;
	        		word[len] = ch;
	        		do {
	        			word[++len] = (ch = fgetc(source));
	        		} while(isalpha(ch) || isdigit(ch));
	        		// we have one extra character, replace it with \0
	        		word[len] = '\0';
	        		// printf("%s\n", word);
	        		if((flag = is_keyword(word)) == -1) {
	        			type = ID;
	        			attr = add_id(word);
	        		} else {
	        			type = flag; attr = 0;
	        		}
	        		ungetc(ch, source);
	        	}
	        	// if isdigit, then NB and loop while its isdigit
	        	else if(isdigit(ch)) {
	        		int val = ch - '0';
	        		while (isdigit(ch = fgetc(source))) {
	                    val = val * 10 + (ch - '0');
	        		}
	                type = NB; attr = val;
	               	ungetc(ch, source);
	        	}
	        	else {
	        		// we need to throw a lexical error and stop lexical analysis
	        	}
	        	break;
		} // end of switch
		add_symbol(type, attr, line);
	} // end of while
}

void print_symbols() {
	int i;
	for(i = 0; i<symbol_table_size; i++) {
		printf("%7s \ttype: %2d\t attr: %2d\tline: %2d\n", lexeme_map[symbol_table[i]->type], symbol_table[i]->type, symbol_table[i]->attr, symbol_table[i]->line);
		printf("--------------------------------------------------------\n");
	}
}