#ifndef __SCANNER_H_
#define __SCANNER_H_
#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

namespace C_3
{
    class Scanner : public yyFlexLexer{
        public:
            Scanner(std::istream * in): yyFlexLexer(in)
            {
            };

            using FlexLexer::yylex;
            virtual int yylex();
        private:
            const int ERROR= -1;
            const int ACEPTAR = 0;
            const int CHAR = 1;
            const int INT = 2;
            const int FLOAT = 3;
            const int DOUBLE = 4;
            const int STRUCT = 5;
            const int VOID = 6;
            const int IF = 7;
            const int ELSE = 8;
            const int WHILE = 9;
            const int DO = 10;
            const int PRINT = 11;
            const int SCAN = 12;
            const int BREAK = 13;
            const int RETURN = 14;
            const int ID = 15;
            const int PYC = 16;
            const int COMA = 17;
            const int PUNTO = 18;
            const int LPAR = 19;
            const int RPAR = 20;
            const int LLLAVE = 21;
            const int RLLAVE = 22;
            const int MAS = 23;
            const int MENOS = 24;
            const int MUL = 25;
            const int DIV = 26;
            const int ASIG = 27;
            const int AND = 28;
            const int OR = 29;
            const int NOT = 30;
            const int MENOR = 31;
            const int MAYOR = 32;
            const int IGUAL = 33;
            const int NOIGUAL = 34;
            const int MAYORIGUAL = 35;
            const int MENORIGUAL = 36;
            const int ENTERO = 37;
            const int FLOTANTE = 38;
            const int CADENA = 39;
            const int CARACTER = 40;
            const int ESP = 41;
    };
}

#endif