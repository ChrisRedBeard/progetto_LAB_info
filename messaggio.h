// messaggio.h
#ifndef MESSAGGIO_H
#define MESSAGGIO_H

typedef struct Messaggio Messaggio;

Messaggio *messaggio_crea(int id, const char *contenuto);
void messaggio_distruggi(Messaggio *m);
int messaggio_get_id(Messaggio *m);
const char* messaggio_get_contenuto(Messaggio *m);
void messaggio_stampa(Messaggio *m);

#endif
