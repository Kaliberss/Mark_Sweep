#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define max_heap 20
#define max_root 10
typedef struct Objeto{
    bool mark;
    int valor;
    struct Objeto* next;
}Objeto;

Objeto* heap[max_heap];
Objeto* root[max_root];
int heap_elements = 0;
int root_elements = 0;
Objeto* new_obj(int valor){
    if (heap_elements >= max_heap){
        printf ("Heap cheio");
        return NULL;
    }
    Objeto* obj = malloc(sizeof(Objeto));
    obj->mark = false;
    obj->valor = valor;
    obj->next = NULL;
    heap[heap_elements++] = obj;
    return obj;
}
void new_root(Objeto* obj){
    if (root_elements >= max_root){
        printf("Limite de raizes atingido");
        return;
    }
    root[root_elements++] = obj;
}
void mark(Objeto* obj){
    if (obj == NULL || obj->mark == true )
    return;
    obj->mark = true;
    mark(obj->next);
}
void sweep(){
    for (int i = 0; i < heap_elements; i++){
        if (heap[i]->mark == false){
            free(heap[i]);
            heap[i] = NULL;
        }
        else{
            heap[i]->mark = false;
        }
    }
}
void coleta(){
    for (int i = 0; i < root_elements; i++){
        mark(root[i]);
    }
    sweep();
}
void print(){
    printf("Heap:\n");
    for(int i = 0; i < heap_elements; i++){
        printf("Objeto %d: Valor: %d, Marcado: %d ",i+1,heap[i]->valor,heap[i]->mark);
    }
}
int main(){
    Objeto* a = new_obj(11);
    Objeto* b = new_obj(22);
    Objeto* c = new_obj(13);
    Objeto* d = new_obj(24);
    new_root(a);
    a->next = b;
    b->next = c;
    c->next = d;
    print();
    root[0] = NULL; //tira a raiz, fazendo com que todos os objetos sejam removidos da heap após a coleta
    coleta();
    printf("\n");
    print();
}