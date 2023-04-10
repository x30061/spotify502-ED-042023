#include "tinyxml2.h"
#include <iostream>
#include <string>

#ifndef IMPORTAR_HPP
#define IMPORTAR_HPP

extern tinyxml2::XMLDocument doc;
void cargarNuevoXML(std::string path);
void elementoInsertar_lectura1();
void elementoInsertar_lectura2();
void elementoEliminar_lectura1();
void elementoEliminar_lectura2();
void elementoEliminar_lectura3();

#endif 