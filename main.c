#include <stdio.h>
#include "lexer.h"
#include "parser.h"
#include "types.h"
	
int main(int argc, char **argv) {
	if (argc == 0) {
		printf("error: no source file provided");
		printf("usage: ./compile source");
		exit(0);
	}
	
	// lexical analysis
	source = fopen(argv[1], "r");
	printf("***********************\nLexical Analysis Start!\n***********************\n");
	next_symbol();
	fclose(source);
	printf("\n############\nSymbol Table\n############\n\n");
	print_symbols();
	printf("\n########\nID Table\n########\n\n");
	print_ids();
	init_parse_table();
	printf("\n****************************\nLexical Analysis Successful!\n****************************\n\n");

	printf("**********************\nSyntax Analysis Start!\n**********************\n\n");
	parse();
	printf("***************************\nSyntax Analysis Successful!\n***************************\n\n");
	return 0;

}