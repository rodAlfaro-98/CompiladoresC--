%{
    #include <iostream>
    #include <string>
    using namespace std;

    #include "tokens.hpp"
    #include "Scanner.hpp"
    #undef YYDECL
%}

%option c++
%option outfile = "Scanner.cpp"
%option yyclass="C_3::Scanner"
%option case-insensitive
%option noyywrap

DIG [0-9]
ESP [ \t\n\r]
ENTERO [0-9][0-9]*
FLOTANTE [0-9]*[.][0-9]+([Ee]([+-])?([0-9])+)?
ID [A-Za-z][A-Za-z0-9_]*
CADENA \"[a-zA-Z0-9_ ]*[\n\t\r]?\"
CARACTER ['][a-zA-Z0-9_\n\t\r][']
%%

"+" {return MAS;}
"-" {return MENOS;}
"*" {return MUL;}
"/" {return DIV;}
"=" {return ASIG;}
"(" {return LPAR;}
")" {return RPAR;}
"{" {return LLLAVE;}
"}" {return RLLAVE;}
"," {return COMA;}
";" {return PYC;}
"&&" {return AND;}
"||" {return OR;}
"!"  {return NOT;}
"==" {return IGUAL;}
"!=" {return NOIGUAL;}
"<"  {return MENOR;}
">"  {return MAYOR;}
"<=" {return MENORIGUAL;}
">=" {return MAYORIGUAL;}

"if"        {return IF;}
"else"      {return ELSE;}
"int"       {return INT;}
"while"     {return WHILE;}
"float"     {return FLOAT;}
"char"       {return CHAR;}
"double"    {return DOUBLE;}
"struct"    {return STRUCT;}
"void"      {return VOID;}
"do"        {return DO;}
"print"     {return PRINT;}
"break"     {return BREAK;}
"return"    {return RETURN;}
{ENTERO}    {return ENTERO;}
{FLOTANTE}  {return FLOTANTE;}
{CADENA}    {return CADENA;}
{CARACTER}  {return CARACTER;}
{ID}        {return ID;}
{ESP}       {return ESP;}

. { cout << "ERROR LEXICO "<<yytext<<endl;}
%%