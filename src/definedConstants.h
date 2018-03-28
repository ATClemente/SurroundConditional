#ifndef DEFINED_CONSTANTS_H
#define DEFINED_CONSTANTS_H

const char* TAB_CHAR = "\t";
const char* NEW_LINE_CHAR = "\n";
const char* CLOSE_BRACE_CHAR = "}";

const char* IF_STATEMENT = "if(true){\n\t";
const int IF_STATEMENT_LEN = 11;

const char* ELSE_IF_STATEMENT = "else if(true){\n\t";
const int ELSE_IF_STATEMENT_LEN = 16;

const char* ELSE_STATEMENT = "else {\n\t";
const int ELSE_STATEMENT_LEN = 8;

const char* WHILE_STATEMENT = "while(true){\n\t";
const int WHILE_STATEMENT_LEN = 14;

const char* FOR_STATEMENT = "for(int i = 0; i < length; i++){\n\t";
const int FOR_STATEMENT_LEN = 34;

const char* DO_WHILE_STATEMENT = "do{\n\t";
const int DO_WHILE_STATEMENT_LEN = 5;

const char* DO_WHILE_END = "}while(true);";
const int DO_WHILE_END_LEN = 13;

const char* SWITCH_STATEMENT = "switch(int){\n\t";
const int SWITCH_STATEMENT_LEN = 14;

#endif // !DEFINED_CONSTANTS_H