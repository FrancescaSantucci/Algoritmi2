#include <stdio.h>
#include <stdlib.h>

typedef struct elemento {
    int nodo;
    struct elemento *adiacenti;
} elemento;

typedef elemento *link;

link * creaLista(int);
void creaAdiacenti(link *, int);
void aggiungiAdiacenza(link *, int, int);
void stampaLista(link *, int);
_Bool verificaAdiacenza(link *, int, int);

int main() {
    setbuf(stdout, NULL);
    int dim;

    printf("GRAFO NON ORIENTATO CON RAPPRESENTAZIONE TRAMITE LISTE DI ADIACENZA \n");

    printf("Inserisci il numero di nodi del grafo. \n");
    scanf("%d", &dim);

    printf("Creazione in corso... \n");
    link *A = creaLista(dim);

    stampaLista(A, dim);

    printf("Inserimento dei nodi adiacenti...  \n");
    creaAdiacenti(A, dim);
    
    stampaLista(A, dim);
    
    return(EXIT_SUCCESS);
}

link * creaLista(int dim) {
    link *A = calloc(dim, sizeof (link));

    /*
     * MEMORIA DINAMICA 
     * Potremmo utilizzare questa chiamata: 
     *       elemento *A = calloc(dim, sizeof(elemento));
     * ma si rischia di non avere memoria a sufficenza poiché andiamo ad allocare in memoria dim struct.
     * Quindi useremmo memoria statica piuttosto che dinamica.
     * In questo modo, creiamo i nostri elementi al momento dell'occorrenza
     *  nella memoria dinamica (memoria grande).
     */

    for (int i = 0; i < dim; i++) {
        A[i] = calloc(1, sizeof (elemento));
        A[i]->nodo = i;
        /*
         *      Commento MEMORIA DINAMICA
         *      A[i].nodo = i;  
         */
    }

    return A;
}

void creaAdiacenti(link *A, int dim) {
    _Bool continua = 1;
    char risposta;
    int u, v;

    while (continua) {
        printf("Vuoi inserire una adiacenza? (s/n) \n");
        scanf(" %c", &risposta);
        continua = (risposta == 's') ? 1 : 0;
        
        /*
         * OPERATORE TERNARIO
         *      continua = (risposta == 's') ? 1 : 0;
         *      variabile = (condizione) ? vero : falso;
         * continua = 1 se risposta è uguale a 's' altrimenti sarà 0. 
         */
        
        if (risposta == 's') {
            printf("Inserisci il nodo di partenza dell'arco. \n");
            scanf("%d", &u);
            printf("Inserisci il nodo di arrivo dell'arco. \n");
            scanf("%d", &v);

            if (u >= dim || v >= dim || u == v) {
                printf("Errore: il valore inserito eccede rispetto al valore dei nodi o sono lo stesso nodo \n");
                continue;
            }

            if (!verificaAdiacenza(A, u, v) || !verificaAdiacenza(A, v, u)) {
                printf("Errore: l'arco gia' esiste. \n ");
                continue;
            } else {
                aggiungiAdiacenza(A, u, v);
                aggiungiAdiacenza(A, v, u);
            }

        }
    }
}

_Bool verificaAdiacenza(link *A, int u, int v) {
    link nodoCorrente = A[u];
    
    while (nodoCorrente->adiacenti != NULL) {
        if (nodoCorrente->adiacenti->nodo == v)
            return 0;
        
        nodoCorrente = nodoCorrente->adiacenti;
    }
    
    return 1;
}

void aggiungiAdiacenza(link *A, int u, int v) {
    link nodoCorrente = A[u];

    while (nodoCorrente->adiacenti != NULL)
        nodoCorrente = nodoCorrente->adiacenti;
    
    nodoCorrente->adiacenti = calloc(1, sizeof(elemento));
    nodoCorrente->adiacenti->nodo = v;
    
    printf("Aggiunta dell'adiacenza tra %d e %d riuscita. \n", u, v);
}

void stampaLista(link *A, int dim) {
    printf("Stampa lista: \n");
    
    for (int i = 0; i < dim; i++) {
        link nodoCorrente = A[i];
        printf("[%d]", nodoCorrente->nodo);
        for (nodoCorrente = nodoCorrente->adiacenti; nodoCorrente != NULL; nodoCorrente = nodoCorrente->adiacenti) {
            printf(" -> %d", nodoCorrente->nodo);
        }
        printf("\n");
    }
}