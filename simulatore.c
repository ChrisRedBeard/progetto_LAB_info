// simulatore.c
#include <stdio.h>
#include <stdlib.h>
#include <windows.h> // for Sleep

#include "nodo.h"
#include "canale.h"
#include "messaggio.h"
#include "protocollo.h"

/*
gcc simulatore.c nodo.c canale.c messaggio.c protocollo.c -o simulatore

*/


// ANSI escape codes for colors
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define WHITE   "\x1b[37m"
#define RESET   "\x1b[0m"



// Line length between nodes
#define LINE_LENGTH 30
void draw_message_progress(int progress) {
    // progress: how many characters of the line are colored celeste
    // Print nodes and line with progressive coloring
    printf("[Node1] ");
    for (int i = 0; i < LINE_LENGTH; i++) {
        if (i < progress) {
            printf(CYAN "-");
        } else {
            printf(WHITE "-");
        }
    }
    printf(" [Node2]" RESET "\r");
    fflush(stdout);
}






int main() {
    // Creazione nodi
    Nodo *n1 = nodo_crea(1);
    Nodo *n2 = nodo_crea(2);
    Nodo *n3 = nodo_crea(3);
    Nodo *n4 = nodo_crea(4);

    // Creazione canali (collegamenti)
    Canale *c1 = canale_crea(n1, n2);
    Canale *c2 = canale_crea(n2, n3);
    Canale *c3 = canale_crea(n3, n4);
    Canale *c4 = canale_crea(n4, n1);

    // Aggiunge canali ai nodi
    nodo_aggiungi_canale(n1, c1);
    nodo_aggiungi_canale(n1, c4);
    nodo_aggiungi_canale(n2, c1);
    nodo_aggiungi_canale(n2, c2);
    nodo_aggiungi_canale(n3, c2);
    nodo_aggiungi_canale(n3, c3);
    nodo_aggiungi_canale(n4, c3);
    nodo_aggiungi_canale(n4, c4);

    // Stampa stato nodi
    nodo_stampa(n1);
    nodo_stampa(n2);
    nodo_stampa(n3);
    nodo_stampa(n4);

/*
Il fine di un protocollo di routing del tipo Link state(ha una visione completa della rete) è quello di adattare i routers alle modifiche della rete.
Questo può essere fatto solo se il database di link state viene aggiornato dopo ogni modifica dello stato del link.
*/
    // Avvio flooding messaggio da nodo 1
    protocollo_avvia_flooding(n1, "Messaggio di test flooding");
     // Avvio flooding messaggio da nodo 1
    protocollo_avvia_flooding(n2, "Messaggio di test flooding");


    // Cleanup
    canale_distruggi(c1);
    canale_distruggi(c2);
    canale_distruggi(c3);
    canale_distruggi(c4);
    nodo_distruggi(n1);
    nodo_distruggi(n2);
    nodo_distruggi(n3);
    nodo_distruggi(n4);
    printf("Simulatore terminato.\n");
   

    // Initially all line is white
    draw_message_progress(0);
    Sleep(3000);

    
    
    for (int i = 1; i <= LINE_LENGTH; i++) {
        draw_message_progress(i);
         Sleep(1000); // wait 100 ms to simulate animation
    }
    printf("\nMessaggio inviato!\n");

    printf("\n");

    return 0;
}