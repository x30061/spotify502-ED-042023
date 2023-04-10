#include "hpp/herramientas.hpp"

void imprimir(std::string cadena)
{
    std::cout << cadena;
}
std::string getTitulo(std::string t)
{
    return "<<<<<<<<<<<< " + t + " >>>>>>>>>>>>";
}
std::string getSubTitulo(std::string t)
{
    return "<----- " + t + " ----->";
}
