// nodo.h
#ifndef NODO_H
#define NODO_H

#include "messaggio.h"
#include "canale.h"

typedef struct Nodo Nodo;

Nodo* nodo_crea(int id);
void nodo_distruggi(Nodo *n);
int nodo_get_id(Nodo *n);

void nodo_aggiungi_canale(Nodo *n, Canale *c);
void nodo_stampa(Nodo *n);
void nodo_ricevi_messaggio(Nodo *n, Messaggio *m);
void nodo_processa_messaggi(Nodo *n);

#endif