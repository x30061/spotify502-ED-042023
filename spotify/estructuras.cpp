#include "hpp/estructuras.hpp"

// <!> puede devolver un nodo NULL por ser el primero en la lista o por no estar en la lista
Nodo * nodoEn(Nodo *inicio,int posicion)
{
    Nodo *aux = inicio;

    if ((aux == NULL) | (posicion == 0)) { return NULL; }

    // devolver el ultimo nodo de la lista 
    if (posicion == -1)
    {
        while (aux->der != NULL)
        {
            aux = aux->der;
        }
        return aux;
    }
    if (posicion == 1) { return aux; }
    
    int i = 1;
    while (i != posicion)
    {
        if (aux == NULL) { return NULL; }
        
        aux = aux->der;
        i = i + 1;
    }
    return aux;
}

/* PRINCIPAL: a prueba de NULL*/
void insertar(Nodo **inicio,Nodo *nuevo,int posicion)
{
    if (posicion == 0) { return; }
    Nodo *aux = *inicio;
    if (nuevo == NULL){}
    else if ((aux == NULL) & ((posicion == 1)|(posicion == -1))) { *inicio = nuevo; }
    else if (aux == NULL) { }
    else if (posicion == 1) 
    { 
        *inicio = nuevo; 
        insertar(nuevo,aux);
    }
    else if(posicion == -1)
    {
        aux = nodoEn(aux,posicion);

        aux->der = nuevo;
        nuevo->izq = aux;

        //if (aux != NULL){}
    }
    else
    { 
        insertar(nuevo,nodoEn(aux,posicion)); 
    }
}

/* insertar un nodo nuevo justo antes de un nodo en una posicion especifica 
<?> si algun nodo es NULL entonces no se ejecuta la operacion*/
void insertar(Nodo *nuevo,Nodo *posicion)
{
    if ((nuevo == NULL) | (posicion == NULL)){ return; }
    
    if (posicion->izq != NULL)
    {
        nuevo->izq = posicion->izq;
        posicion->izq->der = nuevo;
    }
    posicion->izq = nuevo;
    nuevo->der = posicion;
}

/* PRINCIPAL: a prueba de NULL*/
void eliminarPorPosicion(Nodo **inicial,int posicion)
{
    if ((inicial == NULL) | (posicion == 0)) { return; }

    Nodo *aux = *inicial;
    if (aux == NULL) { return; }
    
    if ((posicion == 1) | ((posicion == -1) & tieneUnNodo(aux))) 
    {
        *inicial = aux->der;
        eliminar(aux);
        return;
    }

    Nodo *pos = nodoEn(aux,posicion);
    if (pos == NULL) { return; }
    eliminar(pos);
}

// a prueba de NULL
void eliminar(Nodo *posicion)
{
    if (posicion == NULL) { }
    else if ((posicion->izq == NULL) & (posicion->der == NULL)) { }
    else if ((posicion->izq != NULL) & (posicion->der != NULL))
    {
        posicion->izq->der = posicion->der;
        posicion->der->izq = posicion->izq;
    }
    else if(posicion->izq == NULL)
    {
        posicion->der->izq = NULL;
    }
    else if(posicion->der == NULL)
    {
        posicion->izq->der = NULL;
    }
    posicion = NULL;
    delete posicion;
}

std::string lista(Nodo *inicial)
{
    Nodo *aux = inicial;
    std::string l = ""; 

    while (aux != NULL)
    {
        l.append(aux->getDatos() + " ");
        aux = aux->der;
    }
    return l;
}

void push(Nodo **inicio,Nodo *nuevo)
{
    insertar(inicio,nuevo,-1);
}

void pop(Nodo **inicio)
{
    eliminarPorPosicion(inicio,-1);
}

int contarNodos(Nodo *inicio)
{
    Nodo *aux = inicio;
    int l = 1; 

    while (aux->der != NULL)
    {
        l = l + 1;
        aux = aux->der;
    }
    return l;
}

bool tieneUnNodo(Nodo *inicio)
{
    if (inicio->der == NULL) { return true; }
    return false;
}
