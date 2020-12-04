#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

/*/**********************************************
Esse programa se trata de uma lista duplamente encadeada
a inserção será feita de forma ordenada
******************************************/

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

void Initial(List *x){ //inicializa a fila com valores nulos
    x->ending = NULL; // aponta o final da fila para NULL
    x->front = NULL; //aponta o começo da fila para NULL
    x->lastBlock = NULL; //faz o ponteiro de sinalização apontar para NULL;
    x->size = 0; //deixa a fila com tamanho 0 (zero)
}

void GoRight(Block *after, Block *mid){ //Percorre a lista da esquerda para direita, procurando algum valor maior do que o passado na função Insertion() para inserir o elemento na posição adequada
    if(mid->value < after->value){ //se o valor do elemento for menor do que o do próximo bloco
        mid->next = after; // O sucessor de mid será o after
        mid->previous = after->previous; // o anterior ao mid será quem é anterior ao after
        after->previous->next = mid; //o sucessor do "after->previous" é o mid
        after->previous = mid; //o atecessor do after passa a ser o mid
    }
    else{
        GoRight(after->next, mid); //continua a procura a direita, passando como referencia o sucessor do bloco visitado e o elemento que será encaixado
    }
}

void GoLeft(Block *before, Block *mid){ //Percorre a lista da direita para esquerda, procurando algum valor menor do que o passado na função Insertion() para inserir o elemento na posição adequada
    if(mid->value >= before->value){ //se o
        mid->previous = before; //o before vira o antecessor de mid
        mid->next = before->next; //o sucessor de mid aponta para o sucessor de before
        before->next->previous = mid; //o mid vira o antecessor de "before->next"
        before->next = mid; //mid vira o sucessor de before
    }
    else{
        GoLeft(before->previous, mid); //continua a procura a esquerda, passando como referencia o antecessor do bloco visitado e o elemento que será encaixado
    }
}

int Insertion(List *x, float number){ //função de inserção de elemento
    Block *element = (Block*) calloc(1 , sizeof(Block)); //aloca um espaço na memoria do tamanho da variavel do tipo Block
    element->value = number; // o valor do elemento recebe o numero passado como parametro

    if(x->front == NULL){ // CASO ESPECIAL NUMERO 1: se não tiver nenhum elemento na lista
        x->front = element; // o ponteiro do inicio aponta para o elemento
        x->ending = element; //o ponteiro do fim aponta para o elemento
        x->lastBlock = element;
        x->size = 1; //coloca o tamanho da lista igual a 1
    }
    else{
        x->size++; //coloco mais 1 no tamanho da lista
        if(x->front->value > number){ // CASO ESPECIAL NUMERO 2: o valor que será inserido é menor que o valor do primeiro elemento
            element->next = x->front; //o sucessor do elemento é o inicio da lista
            x->front->previous = element; //o elemento se torna o antecessor do inicio da lista
            x->front = element; //o elemento se torna o inicio da lista
            x->lastBlock = element; //ponteiro que aponta para o ultimo elemento inserido
        }
        else{
            if(x->ending->value <= number){ //CASO ESPECIAL NUMERO 3: o valor que será inserido é maior que o valor do ultimo elemento
                element->previous = x->ending; //o antecessor do elemento é o final da lista
                x->ending->next = element; // o elemento se torna o sucessor do final da lista
                x->ending = element; //o elemento se torna o final da lista
                x->lastBlock = element; //ponteiro que aponta para o ultimo elemento inserido
            }
            else{
                if(x->lastBlock->value > number){// o valor do ultimo elemento inserido for maior do que o atual
                    GoLeft(x->lastBlock, element); // função para percorrer (<-) a lista e achar o local do elemento
                }
                else{
                    GoRight(x->lastBlock, element); // função para percorrer (->) a lista e achar o local do elemento
                }
                x->lastBlock = element; //o elemento torna-se o ultimo a ser inserido
            }
        }
    }
}

float RemovalGoLeft(List *list, Block *x, int counter, int position){ // função para achar a posição que sera removida
     Block *aux;
    float number;
    if(position == 1){
        if(list->front == list->ending){ //CASO ESPECIAL 1: esxite só um elemento na fila
            aux = list->front; //passo o bloco pro aux
            number = aux->value; //guardo o valor do bloco
            list->front = NULL; //zero os ponteiros da lista
            list->ending = NULL;
            list->lastBlock = NULL;
            list->size--;//atualizo o tamanho
            free(aux); //limpa a memoria
            return number; //retorno o valor guardado
        }
        else{
            aux = list->front; //passo o bloco achado para o auxiliar
            number = aux->value; //guarda o valor do bloco;
            if(aux == list->lastBlock){ //se o ultimo elemento inserido for o que será retirado
                list->lastBlock = list->front->next; //atualizo o ponteiro q marca o ultimo elemento inserido
            }
            list->front = list->front->next; //atualizo o ponteiro de inicio da lista
            list->size--; //autalizo o tamanho
            free(aux); //libero a memoria
            return number; // retorno o valor guardado
        }
    }
    else{
        if(position == list->size){
            aux = list->ending;
            number = aux->value;
            if(aux == list->lastBlock){ //se o ultimo elemento inserido for o que será retirado
                list->lastBlock = list->ending->previous; //atualizo o ponteiro q marca o ultimo elemento inserido
            }
            list->ending = aux->previous;
            list->ending->next = NULL;
            list->size--;
            free(aux);
            return number;
        }
        else{
            if(counter == position){ // se o contador for igual aposição atual
                aux = x; // o auxiliar receber x
                number = aux->value;
                if(aux == list->lastBlock){ //se o ultimo elemento inserido for o que será retirado
                    list->lastBlock = aux->next; //atualizo o ponteiro q marca o ultimo elemento inserido
                }
                x->next->previous = aux->previous; // conectamos o antecessor de x e seu sucessor
                x->previous->next = aux->next; //com essa conexão tinramos x da lista
                free(aux); //damos free no aux ( o antigo x)
                return number; //retornamos o valor
            }
            else{
                if(x->next == NULL){
                    printf("Nao existe essa posicao na lista!");
                return 0;
                }
                else{
                    counter--; //diminuição no contador para andar para a esquerda
                    return RemovalGoLeft(list, x->previous, counter, position); //por recursividade a proxima função recebe o sucessor de x, um contador atualizado e a mesma posição
                }
            }
        }
    }
}


float RemovalGoRight(List *list, Block *x, int counter, int position){// função para achar a posição que sera removida
    Block *aux;
    float number;
    if(position == 1){
            if(list->front == list->ending){ //CASO ESPECIAL 1: esxite só um elemento na fila
                aux = list->front; //passo o bloco pro aux
                number = aux->value; //guardo o valor do bloco
                list->front = NULL; //zero os ponteiros da lista
                list->ending = NULL;
                list->lastBlock = NULL;
                list->size--;//atualizo o tamanho
                free(aux); //limpa a memoria
                return number; //retorno o valor guardado
            }
            else{
                aux = list->front; //passo o bloco achado para o auxiliar
                number = aux->value; //guarda o valor do bloco
                if(aux == list->lastBlock){ //se o ultimo elemento inserido for o que será retirado
                    list->lastBlock = list->front->next; //atualizo o ponteiro q marca o ultimo elemento inserido
                }
                list->front = list->front->next; //atualizo o ponteiro de inicio da lista
                list->front->previous = NULL;
                list->size--; //autalizo o tamanho
                free(aux); //libero a memoria
                return number; // retorno o valor guardado
            }
    }
    else{
        if(position == list->size){
            aux = list->ending;
            number = aux->value;

            if(aux == list->lastBlock){ //se o ultimo elemento inserido for o que será retirado
                list->lastBlock = list->ending->previous; //atualizo o ponteiro q marca o ultimo elemento inserido
            }
            list->ending = aux->previous; //atualizo os ponteiro da lista
            list->ending->next = NULL;
            list->size--;
            free(aux);
            return number;
        }
        else{
            if(counter == position){ // se o contador for igual aposição atual
                aux = x; // o auxiliar receber x
                number = aux->value;
                if(aux == list->lastBlock){ //se o ultimo elemento inserido for o que será retirado
                    list->lastBlock = aux->next; //atualizo o ponteiro q marca o ultimo elemento inserido
                }
                x->next->previous = aux->previous; // conectamos o antecessor de x e seu sucessor
                x->previous->next = aux->next; //com essa conexão tinramos x da lista
                free(aux); //damos free no aux ( o antigo x)
                return number; //retornamos o valor
            }
            else{
                if(x->next == NULL){
                    printf("Nao existe essa posicao na lista!");
                return 0;
                }
                else{
                    counter++; //diminuição no contador para andar para a esquerda
                    return RemovalGoRight(list ,x->next, counter, position); //por recursividade a proxima função recebe o sucessor de x, um contador atualizado e a mesma posição
                }
            }
        }
    }
}

float RemovalPosition(List *x, int position){ //função para remover um elemento da lista usando sua posição
    float number;
    if(x->front == NULL){
        printf("A lista ja' esta' vazia!\n");
        return -1;
    }
    else{
        if(x->size < position){ //se a posição passada for maior do que ok tamanho total, acusamos um erro
            printf("A posicao requisitada nao existe \n");
            return -1;
        }
        else{
            if(position >= (x->size / 2)){ //dividimos na metade para "otimizar" a busca. No pior caso, percorreremos metade da pilha e não ela inteira
                number = RemovalGoRight(x, x->front, 1, position);
                printf("Valor devolvido: %.2f\n", number);
               return number;
            }
            else{
                number = RemovalGoLeft(x, x->ending, x->size, position);
                printf("Valor devolvido: %.2f\n", number);
                return number;
            }
        }
    }
}

Block* Walk(Block *x, float number){ //função para andar através da lista e devolver o bloco com o valor requisitado

    if(number == x->value){ // se acharmos o primeiro bloco com valor requisitado (condição de parada)
        return x;
    }
    else{//Há uma outra condição de parada aqui. a de certeza da inexistencia do valor
        if(x->next == NULL || x->next->value > number){ // caso tenhamos chegado ao final da fila e não encontramos o valor ou o proximo valor seja maior do que o requisitado
            printf("Nao existe esse valor dentro da lista! \n");
            return NULL; //retornamos valor nulo
        }
        else{
            return Walk(x->next, number); //recursividade
        }
    }
}

float RemovalElement(List *x, float number){ // remove um elemento da lista, caso ele exista
    Block *element = Walk(x->front, number); //função que irá devolver o bloco que desejamos utilizar
    Block *aux = element; //passar o bloco para uma variavel auxiliar para não perdermos seu valor durante a arrumação de ponteiros

    if(element != NULL){ // se o elemento não for nulo
        x->size--; //atualizamos o tamanho da lista
        float value = aux->value; //value guarda o valor do aux, para que não se perca quando usarmos o free()
        if(x->front == x->ending){// CASO ESPECIAL 1: Há um elemento na lista
            x->front = NULL; //todos os ponteiros da lista recebem valores nulos pois não há mais elementos nela
            x->ending = NULL;
            x->lastBlock == NULL;
        }
        else{
            if(element == x->front){// CASO ESPECIAL 2: O elemento retirado está no começo da lista
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

        free(aux); //libera espaço de memoria
        printf("Valor devolvido: %.2f\n", value); //impirime o valor
        return value; //retorna o valor para caso precise fazer contas com ele
    }
    else{
        return -1;
    }
}


void ShowList(Block *element){ //função para mostrar toda a fila
    if(element->next == NULL){ //se o proximo elemento for nulo cai
        printf("%.2f \n",element->value); //implrime o valor do elemento
        return;
    }
    else{
        printf("%.2f  ",element->value); //implrime o valor do elemento
        ShowList(element->next); //chama a função de novo por recursividade
    }
}

void main(){
    List x;

    float number;
    int position;

    Initial(&x);

    int confirmation = 10;
    int option = 10;

    while(confirmation != 0){
        printf("Digite 1 (um) para fazer uma nova operacao e 0 (zero) para encerrar as operacoes: \n");
        scanf("%d", &confirmation);
        if(confirmation == 1){
            do{
                printf(" Digite 0 (zero) para inserir um item na lista \n Digite 1 (um) para retirar um item da lista por posicao \n Digite 2 (dois) para retirar um item da lista \n Digite 3 (tres) para visualizar a lista \n");
                scanf("%d", &option);
                if(option < 0 || option > 4){
                    printf("Digite apenas uma das opcoes solicitadas.\n");
                }
            }while(option < 0 || option > 4);

            switch (option){
            case 0:
                printf("Digite o valor que deseja inserir na lista: \n");
                scanf("%f", &number);
                Insertion(&x, number);
            break;

            case 1:
                printf("Digite a posicao que deseja retirar: \n");
                scanf("%d", &position);
                RemovalPosition(&x, position);
            break;

            case 2:
                printf("Digite o valor que deseja retirar da lista: \n");
                scanf("%f", &number);
                RemovalElement(&x, number);
            break;

            case 3:
                ShowList(x.front);
            break;
            }

        }
        else{
            if(confirmation == 0){
                printf("Sua lista ficou da seguinte maneira: \n");
                ShowList(x.front);
            }
        }
    }
    printf("\n Terminou!");
}
