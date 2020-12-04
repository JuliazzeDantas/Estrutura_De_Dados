#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

typedef struct Node;

typedef struct Edge{ //Estrutura dos n
    struct Edge *next; //pr�ximo n�
    struct Edge *previous; //N� anterior
    struct Node *present; // Conte�do do n� atual
}Edge;

struct Node{
    float value; //valor do n�
    Edge *before; //N�s que apontam para ele
    Edge *after; //N�s que ele est� apontando
}Node;

typedef struct Origin{
    struct Node *first;
    int quantity;
}Origin;

typedef struct BlockList{
    float value;
    struct BlockList *next;
}BlockList;

typedef struct List{
    struct BlockList *first;
}List;

typedef struct Block { // elemento que forma a fila
    float value; //valor presente em cada bloco
    struct Block *next; //ponteiro que aponta para o proximo elemnto
    struct Block *previous; // ponteiro que aponta para o elemento anterior
} Block;

typedef struct List{ ////estrutura da fila
    int size; //quantidade de blocos da fila
    struct Block *lastBlock; //Ponteiro que apontara para o ultimo elemento inserido
    struct Block *front; // ponteiro para o primeiro elemento da fila
    struct Block *ending; //ponteiro para o ultimo elemento da fila
} List;

void GoRight(Block *after, Block *mid){ //Percorre a lista da esquerda para direita, procurando algum valor maior do que o passado na fun��o Listing() para inserir o elemento na posi��o adequada
    if(mid->value < after->value){ //se o valor do elemento for menor do que o do pr�ximo bloco
        mid->next = after; // O sucessor de mid ser� o after
        mid->previous = after->previous; // o anterior ao mid ser� quem � anterior ao after
        after->previous->next = mid; //o sucessor do "after->previous" � o mid
        after->previous = mid; //o atecessor do after passa a ser o mid
    }
    else{
        GoRight(after->next, mid); //continua a procura a direita, passando como referencia o sucessor do bloco visitado e o elemento que ser� encaixado
    }
}

void GoLeft(Block *before, Block *mid){ //Percorre a lista da direita para esquerda, procurando algum valor menor do que o passado na fun��o Listing() para inserir o elemento na posi��o adequada
    if(mid->value >= before->value){ //se o
        mid->previous = before; //o before vira o antecessor de mid
        mid->next = before->next; //o sucessor de mid aponta para o sucessor de before
        before->next->previous = mid; //o mid vira o antecessor de "before->next"
        before->next = mid; //mid vira o sucessor de before
    }
    else{
        GoLeft(before->previous, mid); //continua a procura a esquerda, passando como referencia o antecessor do bloco visitado e o elemento que ser� encaixado
    }
}

int Listing(List *x, float number){ //fun��o de inser��o de elemento
    Block *element = (Block*) calloc(1 , sizeof(Block)); //aloca um espa�o na memoria do tamanho da variavel do tipo Block
    element->value = number; // o valor do elemento recebe o numero passado como parametro

    if(x->front == NULL){ // CASO ESPECIAL NUMERO 1: se n�o tiver nenhum elemento na lista
        x->front = element; // o ponteiro do inicio aponta para o elemento
        x->ending = element; //o ponteiro do fim aponta para o elemento
        x->lastBlock = element;
        x->size = 1; //coloca o tamanho da lista igual a 1
    }
    else{
        x->size++; //coloco mais 1 no tamanho da lista
        if(x->front->value > number){ // CASO ESPECIAL NUMERO 2: o valor que ser� inserido � menor que o valor do primeiro elemento
            element->next = x->front; //o sucessor do elemento � o inicio da lista
            x->front->previous = element; //o elemento se torna o antecessor do inicio da lista
            x->front = element; //o elemento se torna o inicio da lista
            x->lastBlock = element; //ponteiro que aponta para o ultimo elemento inserido
        }
        else{
            if(x->ending->value <= number){ //CASO ESPECIAL NUMERO 3: o valor que ser� inserido � maior que o valor do ultimo elemento
                element->previous = x->ending; //o antecessor do elemento � o final da lista
                x->ending->next = element; // o elemento se torna o sucessor do final da lista
                x->ending = element; //o elemento se torna o final da lista
                x->lastBlock = element; //ponteiro que aponta para o ultimo elemento inserido
            }
            else{
                if(x->lastBlock->value > number){// o valor do ultimo elemento inserido for maior do que o atual
                    GoLeft(x->lastBlock, element); // fun��o para percorrer (<-) a lista e achar o local do elemento
                }
                else{
                    GoRight(x->lastBlock, element); // fun��o para percorrer (->) a lista e achar o local do elemento
                }
                x->lastBlock = element; //o elemento torna-se o ultimo a ser inserido
            }
        }
    }
}

Block* WalkList(Block *x, float number){ //fun��o para andar atrav�s da lista e devolver o bloco com o valor requisitado

    if(number == x->value){ // se acharmos o primeiro bloco com valor requisitado (condi��o de parada)
        return x;
    }
    else{//H� uma outra condi��o de parada aqui. a de certeza da inexistencia do valor
        if(x->next == NULL || x->next->value > number){ // caso tenhamos chegado ao final da fila e n�o encontramos o valor ou o proximo valor seja maior do que o requisitado
            printf("Nao existe esse valor dentro do grafo! \n");
            return NULL; //retornamos valor nulo
        }
        else{
            return WalkList(x->next, number); //recursividade
        }
    }
}

float RemovalListElement(List *x, float number){ // remove um elemento da lista, caso ele exista
    Block *element = WalkList(x->front, number); //fun��o que ir� devolver o bloco que desejamos utilizar
    Block *aux = element; //passar o bloco para uma variavel auxiliar para n�o perdermos seu valor durante a arruma��o de ponteiros

    if(element == NULL){
        printf("Nao existe esse valor dentro do grafo! \n");
        return -1;
    }
    else{ // se o elemento n�o for nulo
        x->size--; //atualizamos o tamanho da lista
        float value = aux->value; //value guarda o valor do aux, para que n�o se perca quando usarmos o free()
        if(x->front == x->ending){// CASO ESPECIAL 1: H� um elemento na lista
            x->front = NULL; //todos os ponteiros da lista recebem valores nulos pois n�o h� mais elementos nela
            x->ending = NULL;
            x->lastBlock == NULL;
        }
        else{
            if(element == x->front){// CASO ESPECIAL 2: O elemento retirado est� no come�o da lista
                if(element == x->lastBlock){ //Se esse elemento foi o ultimo a ser inserido, atualizamos o lasBlock para o bloco seguinte
                    x->lastBlock = x->front->next;
                }
                x->front->next->previous = NULL; //O antecessor do segundo elemento passar a ser NULL
                x->front = x->front->next; //atualizamos o inicio da lista
            }
            else{
                if(element == x->ending){
                    if(element == x->lastBlock){ //Se esse elemento foi o ultimo a ser inserido, atualizamos o lasBlock para o bloco anterior
                        x->lastBlock = x->ending->previous;
                    }
                    x->ending->previous->next = NULL; //O sucessor do meu penultimo elemento passa a ser o elemento nulo
                    x->ending = x->ending->previous; //Atualizamos o ultimo elemento da lista
                }
                else{
                    if(element == x->lastBlock){ //Se esse elemento foi o ultimo a ser inserido, atualizamos o lasBlock para o bloco seguinte
                        x->lastBlock = x->front->next;
                    }
                    element->previous->next = aux->next; //atualizamos o sponteiros do sucessor e do antecessor do elemento
                    element->next->previous = aux->previous;
                }
            }
        }

        free(aux); //libera espa�o de memoria
        printf("Valor devolvido: %.2f\n", value); //impirime o valor
        return value; //retorna o valor para caso precise fazer contas com ele
    }
    else{
        return -1;
    }
}

void InitialList(List *x){ //inicializa a fila com valores nulos
    x->ending = NULL; // aponta o final da fila para NULL
    x->front = NULL; //aponta o come�o da fila para NULL
    x->lastBlock = NULL; //faz o ponteiro de sinaliza��o apontar para NULL;
    x->size = 0; //deixa a fila com tamanho 0 (zero)
}

void Initial(Origin *x){
    x->first = NULL;
    x->quantity = 0;
}

void Insertion(Origin *origin, List *list, float number, float antecessor){
    origin->quantity++;
    Node node = (Node*) calloc(1, sizeof(Node));
    Listing(list, number);
    node->value = number;
    if(origin->first == NULL){
        origin->first = node;
    }
    else{
        if(WalkList(list, antecessor) == NULL){
            printf("O vertice pai � inexistente");
        }
        else{

        }
    }


}

void main(){

}
