#include <stdio.h>
#include <stdlib.h>

typedef struct nodo *link;

typedef struct nodo {
    int valore;
    link adiacenti;
} nodo;

typedef struct isolati {
    int contatore;
    link prossimo;
} isolati;

link * creaLista(int);
void creaAdiacenti(link *, int);
link nuovaAdiacenza(int , link);
void stampaLista(link *, int);
_Bool verificaAdiacenza(link *, int, int);
_Bool verificaRegolare(link *, int);
int *gradoMassimo(link *, int);
int nodiIsolati(link *, int);



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

    printf("Verifica della regolarita' del grafo... \n");

    if (verificaRegolare(A, dim)) {
        printf("Il grafo e' regolare. \n");
    } else {
        printf("Il grafo e' irregolare. \n");
    }

    printf("Verifica grado massimo dei nodi... \n");
    int * massimo = gradoMassimo(A, dim);
    printf("Il nodo %d ha grado massimo pari a %d. \n", massimo[0], massimo[1]);

    printf("Verifica nodi isolati... \n");
    nodiIsolati (A, dim);
    
 

   // return (EXIT_SUCCESS);
}


link *creaLista(int dim) {
    link *A = calloc(dim, sizeof (link));

    for (int i = 0; i < dim; i++) {
        A[i] = NULL ;
    }

    return A;
}

void creaAdiacenti(link *A, int dim) {
    _Bool continua = 1;
    char risposta;
    int u, v;

    while (continua) {
        printf("Vuoi inserire una adiacenza? (s/n) ");
        while ((risposta = getchar()) == '\n');
        //OPERATORE TERNARIO 
        continua = (risposta == 's') ? 1 : 0;

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
            }

            A[u]=nuovaAdiacenza(v, A[u]);
            A[v]=nuovaAdiacenza(u, A[v]);
           
        }
    }
}

link nuovaAdiacenza(int valore, link adiacenti){
                        
            link x = malloc(sizeof *x);
            x -> valore = valore; 
            x-> adiacenti = adiacenti;
            return x;
        
}

_Bool verificaAdiacenza(link *A, int u, int v) {
    link nodoCorrente = A[u];

    while (nodoCorrente != NULL) {
        if (nodoCorrente->valore == v)
            return 0;

        nodoCorrente = nodoCorrente->adiacenti;
    }

    return 1;
}

void stampaLista(link *A, int dim) {
    printf("Stampa lista: \n");

    for (int i = 0; i < dim; i++) {
        printf("[%d]", i);
        for (link nodoCorrente = A[i]; nodoCorrente != NULL; nodoCorrente = nodoCorrente->adiacenti) {
                printf(" -> %d ", nodoCorrente->valore);
        }
        printf("\n");
    }
}

_Bool verificaRegolare(link *A, int dim) {
    int numeroArchiGenerali = 0;
    link nodoCorrente;
    int numeroArchi;
    _Bool uguali = 1;

    for (int i = 0; (i < dim) && (uguali); i++) {
        numeroArchi = 0;
        nodoCorrente = A[i];
        while (nodoCorrente != NULL) {
            numeroArchi++;
            nodoCorrente = nodoCorrente->adiacenti;

        }

        if (i == 0) {
            numeroArchiGenerali = numeroArchi;
        }

        if (numeroArchiGenerali != numeroArchi) {
            uguali = 0;
        }

    }

    return uguali;

}

int *gradoMassimo(link *A, int dim) {
    link nodoCorrente;
    int massimo = 0, cont = 0;
    static int max[2];

    for (int i = 0; i < dim; i++) {
        cont = 0;
        nodoCorrente = A[i];
        while (nodoCorrente != NULL) {
            cont++;
            nodoCorrente = nodoCorrente->adiacenti;
        }

        if (cont > massimo) {
            massimo = cont;
            max[0] = i;
            max[1] = massimo;
        }

    }

    return max;
}

int nodiIsolati(link *A, int dim) {
    int cont = 0;
 
    for (int i= 0; i < dim ; i++){
        if (A[i] == NULL){
            cont ++;     
            printf (" c = %d", cont);
        }
    }
    return cont;
}