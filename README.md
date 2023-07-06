# Philosophers
Ce projet est une introduction au threading et aux processus, et sur comment travailler sur le même espace mémoire.

Introduction aux threads en langage C avec exemples

Introduction :
Les threads sont des séquences d'exécution concurrentes qui permettent de réaliser des tâches en parallèle dans un programme. En langage C, la bibliothèque `<pthread.h>` fournit des fonctions pour gérer les threads. Dans cette synthèse, nous explorerons les concepts clés des threads en répondant à différentes questions et en fournissant des exemples.

1. Qu'est-ce qu'un thread ?
Les threads sont des séquences d'exécution concurrentes qui permettent de réaliser des tâches en parallèle dans un programme. Les threads partagent une même mémoire et peuvent accéder directement aux variables partagées. En langage C, la bibliothèque <pthread.h> fournit des fonctions pour gérer les threads. En revanche, les pipes sont des mécanismes de communication interprocessus qui permettent à deux processus distincts de communiquer en utilisant un canal unidirectionnel. Contrairement aux threads, les processus communicants via un pipe n'ont pas de mémoire partagée directe et doivent utiliser les opérations d'écriture et de lecture pour échanger des données via le pipe.

Veuillez noter que bien que les pipes et les threads soient des mécanismes de programmation concurrente, ils diffèrent dans la façon dont ils gèrent la communication et la mémoire partagée. Les threads peuvent accéder directement aux variables partagées en utilisant la mémoire partagée, ce qui nécessite une synchronisation appropriée pour éviter les conditions de course. En revanche, les pipes utilisent un canal de communication unidirectionnel pour envoyer et recevoir des données entre des processus distincts, sans partager directement la mémoire.

2. Comment créer et exécuter un thread en C ?
En C, nous utilisons la fonction `pthread_create` pour créer un thread. Cette fonction prend plusieurs arguments, dont un pointeur vers la structure `pthread_t` pour identifier le thread, un pointeur vers une fonction qui sera exécutée par le thread, et éventuellement des arguments à passer à cette fonction. Ensuite, nous utilisons `pthread_join` pour attendre la fin du thread avant de poursuivre l'exécution du programme.

Exemple :
```c
#include <stdio.h>
#include <pthread.h>

void* thread_function(void* arg) {
    int thread_id = *((int*) arg);
    printf("Hello from thread %d\n", thread_id);
    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2;
    int id1 = 1, id2 = 2;

    pthread_create(&thread1, NULL, thread_function, (void*) &id1);
    pthread_create(&thread2, NULL, thread_function, (void*) &id2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
```

3. Qu'est-ce qu'un data race et comment l'éviter ?
Un data race se produit lorsqu'au moins deux threads accèdent simultanément à une même variable ou une même zone de mémoire partagée, avec au moins un accès en écriture, sans mécanisme de synchronisation approprié. Pour éviter les data races, nous utilisons des mécanismes de synchronisation tels que les mutex, les verrous ou les primitives de synchronisation. Ces mécanismes garantissent l'exclusion mutuelle, permettant à un seul thread d'accéder à la ressource partagée à la fois.

4. Qu'est-ce qu'un mutex et comment l'utiliser ?
Un mutex (verrou mutualiste) est un mécanisme de synchronisation utilisé pour éviter les conflits de données entre les threads. Il permet de garantir l'accès exclusif à une ressource partagée. En C, nous utilisons la bibliothèque `<pthread.h>` pour gérer les mutex. Les étapes pour utiliser un mutex incluent la déclaration et l'initialisation du mutex avec `pthread_mutex_init`, le verrouillage du mutex avec `pthread_mutex_lock`, le déverrouillage du mutex avec `pthread_mutex_unlock`, et enfin, la destruction du mutex avec `pthread_mutex_destroy`.

Exemple :
```c
#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;
int counter = 0;

void* increment(void* arg) {
    pthread_mutex_lock(&

mutex);
    counter++;
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2;

    pthread_mutex_init(&mutex, NULL);

    pthread_create(&thread1, NULL, increment, NULL);
    pthread_create(&thread2, NULL, increment, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&mutex);

    printf("Counter value: %d\n", counter);

    return 0;
}
```

6. Comment retourner une valeur à partir d'un thread ?
En C, un thread ne peut pas retourner directement une valeur comme le ferait une fonction classique. Cependant, il existe un moyen de récupérer une valeur de retour à partir d'un thread en utilisant un pointeur passé en argument lors de la création du thread.

Pour retourner une valeur à partir d'un thread :
- Déclarez une variable pour stocker la valeur de retour dans la fonction `main`.
- Passez un pointeur vers cette variable en tant qu'argument lors de la création du thread.
- Utilisez `pthread_exit` pour retourner une valeur spécifique à partir du thread.
- Récupérez la valeur de retour à l'aide de `pthread_join` en utilisant un cast approprié.

Voici un exemple pour illustrer la façon de retourner une valeur à partir d'un thread :

```c
#include <stdio.h>
#include <pthread.h>

void* compute_sum(void* arg) {
    int* values = (int*)arg;
    int a = values[0];
    int b = values[1];
    int sum = a + b;
    pthread_exit((void*)sum);
}

int main() {
    pthread_t thread;
    int values[2] = {3, 4};
    int result;

    pthread_create(&thread, NULL, compute_sum, (void*)values);
    pthread_join(thread, (void**)&result);

    printf("Sum: %d\n", result);

    return 0;
}
```

Dans cet exemple, nous créons un thread qui calcule la somme de deux entiers passés en tant qu'argument. La fonction `compute_sum` reçoit un pointeur vers un tableau `values` contenant les deux entiers à additionner. Le résultat de la somme est retourné à l'aide de `pthread_exit`.

Dans la fonction `main`, nous déclarons une variable `result` pour stocker la valeur de retour du thread. Nous passons l'adresse de `values` lors de la création du thread et utilisons `pthread_join` pour attendre la fin du thread et récupérer la valeur de retour. La valeur est stockée dans `result` en utilisant un cast `(void**)`.

Ainsi, en utilisant un pointeur pour récupérer la valeur de retour, nous pouvons obtenir des résultats calculés dans le thread et les utiliser dans la fonction principale.

N'hésite pas à me poser des questions supplémentaires si nécessaire !

5. Comment passer des arguments à un thread ?
Pour passer des arguments à un thread, nous pouvons utiliser une structure pour regrouper les données à transmettre. Nous définissons une structure qui contient les membres nécessaires pour représenter les données. Avant de créer le thread, nous allouons dynamiquement une instance de cette structure, l'initialisons avec les valeurs souhaitées, puis passons un pointeur vers la structure en tant qu'argument lors de la création du thread. Dans la fonction exécutée par le thread, nous convertissons le pointeur générique en un pointeur vers la structure pour accéder aux données.

Exemple :
```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int arg1;
    char arg2;
} ThreadArgs;

void* thread_function(void* arg) {
    ThreadArgs* args = (ThreadArgs*)arg;
    int value1 = args->arg1;
    char value2 = args->arg2;

    printf("Thread received arguments: %d, %c\n", value1, value2);
    pthread_exit(NULL);
}

int main() {
    pthread_t thread;
    ThreadArgs* args = (ThreadArgs*)malloc(sizeof(ThreadArgs));
    args->arg1 = 42;
    args->arg2 = 'A';

    pthread_create(&thread, NULL, thread_function, (void*)args);
    pthread_join(thread, NULL);

    free(args);

    return 0;
}
```

Conclusion :
Les threads en langage C permettent d'exploiter le parallélisme et d'effectuer des tâches concurrentes dans un programme. Les mutex sont utilisés pour éviter les conflits de données entre les threads. En passant des arguments aux threads, nous pouvons communiquer des données spécifiques à chaque thread. En comprenant ces concepts et en utilisant les bonnes pratiques de synchronisation, nous pouvons créer des programmes multithreadés efficaces et sans conflits.

N'hésite pas à explorer davantage les fonctionnalités et les possibilités offertes par les threads en C pour enrichir tes compétences en programmation multithreadée.