#ifndef __DRIVER_HPP__
#define __DRIVER_HPP__
#include <string>
#include <map>
#include <stack>
#include <vector>
#include <sstream>

struct Cuadrupla{
    std::string arg1, arg2;
    std::string operador;
    std::string resultado;
};

struct Expresion{
    std::string dir;
    int tipo;
};

struct Sym{
    int id;
    int dir;
    int tipo;
    std::string categoria;
    std::vector<Expresion> argumentos;
};

class SymTab{
    private:
        std::map<int,Sym> tablaSim;
    public:
        void agregar_simbolo(int id, int dir, int tipo, std::string categoria){
            Sym temp;
            temp.id = id;
            temp.dir = dir;
            temp.tipo = tipo;
            temp.categoria = categoria;
            temp.argumentos = std::vector<Expresion>();
            tablaSim[id] = temp;
        }

        bool find(int id){
            return (tablaSim.find(id) != tablaSim.end()) ? true : false;    
        }

        bool find(std::string dir){
            int intDir = stoi(dir);
            for(const auto& kv: tablaSim){
                if(kv.second.dir == intDir){
                    return true;
                }
            }
            return false;
        }

        int getTipo(int id){
            return find(id) ? tablaSim[id].tipo: -1;
        }

        std::string cambioTipo(int id, int tipo){
            if (find(id)){
                tablaSim.erase(id);
                int maxDir = 0;
                int maxTipo = 0;
                int ultimoId = 0;
                for(const auto& kv: tablaSim){
                    if(kv.second.dir > maxDir){
                        maxDir = kv.second.dir;
                        maxTipo = kv.second.tipo;
                        ultimoId = kv.second.tipo;
                    }
                    
                }
                int nuevaDir = maxDir + maxTipo;
                agregar_simbolo(ultimoId++,nuevaDir,tipo,"variable");

                return std::to_string(nuevaDir);
            }

            return "";
        }

        int getId(std::string dir){
            int intDir = stoi(dir);
            for(const auto& kv: tablaSim){
                if(kv.second.dir == intDir){
                    return kv.first;
                }
            }
            return -1;
        }
}; //Id, Dir, Tipo, Categoria, Argumentos  //Andy si quieres ser un heroe define esto <3

class TypeTab{
    private: 
        int contStruct = 4;
        std::map<int,std::string> tt;
        std::map<int,SymTab> tStruct;
        std::map<std::string,int> tNombreStruct;
    public:
        TypeTab(){
            tt[0]="void";
            tt[1]="int";
            tt[2]="flaot";
            tt[3]="double";
            tt[4]="struct";
        }
        std::string getNombre(int t){
            if(t >=4){
                return "struct";
            }
            return this->tt[t];
        }
        //Ahorita está incompleta
        int getTam(int t){
            if(getNombre(t) == "struct"){
                if(tStruct.find(t) != tStruct.end()){
                    int tamTotal = 0;
                    SymTab tTemp = tStruct[t];
                     //SUMAR  
                }else{
                    //mostrar error
                }
            }else{
                return tamTipo(t);
            }
        }

        int tamTipo(int t){
            switch(t){
                case 0:
                    return 0;
                case 1:
                    return 4;
                case 2:
                    return 8;
                case 3:
                    return 8;
                }
        }

        void agregarTipo(std::string nombre,SymTab symTab){
            contStruct++;
            tNombreStruct[nombre] = contStruct;
            tStruct[contStruct] = symTab;
        }
};

struct Numero{
    std::string val;
    int tipo;
};

class Driver
{
    private:
        //TypeTab tt;
        TypeTab tt;
        //Pila de tablas de simbolos (vector)
        std::vector<SymTab> ts;
        //Pila para las etiquetas
        std::stack<std::string> pilaEtiquetas;
        //Pila para las Direcciones
        std::stack<int> pilaDir;
        //Pila para las variables temporales
        std::stack<int> pilaTemporal;
        std::map<std::string, std::string> tstring;
        std::map<std::string, Numero>constantes;
        int retorno;
        bool tieneRetorno;
        int dir;
        int etiquetas;
        int cteFloat;
        std::vector<Cuadrupla> codigo_intermedio;
        //Generador de codigo final
    public:
        Driver();
        ~Driver();
        //Funciones para tabla de tipos
        int agregar_tipo(int tam_bytes, SymTab *tipo_base,std::string nombre);

        void agregar_simbolo(std::string id, int tipo, std::string categoria);
        //El vector es una referencia para la tabla de tipos
        void agregar_simbolo(std::string id, int tipo, std::vector<int> args);

        std::string nuevaEtiqueta();
        std::string nuevaTemporal();


        void asignacion(std::string id, Expresion e);
        Expresion disyuncion(Expresion e1, Expresion e2);
        Expresion conjuncion(Expresion e1, Expresion e2);
        Expresion igual(Expresion e1, Expresion e2);
        Expresion distinto(Expresion e1, Expresion e2);
        Expresion mayor_que(Expresion e1, Expresion e2);
        Expresion menor_que(Expresion e1, Expresion e2);
        Expresion mayor_o_igual(Expresion e1, Expresion e2);
        Expresion menor_o_igual(Expresion e1, Expresion e2);
        Expresion suma(Expresion e1, Expresion e2);
        Expresion resta(Expresion e1, Expresion e2);
        Expresion mul(Expresion e1, Expresion e2);
        Expresion division(Expresion e1, Expresion e2);
        Expresion opBinaria(Expresion e1, Expresion e2,std::string operador);
        
        Expresion negacion(Expresion e1);
        Expresion identificador(std::string id);
        Expresion numero(std::string val, int tipo);

        std::string ampliar(std::string dir, int t1, int t2);
        std::string reducir(std::string dir, int t1, int t2);
        int maximo(int t1, int t2);
        int minimo(int t1, int t2);
        bool compatibles(int t1, int t2);

        void error_semantico(std::string mensaje);
        void gen_imprimir(std::string val);
        void gen_lectura(std::string dir);
        void gen_label(std::string val);
        void gen_goto(std::string val);
        void gen_if(std::string val);
        void genIf(std::string condicion, int dir, std::string verdadero);

};

#endif