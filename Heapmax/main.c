#include<stdio.h>


void maxHeapify(int arr[], int i, int n) {
    int l, r, largest, temp;
    l = 2 * i;
    r = (2 * i) + 1;
    if (l <= n && arr[l] > arr[i])
        largest = l;
    else
        largest = i;
    if (r <= n && arr[r] > arr[largest])
        largest = r;
    if (largest != i) {
        temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        maxHeapify(arr, largest, n);
    }
}

void buildHeap(int arr[], int n) {
    int i;
    for (i = n / 2; i >= 1; i--)
        maxHeapify(arr, i, n);
    
    printf("\nHeap attuale: \n");
    for (i = 1; i <= n; i++) {
        printf("%d - ", arr[i]);
    }
}

int heapMaximum(int arr[]) {
    return arr[1];
}

int heapExtractMax(int arr[], int n) {
    int max;
    if (n < 1) {
        printf("Heap Underflow \n");
        return -1;
    } else {
        max = arr[1];
        arr[1] = arr[n];
        n = n - 1;
        maxHeapify(arr, 1, n);
        return max;
    }
}

void heapIncreaseKey(int arr[], int x, int k) {
    int temp;
    if (k <= arr[x]) {
        printf("Il valore inserito è minore o uguale rispetto a quello esistente \n");
    } else {
        arr[x] = k;
        while ( x > 1 && (arr[x / 2] < arr[x]) ) {
            temp = arr[x];
            arr[x] = arr[x / 2];
            arr[x / 2] = temp;
            x = x / 2;
        }
    }
}

void heapInsert(int arr[], int key, int n) {
    arr[n] = -100;
    heapIncreaseKey(arr, n, key);
}

int heapExtractElem(int arr[], int k, int n) {
    int max;
    if (n == 1) {
        printf("Heap Underflow \n");
        return -1;
    } else if (k == n) {
        max = arr[k];
        //arr[k]=arr[n];

        //maxHeapify(arr,k,n);
        n = n - 1;
        return max;
    }
    return heapExtractElem(arr, k, n - 1);
}

int main() {
    setbuf(stdout, NULL);
    int i, n, scelta, max, key;
    
    // Testing 1/2
//    printf("Inserisci il numero di elementi dell'array (se scrivi 100)"
//            "ne viene creato uno di default con 16 elementi: \n");
//    scanf("%d", &n);
//    int arr[n];
//    for (i = 1; i <= n; i++) {
//        printf("Inserisci l'elemento %d\n", i);
//        scanf("%d", &arr[i]);
//    }
    
    // Testing 2/2
    n = 16;
    int arr[] = {0,100,50,80,30,40,70,25,10,15,42,74,55,66,32,12,85};
  
    buildHeap(arr, n);
   
    
    printf("\nScegli \n");
    printf("1. Heap Maximum \n");
    printf("2. Heap Extract Max \n");
    printf("3. Heap Increase Key \n");
    printf("4. Max Heap Insert \n");
    printf("5. Heap Extract element \n");
    scanf("%d", &scelta);

    switch (scelta) {
        case 1:
            // Heap Maximum
            max = heapMaximum(arr);
            printf("Maximum element = %d \n", max);
            break;

        case 2:
            // Heap Extract Max
            max = heapExtractMax(arr, n);
            n = n - 1;
            printf("Maximum element = %d \n", max);
            printf("Array aggiornato: \n");
            for (i = 1; i <= n; i++)
                printf("%d \n", arr[i]);
            break;

        case 3:
            // Heap Increase Key
            printf("Inserisci il valore della chiave : \n");
            scanf("%d \n", &key);
            printf("Inserisci l'indice della chiave: \n");
            scanf("%d", &i);
            heapIncreaseKey(arr, i, key);
            printf("Array aggiornato: \n");
            for (i = 1; i <= n; i++)
                printf("%d \n", arr[i]);
            break;
            
        case 4:
            // Max Heap Insert
            printf("Inserisci il valore della chiave: \n ");
            scanf("%d", &key);
            n = n + 1;
            heapInsert(arr, key, n);
            printf("Array aggiornato: \n");
            for (i = 1; i <= n; i++)
                printf("%d \n", arr[i]);
            break;

        case 5:
            // Heap Extract element
            printf("Inserisci la posizione della chiave: \n ");
            scanf("%d \n", &key);
            max = heapExtractElem(arr, key, n);
            maxHeapify(arr, key, n);
            n = n - 1;
            printf(" L'elemento estratto &egrave= %d \n", max);
            for (i = 1; i <= n; i++)
                printf("%d \n", arr[i]);
            break;
    }
}