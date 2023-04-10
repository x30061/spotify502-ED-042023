#include "hpp/menus.hpp"
#include "hpp/controles.hpp"
#include "hpp/estructuras.hpp"
#include "hpp/importar-xml.hpp"

std::string menu_spoti = "";
std::string menu_repr = "";
std::string menu_store = "";
std::string menu_plistS = "";
std::string menu_abrir = "";

void initMenus()
{
    menu_spoti.append(getTitulo("SPOTIFY") + "\n");
    menu_spoti.append(" 1. reproductor\n"); // -> solicitar playlist
    menu_spoti.append(" 2. store\n");
    menu_spoti.append(" 3. playlists\n");
    menu_spoti.append(" 4. importar ajustes\n");
    menu_repr.append(getTitulo("REPRODUCTOR") + "\n");
    menu_repr.append(" 1. reproducir \n"); // if (cancion == NULL): -> solicitar modo -> solicitar cancion
    menu_repr.append(" 2. anterior\n");
    menu_repr.append(" 3. siguiente\n");
    menu_repr.append(" 4. ver proximas\n");
    menu_repr.append(" 5. agregar a proximas\n");
    //menu_repr.append(" 7. modo de reproduccion\n");
    menu_store.append(getTitulo("STORE") + "\n");
    menu_store.append(" 1. ver canciones \n");
    menu_store.append(" 2. buscar cancion \n");
    menu_store.append(" 3. ingresar cancion\n");
    menu_store.append(" 4. eliminar cancion\n");
    menu_plistS.append(getTitulo("PLAYLISTS") + "\n");
    menu_plistS.append(" 1. ver playlistS\n");
    menu_plistS.append(" 2. abrir playlist\n");
    menu_plistS.append(" 3. ingresar playlist\n");
    menu_plistS.append(" 4. eliminar playlist\n");
    menu_abrir.append(getTitulo("ABRIR PLAYLIST") + "\n");
    menu_abrir.append(" 1. ver canciones\n");
    menu_abrir.append(" 2. ingresar cancion\n");
    menu_abrir.append(" 3. actualizar playlist\n");
    menu_abrir.append(" 4. eliminar cancion\n");
}

void spotify()
{
    initMenus();
    while (true)
    {
        imprimir(menu_spoti);
        imprimir("ingrese una opcion: ");
        int i = 0;
        std::cin >> i;

        if ((1 <= i) & (i <= 4))
        {
            spotify(i);
        }
        else { return; }    
    }
}
void spotify(int i)
{
    switch (i)
    {
    case 1: //reproductor
        reproductor();
        break;
    case 2: //store
        store();
        break;
    case 3: //playlists
        playlistS();
        break;
    case 4: //importar ajustes
        importarAjustes();
        break;
    default:
        break;
    }
}

void reproductor()
{
    imprimir(getSubTitulo("ELEGIR PLAYLIST") + "\n");
    seleccionarPlaylist();
    imprimir(getSubTitulo("MODO DE REPRODUCCION") + "\n");
    modoReproduccion();
    initReproductor();
    
    while (true)
    {
        imprimir(menu_repr);
        imprimir(getSubTitulo("CANCION ACTUAL") + "\n");
        imprimir(getCancionActual() + "\n");
        imprimir("ingrese una opcion: ");
        int i = 0;
        std::cin >> i;

        if ((1 <= i) & (i <= 5))
        {
            reproductor(i);
        }
        else { return; }    
    }
}
void reproductor(int i)
{
    switch (i)
    {
    case 1: //reproducir
        play();
        break;
    case 2: //anterior
        prevSong();
        break;
    case 3: //siguiente
        nextSong();
        break;
    case 4: //ver proximas
        imprimir(getSubTitulo("VER PROXIMAS") + "\n");
        imprimir(getProximas());
        break;
    case 5: //agregar a proximas -> mostrar store
        imprimir(getSubTitulo("AGREGAR A PROXIMAS") + "\n");
        insertarProximas();
        break;
    //case 7: //modo de reproduccion
        //imprimir(getSubTitulo("MODO DE REPRODUCCION") + "\n");
        break;
    default:
        break;
    }
}

void store()
{
    while (true)
    {
        imprimir(menu_store);
        imprimir("ingrese una opcion: ");
        int i = 0;
        std::cin >> i;

        if ((1 <= i) & (i <= 4))
        {
            store(i);
        }
        else { return; }    
    }
}

void store(int i)
{
    switch (i)
    {
    case 1: //ver canciones 
        imprimir(getSubTitulo("VER CANCIONES") + "\n");
        imprimir(getLista(nodo_store->cen));
        break;
    case 2: //buscar cancion
        imprimir(getSubTitulo("BUSCAR CANCION") + "\n");
        buscarCancion();
        break;
    case 3: //ingresar cancion
        imprimir(getSubTitulo("INGRESAR CANCION") + "\n");
        insertarCancionManual(&(nodo_store->cen));
        break;
    case 4: //eliminar cancion
        imprimir(getSubTitulo("ELIMINAR CANCION") + "\n");
        eliminarCancionManual(&(nodo_store->cen));
        break;
    default:
        break;
    }
}

void playlistS()
{
    while (true)
    {
        imprimir(menu_plistS);
        imprimir("ingrese una opcion: ");
        int i = 0;
        std::cin >> i;

        if ((1 <= i) & (i <= 4))
        {
            playlistS(i);
        }
        else { return; }    
    }
}

void playlistS(int i)
{
    switch (i)
    {
    case 1: //ver playlistS 
        imprimir(getSubTitulo("VER PLAYLISTS") + "\n");
        imprimir(getLista(nodo_store));
        break;
    case 2: //abrir playlist
        abrirPlaylist();
        break;
    case 3: //ingresar playlist
        imprimir(getSubTitulo("INGRESAR PLAYLIST") + "\n");
        insertarPlaylistManual(&nodo_store);
        break;
    case 4: //eliminar playlist
        imprimir(getSubTitulo("ELIMINAR PLAYLIST") + "\n");
        eliminarPlaylistManual(&nodo_store);
        break;
    default:
        break;
    }
}

void abrirPlaylist()
{
    imprimir(getSubTitulo("ELEGIR PLAYLIST") + "\n");
    seleccionarPlaylist();
    
    while (true)
    {
        imprimir(menu_abrir);
        imprimir("ingrese una opcion: ");
        int i = -2;
        std::cin >> i;

        if ((1 <= i) & (i <= 4))
        {
            abrirPlaylist(i);
        }
        else {return;}
    }
}

void abrirPlaylist(int i)
{
    switch (i)
    {
    case 1: //ver canciones
        imprimir(getSubTitulo("VER CANCIONES") + "\n");
        imprimir(getLista(nodo_now->cen));
        break;
    case 2: //ingresar cancion
        imprimir(getSubTitulo("INGRESAR CANCION") + "\n");
        insertarCancionManual(&(nodo_now->cen));
        break;
    case 3: //actualizar playlist
        imprimir(getSubTitulo("ACTUALIZAR DATOS") + "\n");
        actualizarPlaylist();
        break;
    case 4: //eliminar cancion
        imprimir(getSubTitulo("ELIMINAR CANCION") + "\n");
        eliminarCancionManual(&(nodo_now->cen));
        break;
    default:
        break;
    }
}

