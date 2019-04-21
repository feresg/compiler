// types.h : types used in the compilation process
#ifndef TYPES_H
#define TYPES_H

#define MAX_LENGTH 16
#define NB_TERMINAL 28
#define NB_NON_TERMINAL 17
#define OFFSET 28

enum lexeme {
	PROGRAM, VAR, INTEGER, CHAR, BEGIN, END, IF, THEN, ELSE,
	WHILE, DO, READ, READLN, WRITE, WRITELN, ID, NB, OPEREL,
	OPADD, OPMUL, OPAFF, SEMCOL, PT, DBPT, COMMA, OPP, CLP, DOLLAR // end of program (or $),
};

enum operel {EQ, NE, INF, INF_EQ, SUP, SUP_EQ};
enum opadd {ADD, SUB, OR};
enum opmul {MUL, DIV, MOD, AND};

typedef struct Symbol {
	int type;
	int attr; // for example lexeme operel, value INF_EQ
	int line;
	// if nb, attr is the nb, if id, attr is the index of id in id table
} Symbol;

typedef struct Id {
    int id;
    char* name;
    int type;
    int val;
} Id;

enum non_terminal {
	P = 28, DCL, LISTEID, LISTEID2, TYPE, INSTCOMP, INST,
	LISTEINST, LISTEINST2, I, EXP, EXP2, EXPSIMPLE, EXPSIMPLE2,
	TERME, TERME2, FACTEUR
};

enum derivations {
	P__PROGRAM_ID_SEMCOL_DCL_INSTCOMP_PT = 1,
	DCL__VAR_LISTEID_DBPT_TYPE_SEMCOL_DCL,
	DCL__EPSILON,
	TYPE__INTEGER,
	TYPE__CHAR,
	INSTCOMP__BEGIN_INST_END,
	INST__LISTELIST,
	INST__EPSILON,
	LISTEINST__I_LISTEINST2,
	LISTEINST2__SEMCOL_I_LISTEINST2,
	LISTEINST2__EPSILON,
	LISTEID__ID_LISTEID2,
	LISTEID2__COMMA_ID_LISTEID2,
	LISTEID2__EPSILON,
	I__ID_OPAFF_EXPSIMPLE,
	I__IF_EXP_THEN_I_ELSE_I,
	I__WHILE_EXP_DO_I,
	I__READ_OPP_ID_CLP,
	I__READLN_OPP_ID_CLP,
	I__WRITE_OPP_ID_CLP,
	I__WRITELN_OPP_ID_CLP,
	EXP__EXPSIMPLE_EXP2,
	EXP2__OPEREL_EXPSIMPLE,
	EXP2__EPSILON,
	EXPSIMPLE__TERME_EXPSIMPLE2,
	EXPSIMPLE2__OPADD_TERME_EXPSIMPLE2,
	EXPSIMPLE2__EPSILON,
	TERME__FACTEUR_TERME2,
	TERME2__OPMUL_FACTEUR_TERME2,
	TERME2__EPSILON,
	FACTEUR__ID,
	FACTEUR__NB,
	FACTEUR__OPP_EXPSIMPLE_CLP
};

int parse_table[NB_NON_TERMINAL][NB_TERMINAL];

void init_parse_table() {
	parse_table[P - OFFSET][PROGRAM] = P__PROGRAM_ID_SEMCOL_DCL_INSTCOMP_PT;

	parse_table[DCL - OFFSET][VAR] = DCL__VAR_LISTEID_DBPT_TYPE_SEMCOL_DCL;
	parse_table[DCL - OFFSET][BEGIN] = DCL__EPSILON;

	parse_table[TYPE - OFFSET][INTEGER] = TYPE__INTEGER;
	parse_table[TYPE - OFFSET][CHAR] = TYPE__CHAR;
	
	parse_table[LISTEID - OFFSET][ID] = LISTEID__ID_LISTEID2;

	parse_table[LISTEID2 - OFFSET][DBPT] = LISTEID2__EPSILON;
	parse_table[LISTEID2 - OFFSET][COMMA] = LISTEID2__COMMA_ID_LISTEID2;

	parse_table[INSTCOMP - OFFSET][BEGIN] = INSTCOMP__BEGIN_INST_END;

	parse_table[INST - OFFSET][END] = INST__EPSILON;
	parse_table[INST - OFFSET][IF] = INST__LISTELIST;
	parse_table[INST - OFFSET][WHILE] = INST__LISTELIST;
	parse_table[INST - OFFSET][READ] = INST__LISTELIST;
	parse_table[INST - OFFSET][READLN] = INST__LISTELIST;
	parse_table[INST - OFFSET][WRITE] = INST__LISTELIST;
	parse_table[INST - OFFSET][WRITELN] = INST__LISTELIST;
	parse_table[INST - OFFSET][ID] = INST__LISTELIST;

	parse_table[LISTEINST - OFFSET][IF] = LISTEINST__I_LISTEINST2;
	parse_table[LISTEINST - OFFSET][WHILE] = LISTEINST__I_LISTEINST2;
	parse_table[LISTEINST - OFFSET][READ] = LISTEINST__I_LISTEINST2;
	parse_table[LISTEINST - OFFSET][READLN] = LISTEINST__I_LISTEINST2;
	parse_table[LISTEINST - OFFSET][WRITE] = LISTEINST__I_LISTEINST2;
	parse_table[LISTEINST - OFFSET][WRITELN] = LISTEINST__I_LISTEINST2;
	parse_table[LISTEINST - OFFSET][ID] = LISTEINST__I_LISTEINST2;

	parse_table[LISTEINST2 - OFFSET][END] = LISTEINST2__EPSILON;
	parse_table[LISTEINST2 - OFFSET][SEMCOL] =  LISTEINST2__SEMCOL_I_LISTEINST2;

	parse_table[I - OFFSET][IF] = I__IF_EXP_THEN_I_ELSE_I;
	parse_table[I - OFFSET][WHILE] = I__WHILE_EXP_DO_I;
	parse_table[I - OFFSET][READ] = I__READ_OPP_ID_CLP;
	parse_table[I - OFFSET][READLN] = I__READLN_OPP_ID_CLP;
	parse_table[I - OFFSET][WRITE] = I__WRITE_OPP_ID_CLP;
	parse_table[I - OFFSET][WRITELN] = I__WRITELN_OPP_ID_CLP;
	parse_table[I - OFFSET][ID] = I__ID_OPAFF_EXPSIMPLE;

	parse_table[EXP - OFFSET][ID] = EXP__EXPSIMPLE_EXP2;
	parse_table[EXP - OFFSET][NB] = EXP__EXPSIMPLE_EXP2;
	parse_table[EXP - OFFSET][OPP] = EXP__EXPSIMPLE_EXP2;
	
	parse_table[EXP2 - OFFSET][OPEREL] = EXP2__OPEREL_EXPSIMPLE;
	parse_table[EXP2 - OFFSET][THEN] = EXP2__EPSILON;
	parse_table[EXP2 - OFFSET][DO] = EXP2__EPSILON;

	parse_table[EXPSIMPLE - OFFSET][ID] = EXPSIMPLE__TERME_EXPSIMPLE2;
	parse_table[EXPSIMPLE - OFFSET][NB] = EXPSIMPLE__TERME_EXPSIMPLE2;
	parse_table[EXPSIMPLE - OFFSET][OPP] = EXPSIMPLE__TERME_EXPSIMPLE2;

	parse_table[EXPSIMPLE2 - OFFSET][OPADD] = EXPSIMPLE2__OPADD_TERME_EXPSIMPLE2;
	parse_table[EXPSIMPLE2 - OFFSET][THEN] = EXPSIMPLE2__EPSILON;
	parse_table[EXPSIMPLE2 - OFFSET][ELSE] = EXPSIMPLE2__EPSILON;
	parse_table[EXPSIMPLE2 - OFFSET][DO] = EXPSIMPLE2__EPSILON;
	parse_table[EXPSIMPLE2 - OFFSET][OPEREL] = EXPSIMPLE2__EPSILON;
	parse_table[EXPSIMPLE2 - OFFSET][SEMCOL] = EXPSIMPLE2__EPSILON;
	parse_table[EXPSIMPLE2 - OFFSET][CLP] = EXPSIMPLE2__EPSILON;
	parse_table[EXPSIMPLE2 - OFFSET][END] = EXPSIMPLE2__EPSILON;

	parse_table[TERME - OFFSET][ID] = TERME__FACTEUR_TERME2;
	parse_table[TERME - OFFSET][NB] = TERME__FACTEUR_TERME2;
	parse_table[TERME - OFFSET][OPP] = TERME__FACTEUR_TERME2;
	
	parse_table[TERME2 - OFFSET][OPMUL] = TERME2__OPMUL_FACTEUR_TERME2;
	parse_table[TERME2 - OFFSET][OPADD] = TERME2__EPSILON;
	parse_table[TERME2 - OFFSET][OPEREL] = TERME2__EPSILON;
	parse_table[TERME2 - OFFSET][CLP] = TERME2__EPSILON; 
	parse_table[TERME2 - OFFSET][END] = TERME2__EPSILON;
	parse_table[TERME2 - OFFSET][THEN] = TERME2__EPSILON;
	parse_table[TERME2 - OFFSET][ELSE] = TERME2__EPSILON;
	parse_table[TERME2 - OFFSET][DO] = TERME2__EPSILON;
	parse_table[TERME2 - OFFSET][SEMCOL] = TERME2__EPSILON;

	parse_table[FACTEUR - OFFSET][ID] = FACTEUR__ID;
	parse_table[FACTEUR - OFFSET][NB] = FACTEUR__NB;
	parse_table[FACTEUR - OFFSET][OPP] = FACTEUR__OPP_EXPSIMPLE_CLP;
}

static const char* lexeme_map[] = {
	"program", "var", "integer", "char", "begin", "end", "if", "then", "else",
	"while", "do", "read", "readln", "write", "writeln", "ID", "NB", "OPEREL",
	"OPADD", "OPMUL", ":=", ";", ".", ":", ",", "(", ")", "$", // end of program
	"P", "DCL", "LISTEID", "LISTEID2", "TYPE", "INSTCOMP", "INST",
	"LISTEINST", "LISTEINST2", "I", "EXP", "EXP2", "EXPSIMPLE", "EXPSIMPLE2",
	"TERME", "TERME2", "FACTEUR"
};

static const char* derivations_map[] = {
	"NULL",
	"P -> program id; Dcl Inst_composee .",
	"Dcl -> var Liste_id : Type; Dcl",
	"Dcl -> EPSILON",
	"Type -> integer",
	"Type -> char",
	"Inst_composee -> begin Inst end",
	"Inst -> Liste_Inst",
	"Inst -> EPSILON",
	"Liste_Inst -> I Liste_Inst\'",
	"Liste_Inst\' -> ; I ListeInst\'",
	"Liste_Inst\' -> EPSILON",
	"Liste_Id -> Id Liste_Id\'",
	"Liste_Id\' -> , Id Liste_Id\'",
	"Liste_Id\' -> EPSILON",
	"I -> id := Exp_Simple",
	"I -> if Exp then I else I",
	"I -> while Exp do I",
	"I -> read(id)",
	"I -> readln(id)",
	"I -> write(id)",
	"I -> writeln(id)",
	"Exp -> Exp_Simple Exp\'",
	"Exp\' -> OPEREL Exp_Simple",
	"Exp\' -> EPSILON",
	"Exp_Simple -> Terme Exp_Simple\'",
	"Exp_Simple\' -> OPADD Terme Exp_Simple\'",
	"Exp_Simple\' -> Epsilon",
	"Terme -> Facteur Terme\'",
	"Terme\' -> OPMUL Facteur Terme\'",
	"Terme\' -> EPSILON",
	"Facteur -> id",
	"Facteur -> nb",
	"Facteur -> (Exp_Simple)"
};

#endif



