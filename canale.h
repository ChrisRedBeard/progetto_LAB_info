// canale.h
#ifndef CANALE_H
#define CANALE_H

typedef struct Nodo Nodo; // Forward declaration

typedef struct Canale Canale;

Canale* canale_crea(Nodo *nodo1, Nodo *nodo2);
void canale_distruggi(Canale *c);
Nodo* canale_get_altro_nodo(Canale *c, Nodo *da);

#endif