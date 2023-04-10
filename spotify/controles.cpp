#include "hpp/controles.hpp"
#include "hpp/estructuras.hpp"
#include "hpp/herramientas.hpp"
#include "hpp/importar-xml.hpp"

Nodo *nodo_now = NULL;
Dato *dato_store = new Dato(PLIST,"STORE","playlist que contiene todas las canciones");
Nodo *nodo_store = new Nodo(dato_store);

Nodo *song1_proximas = NULL;
Nodo *song_now = NULL;

Modo modo_repr = NORMAL;

void importarAjustes()
{
    imprimir(getTitulo("IMPORTAR AJUSTES") + "\n");
    std::string path;
    imprimir("path del archivo de ajustes: ");
    std::cin.ignore();
    std::getline(std::cin, path);
    imprimir("path: " + path + "\n");
    cargarNuevoXML(path);
}

// necesario en "reproductor" y en "abrir playlist"
void seleccionarPlaylist()
{
    
    imprimir(getLista(nodo_store));
    int i = -2;
    imprimir("seleccione una playlist: ");
    std::cin >> i;
    nodo_now = nodoEn(nodo_store,i);
    if (nodo_now != NULL)
    {
        imprimir("<?> selecccionado: " + nodo_now->getInfo() + "\n");
    }
    else 
    {
        imprimir("<!> playlist no encontrada\n");
    }
}

void modoReproduccion()
{
    imprimir("normal = 0, repetitivo = 1: ");
    int i = 0;
    std::cin >> i;
    if (i == 1) { modo_repr = BUCLE; }
    else { modo_repr = NORMAL; }
}

void initReproductor()
{
    song_now = nodo_now->cen;
}

std::string getCancionActual()
{
    if (song1_proximas != NULL) { return "<?> " + nodoEn(song1_proximas,-1)->getInfo(); }
    if (song_now != NULL) { return "<?> " + song_now->getInfo(); }
    return "<?> reproduccion finalizada";
}

void nextSong()
{
    if (song1_proximas != NULL) { pop(&song1_proximas); return; }
    if (song_now == NULL) { return; }

    if ((song_now->der == NULL) & (modo_repr == BUCLE))
    {
        song_now = nodo_now->cen;
    }
    else { song_now = song_now->der; }
}

void prevSong()
{
    if (song1_proximas != NULL) { return; }
    
    if (song_now == NULL) { return; }

    if ((song_now->izq == NULL) & (modo_repr == BUCLE))
    {
        song_now = nodoEn(nodo_now->cen,-1);
    }
    else { song_now = song_now->izq; }
}

void play()
{
    std::string path;

    if (song1_proximas != NULL)
    {
        path = nodoEn(song1_proximas,-1)->getDato()->getExt();
    }
    else if (song_now != NULL)
    {
        path = song_now->getDato()->getExt();
    } 
    else { return; }

    std::string cmd = "mpv --window-minimized=yes --audio-display=no \"" + path + "\"";
    imprimir(cmd + "\n");
    system(cmd.c_str());
}

void insertarPlaylistManual(Nodo **plist)
{
    std::string name;
    std::string desc;
    imprimir("nombre: ");
    std::cin.ignore();
    std::getline(std::cin, name);
    imprimir("descripcion: ");
    //std::cin.ignore();
    std::getline(std::cin, desc);
    Dato *song = new Dato(PLIST,name,desc);
    Nodo *nuevo = new Nodo(song);
    insertar(plist,nuevo,-1);
}
void eliminarPlaylistManual(Nodo **plist)
{
    int i = -2;
    imprimir("posicion de playlist a eliminar: ");
    std::cin >> i;
    if (i == 1)
    {
        imprimir("<!> no puede eliminar la STORE\n");
        return;
    }
    eliminarPorPosicion(plist,i);
}

void insertarCancionManual(Nodo **plist)
{
    std::string name;
    std::string path;
    imprimir("nombre: ");
    std::cin.ignore();
    std::getline(std::cin, name);
    imprimir("path: ");
    //std::cin.ignore();
    std::getline(std::cin, path);
    Dato *song = new Dato(SONG,name,path);
    Nodo *nuevo = new Nodo(song);
    insertar(plist,nuevo,-1);
}

void eliminarCancionManual(Nodo **plist)
{
    int i = -2;
    imprimir("posicion de cancion a eliminar: ");
    std::cin >> i;
    eliminarPorPosicion(plist,i);
}

std::string getProximas()
{
    Nodo *aux = nodoEn(song1_proximas,-1);
    std::string l = ""; 

    while (aux != NULL)
    {
        l.append(" " + aux->getInfo() + "\n");
        aux = aux->izq;
    }
    aux = nodo_now->cen;
    while (aux != NULL)
    {
        l.append(" " + aux->getInfo() + "\n");
        aux = aux->der;
    }
    return l;
}

std::string getLista(Nodo *init)
{
    Nodo *aux = init;
    int i = 1;
    std::string l = ""; 

    while (aux != NULL)
    {
        l.append(std::to_string(i) + ". " + aux->getInfo() + "\n");
        aux = aux->der;
        i = i + 1;
    }

    return l;
}


void insertarProximas()
{
    imprimir(getLista(nodo_store->cen));
    imprimir("posicion de cancion a agregar: ");
    int i = -2;
    std::cin >> i; 
    Nodo *aux = nodoEn(nodo_store->cen,i);
    
    if (aux != NULL)
    {
        Nodo *aux_copy = aux->getCopia();
        push(&song1_proximas,aux_copy);
    }
    else 
    {
        imprimir("<!> cancion no encontrada\n");
    }
}

Nodo * nodoPorNombre(Nodo *inicio,std::string name)
{
    Nodo *aux = inicio;

    if (aux == NULL) { return aux; }

    std::string aux_name;
    while (aux != NULL)
    {
        aux_name = aux->getDato()->getName();
        int res = name.compare(aux_name);
        if (res == 0){ break; }
        aux = aux->der;
    }
    
    return aux;
}
void eliminarPorNombre(Nodo **inicial,std::string name)
{
    if (*inicial == NULL) { return; }

    Nodo *buscado = nodoPorNombre(*inicial,name);
    if (buscado == NULL) { return; }

    if(buscado == *inicial) { *inicial = (*inicial)->der; }

    eliminar(buscado);
}

int posicionPorNombre(Nodo *inicio,std::string name)
{
    Nodo *aux = inicio;

    if (aux == NULL) { return 0; }

    int i = 0;
    std::string aux_name;
    while (aux != NULL)
    {
        i = i + 1;
        aux_name = aux->getDato()->getName();
        int res = name.compare(aux_name);
        if (res == 0) { return i; }
        aux = aux->der;
    }
    if (aux == NULL) { return 0; }
    return 0;
}


// A PRUEBA DE ERRORES
void buscarCancion()
{
    std::string name;
    imprimir("nombre: ");
    std::cin.ignore();
    std::getline(std::cin, name);
    int i = posicionPorNombre(nodo_store->cen,name);
    if (i != 0)
    {
        Nodo *aux = nodoEn(nodo_store->cen,i);
        std::string m = "<?> se encontro: " + std::to_string(i) + ". " + aux->getInfo() + "\n";
        imprimir(m);
    }
    else 
    {
        imprimir("<!> cancion no encontrada\n");
    }
}

void actualizarPlaylist()
{
    if(nodo_now == NULL) { return; }

    std::string name;
    std::string desc;
    imprimir("nombre: ");
    std::cin.ignore();
    std::getline(std::cin, name);
    imprimir("descripcion: ");
    //std::cin.ignore();
    std::getline(std::cin, desc);

    if (name.empty()) { name = nodo_now->getDato()->getName(); }
    if (desc.empty()) { desc = nodo_now->getDato()->getExt(); }

    nodo_now->getDato()->setDatos(name,desc);
}

