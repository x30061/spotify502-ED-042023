#include "hpp/datos.hpp"

// >>>>>>>>>>>>> NODO >>>>>>>>>>>>>

Nodo::Nodo(Dato *dat)
{
    this->dat = dat;
    this->izq = NULL;
    this->der = NULL;
    this->cen = NULL;
}

Nodo::~Nodo()
{
    der = NULL;
    izq = NULL;
    cen = NULL;
    delete dat;
}

std::string Nodo::getDatos()
{
    if (dat != NULL){ return dat->getDatos(); }
    return NULL;
}

Dato * Nodo::getDato()
{
    return dat;
}

std::string Nodo::getInfo()
{
    return dat->getInfo();
}

Nodo * Nodo::getCopia()
{
    std::string name = dat->getName();
    std::string ext = dat->getExt();
    Modo m = dat->getModo();
    return new Nodo(new Dato(m,name,ext));
}


// >>>>>>>>>>>>> DATO >>>>>>>>>>>>>

Dato::Dato(Modo mod,std::string name,std::string ext)
{
    this->mod = mod;
    this->name = name;
    this->ext = ext;
}

Dato::~Dato()
{
    name = "";
    ext = "";
}
std::string Dato::getName()
{
    return name;
}

std::string Dato::getExt()
{
    return ext;
}
Modo Dato::getModo()
{
    return mod;
}

void Dato::setDatos(std::string name,std::string ext)
{
    this->name = name;
    this->ext = ext;
}

std::string Dato::getInfo()
{
    std::string i = "";
    if (mod == PLIST)
    {
        i = name + " - " + ext;
    }
    else
    {
        i = name + " - \"" + ext + "\"";
    }
    return i;
}

std::string Dato::getDatos()
{
    std::string d = "{" + this->name + "," + this->ext+"}";
    return d;
}

void Dato::printDatos()
{
    std::cout << getDatos();
}



