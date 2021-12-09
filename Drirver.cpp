#include "Driver.hpp"
#include <sstream>

Expresion Driver::opBinaria(Expresion e1, Expresion e2,std::string operador){
    Expresion e;
    e.tipo = 1;
    e.dir = nuevaTemporal();
    if(compatibles(e1.tipo, e2.tipo)){
        Cuadrupla c;
        c.arg1 = e1.dir;
        c.arg2 = e2.dir;
        c.resultado = e.dir;
        c.operador = operador;
        codigo_intermedio.push_back(c);
    }else{
        error_semantico("Los tipos de los operandos son incompatibles");
    }
}

Expresion Driver::disyuncion(Expresion e1, Expresion e2){
    opBinaria(e1, e2, "||");
}

Expresion Driver::conjuncion(Expresion e1, Expresion e2){
    opBinaria(e1,e2,"&&");
}

Expresion Driver::igual(Expresion e1, Expresion e2){
    opBinaria(e1,e2,"==");
}

Expresion Driver::menor_que(Expresion e1, Expresion e2){
    opBinaria(e1,e2,"<");
}

Expresion Driver::mayor_que(Expresion e1, Expresion e2){
    opBinaria(e1,e2,">");
}

Expresion Driver::menor_o_igual(Expresion e1, Expresion e2){
    opBinaria(e1,e2,"<=");
}

Expresion Driver::mayor_o_igual(Expresion e1, Expresion e2){
    opBinaria(e1,e2,"<=");
}

Expresion Driver::distinto(Expresion e1, Expresion e2){
    opBinaria(e1,e2,"!=");
}

Expresion Driver::suma(Expresion e1, Expresion e2){
    opBinaria(e1,e2,"+");
}

Expresion Driver::resta(Expresion e1, Expresion e2){
    opBinaria(e1,e2,"-");
}

Expresion Driver::mul(Expresion e1, Expresion e2){
    opBinaria(e1,e2,"*");
}

Expresion Driver::division(Expresion e1, Expresion e2){
    opBinaria(e1,e2,"/");
}

Expresion Driver::negacion(Expresion e1){
    Expresion e;
    e.tipo = 1;
    e.dir = nuevaTemporal();
    Cuadrupla c;
    c.arg1 = e1.dir;
    c.arg2 = "";
    c.resultado = e.dir;
    c.operador = '!';
    codigo_intermedio.push_back(c);
}

void Driver::asignacion(std::string id, Expresion e){
    int intId = stoi(id);
    //en caso de no ser funcion ni estructura
    if(ts.back().find(intId)){
        if(ts.back().getTipo(intId) == e.tipo){
            //Pasar dir de e a id.
        }else {
            error_semantico("Tipos incompatibles");
        }
    }else{
        error_semantico("Id no ha sido definido");
    }
}

bool Driver::compatibles(int t1, int t2){
    std::string nombre = tt.getNombre(t1);
    std::string nombre2 = tt.getNombre(t2);
    if(nombre == "struct" && nombre2 == "struct"){
        //Validar la equivalencia de los campos de los tipos
        //estructurados
        //Tablas de símbolos de los tipos estructurados se puede usar
        //No tiene siempre mismo orden
    }
    if(t1 == t2) return true;
    if(t1 == 1 || t2 == 2) return true;
    return false;
}

Expresion Driver::numero(std::string val, int tipo){
    //float
    if(tipo == 2){
        std::stringstream cte;
        cte << "cteFloat" << cteFloat++;
        Numero num;
        num.val = val;
        num.tipo = 2;
        constantes[cte.str()] = num;
    }else if(tipo == 3){ //double
        std::stringstream cte;
        cte << "cteFloat" << cteFloat++;
        Numero num;
        num.val = val;
        num.tipo = 3;
        constantes[cte.str()] = num;
    }else{
        Numero num;
        num.val = val;
        num.tipo = 1;
        
    }

}

std::string Driver::ampliar(std::string dir, int t1, int t2){
    int max = maximo(t1, t2);
    int tipo = tt.getTam(max);
    if(ts.back().find(dir)){
        int id = ts.back().getId(dir);
        return ts.back().cambioTipo(id,tipo);
    }
}

std::string Driver::reducir(std::string dir, int t1, int t2){
    int min = minimo(t1, t2);
    int tipo = tt.getTam(min);
    if(ts.back().find(dir)){
        int id = ts.back().getId(dir);
        return ts.back().cambioTipo(id,tipo);
    }
}

std::string reducir(std::string dir, int t1, int t2){

}

int Driver::maximo(int t1, int t2){
    int val1 = tt.getTam(t1);
    int val2 = tt.getTam(t2);
    return val1 < val2 ? val2 : val1;
}

int Driver::minimo(int t1, int t2){
    int val1 = tt.getTam(t1);
    int val2 = tt.getTam(t2);
    return val1 > val2 ? val2 : val1;
}

void Driver::gen_if(std::string val){
    std::string sig=nuevaEtiqueta();
    gen_label(sig);
    std::string verdadero = nuevaEtiqueta();
    std::string falso = nuevaEtiqueta();
    genIf(val,this->pilaDir.top(),verdadero);
    gen_goto(falso);
    gen_goto(verdadero);
    gen_goto(this->pilaEtiquetas.top());
    gen_label(verdadero);
}

void Driver::gen_label(std::string label){
    this->pilaEtiquetas.push(label);
}

std::string Driver::nuevaEtiqueta(){
    std::string nuevaString = "";
    return nuevaString;
}