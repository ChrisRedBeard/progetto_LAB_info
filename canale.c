// canale.c
#include <stdlib.h>
#include "canale.h"

/*abbiamo pensato di usare una struct per rappresentare un canale
 come collegamento tra due nodi.
*/

struct Canale
{
    Nodo *nodo1;
    Nodo *nodo2;
};

/*
 @brief Funzione per creare un canale tra due nodi
 @param nodo1 primo nodo
 @param nodo2 secondo nodo

 @return  Restituisce un puntatore al canale creato oppure NULL in caso di errore
*/

Canale *canale_crea(Nodo *nodo1, Nodo *nodo2)
{
    Canale *c = (Canale *)malloc(sizeof(Canale));
    if (!c)
        return NULL;
    c->nodo1 = nodo1;
    c->nodo2 = nodo2;
    return c;
}

// Funzione per distruggere un canale
void canale_distruggi(Canale *c)
{
    free(c);
}

// Funzione per ottenere l'altro nodo connesso a un canale partendo dal nodo di partenza
Nodo *canale_get_altro_nodo(Canale *c, Nodo *da)
{
    if (c->nodo1 == da)
        return c->nodo2;
    else if (c->nodo2 == da)
        return c->nodo1;
    else
        return NULL; // Nodo non connesso a questo canale
}
