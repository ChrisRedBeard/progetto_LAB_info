// protocollo.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "protocollo.h"
#include "messaggio.h"
#include "nodo.h"

void protocollo_avvia_flooding(Nodo *start, const char *contenuto) {
    // Crea messaggio iniziale e lo inserisce nel nodo start
    Messaggio *m = messaggio_crea(rand() % 1000, contenuto);
    printf("Avvio flooding nel nodo %d con messaggio: %s\n", nodo_get_id(start), contenuto);
    nodo_ricevi_messaggio(start, m);
    nodo_processa_messaggi(start);
}
    