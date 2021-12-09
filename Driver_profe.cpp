#include "Driver.hpp"
#include <sstream>

Expresion Driver::disyunción(Expresion e1, Expresion e2){
    Expresion e;
    e.tipo = 1; // Depende de la tabla de tipos
    e.dir = nuevaTemporal();
    if(compatibles(e1.tipo, e2.tipo)){
        Cuadrupla c;
        c.arg1 = e1.dir;
        c.arg2 = e2.dir;
        c.resultado = e.dir;
        c.operador = "||";
        codigo_intermedio.push_back(c);
    }else{
        error_semantico("Los tipos de los operandos son incompatibles");
    }
}

bool Driver::compatibles(int t1, int t2){
    std::string nombre = tt.getNombre(t1);
    std::string nombre2 = tt.getNombre(t2);
    if(nombre =="struct" && nombre2=="struct"){
        //Validar la equivalencia de los campos de los tipos
        //estructurados
    }
    if(t1==t2) return true;
    if(t1 ==1 || t2 == 2) return true;
    return false;
    
}

Expresion Expresion::numero(std::string val, int tipo){
    if( tipo == 2){
        stringstream cte;
        cte<<"cteFloat"<<cteFloat++;
        Numero num;
        num.val = val;
        num.tipo = tipo;
        contantes[cte.str()] = num;
    }
}