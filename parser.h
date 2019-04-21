// parser.h : performs syntax analysis on a source code file, ll1 predictive recursive
#ifndef PARSER_H
#define PARSER_H

#include <string.h>

#include "stack.h"

#define MAX_STACK_SIZE 100

struct Stack* ps;
int sym_index = 0;
int symbol;
char err_line[2];

void parse() {
	ps = create_stack(MAX_STACK_SIZE);
	push(ps, DOLLAR);
	push(ps, P);

	while(!(is_empty(ps)) && (sym_index < symbol_table_size)) {
		symbol = symbol_table[sym_index]->type;
		printf("Stack top: %s\tCurrent symbol: %s\n", lexeme_map[top(ps)], lexeme_map[symbol]);
		if(symbol == top(ps)) { // stack contains current terminal symbol
			printf("Matched symbols: %s\n", lexeme_map[symbol]);
			sym_index++;
			pop(ps);
		} else {
			if((top(ps)) < P) {
				fatal_error("syntax error", "terminal symbols dont match");
			}
			// printf("%d\n", parse_table[top(ps) - OFFSET][symbol]);
			printf("Rule: %s\n", derivations_map[parse_table[top(ps) - OFFSET][symbol]]);
			switch(parse_table[top(ps) - OFFSET][symbol]) {
				
				case P__PROGRAM_ID_SEMCOL_DCL_INSTCOMP_PT:
					pop(ps);
					push(ps, PT); push(ps, INSTCOMP); push(ps, DCL); push(ps, SEMCOL); push(ps, ID); push(ps, PROGRAM);
					break;
				
				case DCL__VAR_LISTEID_DBPT_TYPE_SEMCOL_DCL:
					pop(ps);
					push(ps, DCL); push(ps, SEMCOL); push(ps, TYPE); push(ps, DBPT); push(ps, LISTEID); push(ps, VAR);
					break;
				
				case DCL__EPSILON:
					pop(ps);
					break;
				
				case TYPE__INTEGER:
					pop(ps);
					push(ps, INTEGER);
					break;
				
				case TYPE__CHAR:
					pop(ps);
					push(ps, CHAR);
					break;
				
				case INSTCOMP__BEGIN_INST_END:
					pop(ps);
					push(ps, END); push(ps, INST); push(ps, BEGIN);
					break;
				
				case INST__LISTELIST:
					pop(ps);
					push(ps, LISTEINST);
					break;
				
				case INST__EPSILON:
					pop(ps);
					break;
				
				case LISTEINST__I_LISTEINST2:
					pop(ps);
					push(ps, LISTEINST2); push(ps, I);
					break;
				
				case LISTEINST2__SEMCOL_I_LISTEINST2:
					pop(ps);
					push(ps, LISTEINST2); push(ps, I); push(ps, SEMCOL);
					break;
				
				case LISTEINST2__EPSILON:
					pop(ps);
					break;
				
				case LISTEID__ID_LISTEID2:
					pop(ps);
					push(ps, LISTEID2); push(ps, ID);
					break;
				
				case LISTEID2__COMMA_ID_LISTEID2:
					pop(ps);
					push(ps, LISTEID2); push(ps, ID); push(ps, COMMA);
					break;
				
				case LISTEID2__EPSILON:
					pop(ps);
					break;
				
				case I__ID_OPAFF_EXPSIMPLE:
					pop(ps);
					push(ps, EXPSIMPLE); push(ps, OPAFF); push(ps, ID);
					break;
				
				case I__IF_EXP_THEN_I_ELSE_I:
					pop(ps);
					push(ps, I); push(ps, ELSE); push(ps, I); push(ps, THEN); push(ps, EXP); push(ps, IF);
					break;
				
				case I__WHILE_EXP_DO_I:
					pop(ps);
					push(ps, I); push(ps, DO); push(ps, EXP); push(ps, WHILE);
					break;
				
				case I__READ_OPP_ID_CLP:
					pop(ps);
					push(ps, CLP); push(ps, ID); push(ps, OPP); push(ps, READ);
					break;
				
				case I__READLN_OPP_ID_CLP:
					pop(ps);
					push(ps, CLP); push(ps, ID); push(ps, OPP); push(ps, READLN);
					break;
				
				case I__WRITE_OPP_ID_CLP:
					pop(ps);
					push(ps, CLP); push(ps, ID); push(ps, OPP); push(ps, WRITE);
					break;
				
				case I__WRITELN_OPP_ID_CLP:
					pop(ps);
					push(ps, CLP); push(ps, ID); push(ps, OPP); push(ps, WRITELN);
					break;
				
				case EXP__EXPSIMPLE_EXP2:
					pop(ps);
					push(ps, EXP2); push(ps, EXPSIMPLE);
					break;
				
				case EXP2__OPEREL_EXPSIMPLE:
					pop(ps);
					push(ps, EXPSIMPLE); push(ps, OPEREL);
					break;
				
				case EXP2__EPSILON:
					pop(ps);
					break;
				
				case EXPSIMPLE__TERME_EXPSIMPLE2:
					pop(ps);
					push(ps, EXPSIMPLE2); push(ps, TERME);
					break;
				
				case EXPSIMPLE2__OPADD_TERME_EXPSIMPLE2:
					pop(ps);
					push(ps, EXPSIMPLE2); push(ps, TERME); push(ps, OPADD);
					break;
				
				case EXPSIMPLE2__EPSILON:
					pop(ps);
					break;
				
				case TERME__FACTEUR_TERME2:
					pop(ps);
					push(ps, TERME2); push(ps, FACTEUR);
					break;
				
				case TERME2__OPMUL_FACTEUR_TERME2:
					pop(ps);
					push(ps, TERME2); push(ps, FACTEUR); push(ps, OPMUL);
					break;
				
				case TERME2__EPSILON:
					pop(ps);
					break;
				
				case FACTEUR__ID:
					pop(ps);
					push(ps, ID);
					break;
				
				case FACTEUR__NB:
					pop(ps);
					push(ps, NB);
					break;
				
				case FACTEUR__OPP_EXPSIMPLE_CLP:
					pop(ps);
					push(ps, CLP); push(ps, EXPSIMPLE); push(ps, OPP);
					break;			
				
				default:
					fatal_error_at_line("syntax error", "an error occured", symbol_table[sym_index]->line);
					break;
			}
		}
		printf("--------------------------------------------------\n");
	}
	printf("\n");
}

#endif
