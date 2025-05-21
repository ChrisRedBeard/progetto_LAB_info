
// messaggio.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "messaggio.h"

// struct del messaggio
struct Messaggio
{
    int id;
    char *contenuto;
};

Messaggio *messaggio_crea(int id, const char *contenuto)
{
    Messaggio *m = (Messaggio *)malloc(sizeof(Messaggio));
    if (!m)
        return NULL;
    m->id = id;
    m->contenuto = strdup(contenuto);
    return m;
}

// Funzione per distruggere un messaggio
void messaggio_distruggi(Messaggio *m)
{
    if (m)
    {
        free(m->contenuto);
        free(m);
    }
}

// Funzioni per ottenere l'ID
int messaggio_get_id(Messaggio *m)
{
    return m ? m->id : -1;
}
// Funzioni per ottenere il contenuto del messaggio
const char *messaggio_get_contenuto(Messaggio *m)
{
    return m ? m->contenuto : NULL;
}

// Funzione per stampare il messaggio
void messaggio_stampa(Messaggio *m)
{
    if (m)
        printf("Messaggio ID %d: %s\n", m->id, m->contenuto);
}
