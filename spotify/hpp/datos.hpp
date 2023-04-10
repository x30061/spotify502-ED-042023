#include "herramientas.hpp"

#ifndef DATOS_HPP
#define DATOS_HPP

enum Modo
{
    SONG,PLIST,PLAY,STOP,PREV,NEXT,NORMAL,BUCLE
};

class Dato
{
    private:
    Modo mod;
    std::string name;
    std::string ext;

    public:
    //Dato();
    Dato(Modo mod,std::string name,std::string ext);
    ~Dato();
    std::string getName();
    std::string getExt();
    void setDatos(std::string name,std::string ext);
    std::string getDatos();
    void printDatos();
    std::string getInfo();
    Modo getModo();
};

class Nodo
{
    private:
    Dato *dat;

    public:
    Nodo *izq;
    Nodo *der;
    Nodo *cen;
    Nodo(Dato *dat);
    ~Nodo();
    Dato * getDato();
    std::string getDatos();
    std::string getInfo();
    Nodo *getCopia();
};

#endif 