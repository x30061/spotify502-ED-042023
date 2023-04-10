#include "hpp/importar-xml.hpp"
#include "hpp/controles.hpp"

tinyxml2::XMLDocument doc;

void cargarNuevoXML(std::string path)
{
    doc.Clear();
    tinyxml2::XMLError res = doc.LoadFile(path.c_str());
    if (res == tinyxml2::XML_SUCCESS) 
    {
        elementoInsertar_lectura1();
        elementoInsertar_lectura2();
        elementoEliminar_lectura1();
        elementoEliminar_lectura2();
        elementoEliminar_lectura3();
    }
}

// agrega nuevas canciones a la STORE o agrega nuevas playlists a SPOTIFY
void elementoInsertar_lectura1()
{
    tinyxml2::XMLElement *nivel_1 = doc.FirstChildElement("Insertar");
    if (nivel_1 == NULL){return;}

    while (true)
    {
        //std::cout << nivel_1->GetLineNum() << ": "<< nivel_1->Name() << '\n';

        tinyxml2::XMLElement *nivel_2 = nivel_1->FirstChildElement();
        if (nivel_2 == NULL) { return; }

        while (true)
        {
            //std::cout << nivel_2->GetLineNum() << ": "<< nivel_2->Name() << '\n';

            if (strcmp(nivel_2->Name(),"cancion") == 0)
            {
                tinyxml2::XMLElement *nivel_3 = nivel_2->FirstChildElement("Pos");
                if (nivel_3 == NULL)
                {
                    nivel_3 = nivel_2->FirstChildElement("Nombre");
                    //std::cout << nivel_3->GetLineNum() << "S: "<< nivel_3->GetText() << '\n';
                    std::string name = nivel_3->GetText();

                    nivel_3 = nivel_2->FirstChildElement("path");
                    //std::cout << nivel_3->GetLineNum() << ": "<< nivel_3->GetText() << '\n';
                    std::string path = nivel_3->GetText();

                    Dato *d = new Dato(SONG,name,path);
                    Nodo *n = new Nodo(d);

                    insertar(&(nodo_store->cen),n,-1);
                    imprimir("nueva cancion en \'-1\'@\'STORE\': " + n->getInfo() + "\n");
                }
            }
            else if(strcmp(nivel_2->Name(),"Lista") == 0)
            {
                tinyxml2::XMLElement *nivel_3 = nivel_2->FirstChildElement("Canciones");
                if (nivel_3 == NULL)
                {
                    nivel_3 = nivel_2->FirstChildElement("Nombre");
                    //std::cout << nivel_3->GetLineNum() << "L: "<< nivel_3->GetText() << '\n';
                    std::string name = nivel_3->GetText();
                    
                    nivel_3 = nivel_2->FirstChildElement("Descripcion");
                    //std::cout << nivel_3->GetLineNum() << ": "<< nivel_3->GetText() << '\n';
                    std::string desc = nivel_3->GetText();

                    Dato *d = new Dato(PLIST,name,desc);
                    Nodo *n = new Nodo(d);
                    insertar(&nodo_store,n,-1);
                    imprimir("nueva lista en \'-1\'@\'SPOTIFY\': " + n->getInfo() + "\n");
                }
            }

            if (nivel_2->NextSiblingElement() == NULL)
            {
                //std::cout << "<<<<< nivel_2\n";
                break;
            }
            nivel_2 = nivel_2->NextSiblingElement();
        }
        
        if (nivel_1->NextSiblingElement("Insertar") == NULL)
        {
            //std::cout << "<<<<< nivel_1\n";
            break;
        }
        nivel_1 = nivel_1->NextSiblingElement("Insertar");
    }
}// <<<<<<<<< FINALIZADO

/* agrega una nueva playlist con canciones de la STORE a SPOTIFY o 
agrega nuevas canciones a la STORE en una posicion de la STORE*/
void elementoInsertar_lectura2()
{
    tinyxml2::XMLElement *nivel_1 = doc.FirstChildElement("Insertar");
    if (nivel_1 == NULL){return;}

    while (true)
    {
        //std::cout << nivel_1->GetLineNum() << ": "<< nivel_1->Name() << '\n';

        tinyxml2::XMLElement *nivel_2 = nivel_1->FirstChildElement();
        if (nivel_2 == NULL) { return; }

        while (true)
        {
            //std::cout << nivel_2->GetLineNum() << ": "<< nivel_2->Name() << '\n';

            if (strcmp(nivel_2->Name(),"cancion") == 0)
            {
                tinyxml2::XMLElement *nivel_3 = nivel_2->FirstChildElement("Pos");
                if (nivel_3 != NULL)
                {
                    nivel_3 = nivel_2->FirstChildElement("Nombre");
                    //std::cout << nivel_3->GetLineNum() << "S: "<< nivel_3->GetText() << '\n';
                    std::string name = nivel_3->GetText();

                    nivel_3 = nivel_2->FirstChildElement("path");
                    //std::cout << nivel_3->GetLineNum() << ": "<< nivel_3->GetText() << '\n';
                    std::string path = nivel_3->GetText();

                    nivel_3 = nivel_2->FirstChildElement("Pos");
                    //std::cout << nivel_3->GetLineNum() << ": "<< nivel_3->GetText() << '\n';
                    std::string pos = nivel_3->GetText();

                    Dato *d = new Dato(SONG,name,path);
                    Nodo *n = new Nodo(d);
                    insertar(&(nodo_store->cen),n,std::stoi(pos));
                    imprimir("nueva cancion en \'" + pos + "\'@\'STORE\': " + n->getInfo() + "\n");
                }
            }
            else if(strcmp(nivel_2->Name(),"Lista") == 0)
            {
                tinyxml2::XMLElement *nivel_3 = nivel_2->FirstChildElement("Canciones");
                if (nivel_3 != NULL)
                {
                    nivel_3 = nivel_2->FirstChildElement("Nombre");
                    //std::cout << nivel_3->GetLineNum() << "L: "<< nivel_3->GetText() << '\n';
                    std::string name = nivel_3->GetText();

                    nivel_3 = nivel_2->FirstChildElement("Descripcion");
                    //std::cout << nivel_3->GetLineNum() << ": "<< nivel_3->GetText() << '\n';
                    std::string desc = nivel_3->GetText();

                    nivel_3 = nivel_2->FirstChildElement("Canciones");
                    //std::cout << nivel_3->GetLineNum() << ": ... " << '\n';

                    Dato *d = new Dato(PLIST,name,desc);
                    Nodo *nodo_new = new Nodo(d);
                    insertar(&nodo_store,nodo_new,-1);
                    imprimir("nueva lista en \'-1\'@\'SPOTIFY\': " + nodo_new->getInfo() + "\n");
                    
                    tinyxml2::XMLElement *nivel_4 = nivel_3->FirstChildElement("pos");
                    if (nivel_4 != NULL) 
                    {
                        while (true)
                        {
                            //std::cout << nivel_4->GetLineNum() << "#: "<< nivel_4->GetText() << '\n';
                            std::string pos = nivel_4->GetText();
                            int p = std::stoi(pos);

                            Nodo *song_store = nodoEn(nodo_store->cen,p);

                            Nodo *song_store_copy = song_store->getCopia();

                            insertar(&(nodo_new->cen),song_store_copy,-1);
                            imprimir("nueva cancion en \'" + pos + "\'@\'" + nodo_new->getDato()->getName() + "\'\n");

                            if (nivel_4->NextSiblingElement("pos") == NULL)
                            {
                                //std::cout << "<<<<< nivel_4\n";
                                break;
                            }
                            nivel_4 = nivel_4->NextSiblingElement("pos");
                        }
                    }
                }
            }

            if (nivel_2->NextSiblingElement() == NULL)
            {
                //std::cout << "<<<<< nivel_2\n";
                break;
            }
            nivel_2 = nivel_2->NextSiblingElement();
        }
        
        if (nivel_1->NextSiblingElement("Insertar") == NULL)
        {
            //std::cout << "<<<<< nivel_1\n";
            break;
        }
        nivel_1 = nivel_1->NextSiblingElement("Insertar");
    }
} // <<<<<<<<< FINALIZADO


// elimina canciones de las posiciones de una playlist 
void elementoEliminar_lectura1()
{
    tinyxml2::XMLElement *nivel_1 = doc.FirstChildElement("Eliminar");
    if (nivel_1 == NULL){return;}

    while (true)
    {
        //std::cout << nivel_1->GetLineNum() << ": "<< nivel_1->Name() << '\n';

        tinyxml2::XMLElement *nivel_2 = nivel_1->FirstChildElement("Lista");
        if (nivel_2 == NULL) { return; }

        while (true)
        {
            //std::cout << nivel_2->GetLineNum() << ": "<< nivel_2->Name() << '\n';

            tinyxml2::XMLElement *nivel_3 = nivel_2->FirstChildElement("canciones");
            if (nivel_3 != NULL)
            {
                nivel_3 = nivel_2->FirstChildElement("id");
                //std::cout << nivel_3->GetLineNum() << "~L: "<< nivel_3->GetText() << '\n';
                std::string id = nivel_3->GetText();

                nivel_3 = nivel_2->FirstChildElement("canciones");
                //std::cout << nivel_3->GetLineNum() << ":_ " << '\n';

                tinyxml2::XMLElement *nivel_4 = nivel_3->FirstChildElement("pos");
                if (nivel_4 != NULL) 
                {
                    Nodo *nodo_plist = nodoEn(nodo_store,std::stoi(id));

                    while (true)
                    {
                        //std::cout << nivel_4->GetLineNum() << "#: "<< nivel_4->GetText() << '\n';
                        std::string pos = nivel_4->GetText();
                        int pos_int = std::stoi(pos);

                        eliminarPorPosicion(&(nodo_plist->cen),pos_int);
                        imprimir("cancion eliminada: \'" + pos + "\'@\'" + nodo_plist->getDato()->getName() + "\'\n");

                        if (nivel_4->NextSiblingElement("pos") == NULL)
                        {
                            //std::cout << "<<<<< nivel_4\n";
                            break;
                        }
                        nivel_4 = nivel_4->NextSiblingElement("pos");
                    }
                }
            }

            if (nivel_2->NextSiblingElement("Lista") == NULL)
            {
                //std::cout << "<<<<< nivel_2\n";
                break;
            }
            nivel_2 = nivel_2->NextSiblingElement("Lista");
        }
        
        if (nivel_1->NextSiblingElement("Eliminar") == NULL)
        {
            //std::cout << "<<<<< nivel_1\n";
            break;
        }
        nivel_1 = nivel_1->NextSiblingElement("Eliminar");
    }
} // <<<<<<<<< FINALIZADO

// elimina playlists por nombre o por posicion
void elementoEliminar_lectura2()
{
    tinyxml2::XMLElement *nivel_1 = doc.FirstChildElement("Eliminar");
    if (nivel_1 == NULL){return;}

    while (true)
    {
        //std::cout << nivel_1->GetLineNum() << ": "<< nivel_1->Name() << '\n';

        tinyxml2::XMLElement *nivel_2 = nivel_1->FirstChildElement("Lista");
        if (nivel_2 == NULL) { return; }

        while (true)
        {
            //std::cout << nivel_2->GetLineNum() << ": "<< nivel_2->Name() << '\n';

            tinyxml2::XMLElement *nivel_3 = nivel_2->FirstChildElement("Nombre");
            if (nivel_3 != NULL)
            {
                //std::cout << nivel_3->GetLineNum() << "~L-: "<< nivel_3->GetText() << '\n';
                std::string name = nivel_3->GetText();

                //int pos = posicionPorNombre(nodo_store,name);
                //eliminar(&(nodo_store),pos);
                
                eliminarPorNombre(&nodo_store,name);
                imprimir("playlist eliminada: \'" + name + "\'@\'SPOTIFY\'\n");
            }
            else
            {
                nivel_3 = nivel_2->FirstChildElement("canciones");
            }
            if (nivel_3 == NULL)
            {
                nivel_3 = nivel_2->FirstChildElement("id");
                //std::cout << nivel_3->GetLineNum() << "~L#: "<< nivel_3->GetText() << '\n';

                std::string id = nivel_3->GetText();
                int id_int = std::stoi(id);

                eliminarPorPosicion(&nodo_store,id_int);
                imprimir("playlist eliminada: \'" + id + "\'@\'SPOTIFY\'\n");
            }
            
            if (nivel_2->NextSiblingElement("Lista") == NULL)
            {
                //std::cout << "<<<<< nivel_2\n";
                break;
            }
            nivel_2 = nivel_2->NextSiblingElement("Lista");
        }
        
        if (nivel_1->NextSiblingElement("Eliminar") == NULL)
        {
            //std::cout << "<<<<< nivel_1\n";
            break;
        }
        nivel_1 = nivel_1->NextSiblingElement("Eliminar");
    }
} // <<<<<<<<< FINALIZADO

// elimina canciones por nombre o por posicion de la store
void elementoEliminar_lectura3()
{
    tinyxml2::XMLElement *nivel_1 = doc.FirstChildElement("Eliminar");
    if (nivel_1 == NULL){return;}

    while (true)
    {
        //std::cout << nivel_1->GetLineNum() << ": "<< nivel_1->Name() << '\n';

        tinyxml2::XMLElement *nivel_2 = nivel_1->FirstChildElement("cancion");
        if (nivel_2 == NULL) { return; }

        while (true)
        {
            //std::cout << nivel_2->GetLineNum() << ": "<< nivel_2->Name() << '\n';
            
            tinyxml2::XMLElement *nivel_3 = nivel_2->FirstChildElement();
            if (strcmp(nivel_3->Name(),"Nombre") == 0)
            {
                //std::cout << nivel_3->GetLineNum() << "~S-: "<< nivel_3->GetText() << '\n';
                std::string name = nivel_3->GetText();

                eliminarPorNombre(&(nodo_store->cen),name);
                imprimir("cancion eliminada: \'" + name + "\'@\'STORE\'\n");
            }
            else if (strcmp(nivel_3->Name(),"id") == 0)
            {
                //std::cout << nivel_3->GetLineNum() << "~S#: "<< nivel_3->GetText() << '\n';
                std::string id = nivel_3->GetText();
                int id_int = std::stoi(id);

                eliminarPorPosicion(&(nodo_store->cen),id_int);
                imprimir("cancion eliminada: \'" + id + "\'@\'STORE\'\n");
            }
            
            if (nivel_2->NextSiblingElement("cancion") == NULL)
            {
                //std::cout << "<<<<< nivel_2\n";
                break;
            }
            nivel_2 = nivel_2->NextSiblingElement("cancion");
        }
        
        if (nivel_1->NextSiblingElement("Eliminar") == NULL)
        {
            //std::cout << "<<<<< nivel_1\n";
            break;
        }
        nivel_1 = nivel_1->NextSiblingElement("Eliminar");
    }
}
