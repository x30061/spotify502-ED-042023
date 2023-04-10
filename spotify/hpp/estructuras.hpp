#include "datos.hpp"

#ifndef ESTRUCTURAS_HPP
#define ESTRUCTURAS_HPP

Nodo * nodoEn(Nodo *inicio,int posicion);

void insertar(Nodo **inicio,Nodo *nuevo,int posicion);
void insertar(Nodo *nuevo,Nodo *posicion);

void eliminarPorPosicion(Nodo **inicial,int posicion);
void eliminar(Nodo *posicion);

void push(Nodo **inicio,Nodo *nuevo);
void pop(Nodo **inicio);

std::string lista(Nodo *inicial);
int contarNodos(Nodo *inicio);
bool tieneUnNodo(Nodo *inicio);

#endif 