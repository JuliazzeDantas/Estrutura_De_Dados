#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

typedef struct Block { // Estrutura de cada elemento (bloco) da pilha
    float value; //Valor que ser� inserido na pilha
    struct Block *next; //polnteiro que aponta para o proximo elemento da pilha
} Block;

typedef struct Stack { //A estrutura da pilha. Basta apontar para o o topo dela e o resto est� ligado
    int size; //tamanho atual da pilha
    struct Block *top; // ponteiro que apointa para o topo da pilha
} Stack;

int Size(Stack *prime){ //fun��o para mostarr a quantidade blocos na pilha
    return prime->size;
}

int Push(struct Stack *prime, float number){ //fun��o para colocar um novo elemento
    Block *x = (struct Block*) calloc(1 , sizeof(struct Block)); //reserva um espa�o da memoria para um novo bloco
    x->value = number; //o valor do bloco recebe o numero passado como parametro pela fun��o

    if(prime->size == 0){ //caso esse seja o primeiro elemento da pilha
        x->next = NULL; //// o ponteiro next aponta para NULL, pois n�o h� outro bloco para apontar
        prime->top = x; //a pilha designa esse elemento como o novo topo
        prime->size = 1; // incrementa 1 no tamanho atual da pilha
    }
    else{ //casso esse n�o seja o primeiro elemento da pilha
        x->next = prime->top;  //o ponteiro next recebe o bloco que est� no topo da pilha
        prime->top = x; //o topo da pilha � atualizado e passa a apontar para o bloco que alocamos espa�o no come�o da fun��o
        prime->size++; //icrementamos o tamanhos da pilha em +1
    }
    return 1;
}

int EmptyStack(struct Stack *prime){ // Verifica se a pilha est� vazia
    if(prime->size <= 0){
        return 1; //Caso esteja vazia retorna 1 (um)
    }
    else{
        return 0; //Caso esteja vazia retorna 0 (zero)
    }
}

float Pop(struct Stack *prime){ //Retira um elemento da pilha
    float number; // Variavel auxiliar para guarda o valor da pilha
    Block *aux = prime->top; // Variavel auxiliar que receber� o atual topo para desalocar a memoria
    if(EmptyStack(prime)){ //Verifica se a pilha est� vazia
        printf("Error! A estrutura esta' vazia\n"); //Emite uma mensagem de erro, caso a pilha esteja vazia
        return 0;
    }
    else{ //Caso nao esteja vazia
        number = prime->top->value; //guarga o valor da pilha em um auxiliar
        prime->top = prime->top->next; // atualiza o topo dapilha
        prime->size--; //diminui o tamanho da pilha
        free(aux); //elimina a memoria alocada para o bloco
        return number; //retorna o numero dentro da pilha
    }
    return -1;//retorno para verifica��o de erro caso seja um valor discordante
}

float SeeTop(struct Stack *prime){ //ver o topo da pilha sem retirar o elemento
    return prime->top->value; // retorno o valor do topo da pilha
}

void Initial(struct Stack *prime){ //inicia a pilha com valores nulos
    prime->size = 0; //zera o tamanho dela
    prime->top = NULL; //aponta para null
}

//Para treinar, a fun��o abaixo foi feita de modo recursivo
void ShowStack(Block *block){ // fun��o para mostrar toda a pilha
    if(block->next == NULL){ //se o proximo bloco for igual a null, ent�o cessamos a recursividades e printamos o valor do bloco
        printf("%.2f \n", block->value); // mostra o valor do bloco na tela
    }else{ // caso o proximo valor n�o seja null, iremos continuar a recurs�o
        printf("%.2f \n", block->value); // para imprimir do topo para a base, imprimimos o valor desse bloco antes de ir para a proxima recursao
        ShowStack(block->next); // continua��o da recursao
    }
}

void main(){// inicio da main
    Stack x; //declara a pilha

    float number; //variavel para guardar os numeros que ser�o inseridos

    Initial(&x); // inicia��o da pilha

    int confirmation = 10;  //valor aleat�rio diferente de 10 para entrar no loop
    int option = 10;

    while(confirmation != 0){ // loop de intera��o com o usuario
        printf("Digite 1 (um) para fazer uma nova operacao e 0 (zero) para encerrar as operacoes: \n");
        scanf("%d", &confirmation); //L� a confirma��o
        if(confirmation == 1){
            do{ //Loop para fazer o usuario digitar as op��es dadas
                printf(" Digite 0 (zero) para retirar um item da pilha \n Digite 1 (um) para inserir um item na pilha \n Digite 2 (dois) para visualizar o topo da pilha \n Digite 3 (tres) para ver se a pilha esta vazia \n Digite 4 (quatro) para ver o tamanho da pilha \n Digite 5 (cinco) para ver a pilha \n");
                scanf("%d", &option);
                if(option < 0 || option > 5){
                    printf("Digite apenas uma das opcoes solicitadas.\n");
                }
            }while(option < 0 || option > 5);

            switch (option){
            case 0:
                printf("Valor devolvido: %.2f\n", Pop(&x));
            break;

            case 1:
                printf("Digite o valor que deseja inserir na pilha: \n");
                scanf("%f", &number);
                Push(&x, number);
            break;

            case 2:
                printf("Valor devolvido: %.2f\n",SeeTop(&x));
            break;

            case 3:
                if(EmptyStack(&x) == 1){
                    printf("A pilha esta vazia \n");
                }
                else{
                    printf("A pilha tem %d elementos \n", x.size);
                }
            break;

            case 4:
                printf("A pilha tem %d blocos \n ", Size(&x));
            break;

            case 5:
                ShowStack(x.top);
            break;
            }

        }
        else{
            if(confirmation == 0){
                printf("Sua pilha ficou da seguinte maneira: \n");
                ShowStack(x.top);
            }
        }
    }
    printf("Terminou!");
}
