// nodo.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nodo.h"

struct Nodo
{
    int id;
    Canale **canali; // array dinamico di canali connessi
    int num_canali;
    int cap_canali;

    Messaggio **coda_messaggi; // coda di messaggi in arrivo
    int num_messaggi;
    int cap_messaggi; /*Quando il numero di messaggi (num_messaggi) supera la capacità attuale (cap_messaggi),
    il codice utilizza realloc per aumentare la dimensione dell'array coda_messaggi-
    Questo permette al nodo di accettare più messaggi senza perdere quelli già presenti.*/
};

Nodo *nodo_crea(int id)
{
    Nodo *n = (Nodo *)malloc(sizeof(Nodo));
    if (!n)
        return NULL;
    n->id = id;
    n->num_canali = 0;
    n->cap_canali = 4;
    n->canali = (Canale **)malloc(n->cap_canali * sizeof(Canale *));
    n->num_messaggi = 0;
    n->cap_messaggi = 4;
    n->coda_messaggi = (Messaggio **)malloc(n->cap_messaggi * sizeof(Messaggio *));
    return n;
}

void nodo_distruggi(Nodo *n)
{
    if (!n)
        return;
    free(n->canali);
    for (int i = 0; i < n->num_messaggi; i++)
    {
        messaggio_distruggi(n->coda_messaggi[i]);
    }
    free(n->coda_messaggi);
    free(n);
}

int nodo_get_id(Nodo *n)
{
    return n->id;
}

void nodo_aggiungi_canale(Nodo *n, Canale *c)
{
    if (n->num_canali == n->cap_canali)
    {
        n->cap_canali *= 2;
        n->canali = (Canale **)realloc(n->canali, n->cap_canali * sizeof(Canale *));
    }
    n->canali[n->num_canali++] = c;
}

void nodo_stampa(Nodo *n)
{
    printf("Nodo %d connesso a nodi: ", n->id);
    for (int i = 0; i < n->num_canali; i++)
    {
        Nodo *altro = canale_get_altro_nodo(n->canali[i], n);
        printf("%d ", nodo_get_id(altro));
    }
    printf("\n");
}

void nodo_ricevi_messaggio(Nodo *n, Messaggio *m)
{
    // Inserisce il messaggio nella coda di messaggi in arrivo
    if (n->num_messaggi == n->cap_messaggi)
    {
        n->cap_messaggi *= 2;
        n->coda_messaggi = (Messaggio **)realloc(n->coda_messaggi, n->cap_messaggi * sizeof(Messaggio *));
    }
    n->coda_messaggi[n->num_messaggi++] = m;
}

void nodo_processa_messaggi(Nodo *n)
{
    // Processa tutti messaggi in coda (ad es. fa flooding)
    for (int i = 0; i < n->num_messaggi; i++)
    {
        Messaggio *m = n->coda_messaggi[i];
        printf("[Nodo %d] Processa messaggio ID %d: \"%s\"\n", n->id, messaggio_get_id(m), messaggio_get_contenuto(m));
        // Esempio: flooding - invia il messaggio a tutti i nodi vicini tranne da cui è arrivato
        for (int j = 0; j < n->num_canali; j++)
        {
            Nodo *vicino = canale_get_altro_nodo(n->canali[j], n);
            // Per evitare loop semplice, non ritrasmettiamo se ID messaggio già visto. (Qui semplificato, inviato comunque)
            // In una versione avanzata si inserirebbe filtro o lista messaggi ricevuti.
            printf("-- Invio messaggio ID %d da nodo %d a nodo %d\n", messaggio_get_id(m), n->id, nodo_get_id(vicino));
            // Copia messaggio per nuovo nodo (qui stesso puntatore per semplicità)
            Messaggio *m_nuovo = messaggio_crea(messaggio_get_id(m), messaggio_get_contenuto(m));
            nodo_ricevi_messaggio(vicino, m_nuovo);
        }
        messaggio_distruggi(m);
    }
    n->num_messaggi = 0;
}