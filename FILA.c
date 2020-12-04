#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

typedef struct Block { // elemento que forma a fila
    float value; //valor presente em cada bloco
    struct Block *next; //ponteiro que aponta para o proximo elemnto
} Block;

typedef struct Line { ////estrutura da fila
    int size; //quantidade de blocos da fila
    struct Block *front; // ponteiro para o primeiro elemento da fila
    struct Block *ending; //ponteiro para o ultimo elemento da fila
} Line;

void Initial(Line *x){ //inicializa a fila com valores nulos
    x->ending = NULL; // aponta o final da fila para NULL
    x->front = NULL; //aponta o começo da fila para NULL
    x->size = 0; //deixa a fila com tamanho 0 (zero)
}

int Insertion(Line *x, float number){ //inserção de um elemento  na fila
    Block *individual = (struct Block*) calloc(1 , sizeof(Block)); //Aloca na memoria o espaço de um bloco
    individual->value = number; //o valor desse bloco recebe o numero passado como parametro

    if(x->front == NULL && x->ending == NULL){ //se não tiver nenhum individuo na fila
        x->front = individual; //aponta o começo da fila para esse individuo
        x->ending = individual; //aponta o fim da fila para esse individuo
        x->size = 1; //coloca o tamanho da fila para 1
        return 1;
    }
    else{
        x->size++;
        x->ending->next = individual; //o ponteiro next do ultimo elemento aponta para o individuo
        x->ending = individual; //o novo individuo vira o o ultimo elemento
        return 1;
    }
    return 0; //retorno para ver erros
}

float Removal(Line *x){
    Block *individual;
    float number;
    if(x->front == NULL){ //se não tiver nenhum elemento na fila aparece a mensagem abaixo
        printf("A fila esta' vazia!");
        return -1;
    }
    else{
        if(x->ending == x->front){ //se só tiver um elemento na fila
            x->size--; //diminuimos o tamanho da fila
            number = x->front->value; // number receber o valor do bloco da fila
            individual = x->front; // individual recebe o bloco do front
            x->front = NULL; //o front vai apontar para null
            x->ending = NULL; //o final vai apontar para null
            free(individual); //libera o espaço de memoria alocado
            return number; //retorno o numero
        }
        else{ // caso front e ending sejam diferentes
            x->size--; //diminuimos o tamanho da fila
            number = x->front->value; //number recebe o valor do bloco
            individual = x->front; //individual recebe o bloco do front
            x->front = x->front->next; //o front aponta para o bloco seguinte
            free(individual); //liberamos a memorai alocada
            return number; //retornamos o numero que estava no bloco
        }
    }
}

int Size(Line *x){
    return x->size;
}

int ShowTheLine(Block *x){
    if(x->next == NULL){
        printf("%.2f \n", x->value);
        return 1;
    }
    else{
        printf("%.2f ", x->value);
        ShowTheLine(x->next);
        return 1;
    }
    return 0;
}

void main(){
    Line x;

    float number;

    Initial(&x);

    int confirmation = 10;
    int option = 10;

    while(confirmation != 0){
        printf("Digite 1 (um) para fazer uma nova operacao e 0 (zero) para encerrar as operacoes: \n");
        scanf("%d", &confirmation);
        if(confirmation == 1){
            do{
                printf(" Digite 0 (zero) para retirar um item da fila \n Digite 1 (um) para inserir um item na fila \n Digite 2 (dois) para visualizar a fila \n Digite 3 (tres) para ver o tamanho da fila \n");
                scanf("%d", &option);
                if(option < 0 || option > 4){
                    printf("Digite apenas uma das opcoes solicitadas.\n");
                }
            }while(option < 0 || option > 4);

            switch (option){
            case 0:
                printf("Valor devolvido: %.2f\n", Removal(&x));
            break;

            case 1:
                printf("Digite o valor que deseja inserir na fila: \n");
                scanf("%f", &number);
                Insertion(&x, number);
            break;

            case 2:
                ShowTheLine(x.front);
            break;

            case 3:
                printf("A fila tem %d individuos \n",Size(&x));
            break;
            }

        }
        else{
            if(confirmation == 0){
                printf("Sua fila ficou da seguinte maneira: \n");
                ShowTheLine(x.front);
            }
        }
    }
    printf("\n Terminou!");
}
