#include "spotify/hpp/herramientas.hpp"
#include "spotify/hpp/datos.hpp"
#include "spotify/hpp/estructuras.hpp"
#include "spotify/hpp/menus.hpp"

int main()
{
    spotify();
    return 0;
}

/*
g++ -std=c++11 -Wall -Wextra -Wpedantic -o app.exe *.cpp
TinyXML-2 (9.0.0) 
*/



/* ######### CRITICO #########
1- AGREGAR VLC/MPV A LAS VARIABLES DE ENTORNO 
2- para importar con xml (verificar en el enunciado): 
    insertar todas las canciones SIN el elemento "posicion", luego
    insertar todas las canciones CON el elemento "posicion", luego
    insertar todas las playlists SIN el elemento "canciones", luego
    insertar todas las playlists CON el elemento "canciones"
    
    eliminar las canciones en las listas, luego
    eliminar las listas, luego
    eliminar las canciones de la store

    lo anterior se basa en el supuesto que si el usuario necesita que su cancion quede en la posicion 3
    entonces siginifica que despues de haber agregado todas las canciones de forma secuencial,
    se necesita que en la posicion 3 quede dicha cancion
    el mismo comportamiento se puede aplicar a las demas etiquetas
3- no permitir que se elimine la STORE

4- lista doble circular
5- en el reproductor solo se debe mostrar (sin reproducir) la cancion actual 
    y los controles para cambiar de cancion,
    cuando se quiera reproducir una cancion se elige la opcion "reproducir" 
    y solo es ahi cuando se reproduce la cancion
6- hacer que el song_now cambie de cancion cuando se seleccione next o prev
7- crear el modo de reproduccion

8- ACTUALIZAR CANCION? Y PLAYLIST

*/

