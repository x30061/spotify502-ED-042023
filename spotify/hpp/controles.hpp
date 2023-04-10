#include "estructuras.hpp"
#ifndef CONTROLES_HPP
#define CONTROLES_HPP

extern Nodo *song1_proximas;
extern Nodo *nodo_store;
extern Nodo *nodo_now;
extern Nodo *song_now;

void modoReproduccion();
std::string getCancionActual();
std::string getTitulo(std::string t);
std::string getSubTitulo(std::string t);
std::string getLista(Nodo *init);
std::string getProximas();
void buscarCancion();
void seleccionarPlaylist();
void insertarCancionManual(Nodo **plist);
void eliminarCancionManual(Nodo **plist);
void insertarPlaylistManual(Nodo **plist);
void eliminarPlaylistManual(Nodo **plist);
void insertarProximas();
Nodo * nodoPorNombre(Nodo *inicio,std::string name);
void importarAjustes();
int posicionPorNombre(Nodo *inicio,std::string name);
void initReproductor();
void play();
void prevSong();
void nextSong();
void eliminarPorNombre(Nodo **inicial,std::string name);
void actualizarPlaylist();

#endif 