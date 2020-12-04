#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

typedef struct Node{ //estrutura de cada n�
    struct Node *father; // N� pai do n� atual
    struct Node *right; //Filho a direita do pai
    struct Node *left; // Filho a esquerda do pai
    float value; // valor
    int depth;
} Node;

typedef struct Root{ //estrutura da raiz
    struct Node *first; //origem da arvore//
    int quantity; //quantidade de n�s
} Root;

void Initial (Root *x){ //Inicia a raiz
    x->quantity = 0; // zera seu tamanho
    x->first = NULL; // Faz o n� apontar para nulo
}

Node* LookingFor(Node *progenitor, float number){ //Fun��o para procurar o progenitor do novo n� inseridor
    if(progenitor->value > number){ //Se o valor do n� atual for maior do que o n�mero que ser� inserido a fun��o continua procurando � esquerda
        if(progenitor->left == NULL){ // Se o pr�ximo n� for nulo, achasse a condi��o de parada e retorna o N� atual
            return progenitor; // retorno
        }
        else{
            return LookingFor(progenitor->left, number); //Se n�o achar um valor nulo, a fun��o � chamada novamente
        }

    }
    else{ //Se o valor do n� atual for menor do que o n�mero que ser� inserido a fun��o continua procurando � esquerda
        if(progenitor->right == NULL){ // Se o pr�ximo n� for nulo, achasse a condi��o de parada e retorna o N� atual
            return progenitor; //retorno
        }
        else{
            return LookingFor(progenitor->right, number); //Se n�o achar um valor nulo, a fun��o � chamada novamente
        }
    }
}

void Insertion(Root *root, float number){ //Fun��o de inser��o
    Node *newChild = (Node*) calloc(1 , sizeof(Node)); //Aloca espa�o do novo n� da arvore
    newChild->value = number;  //Guarda o numero passado como par�metro dentro do N�

    root->quantity++; // Atualiza o tamanho da arvore
    if(root->first == NULL){ //CASO ESPECIAL 1: N�a tem nenhum n� na arvore
        root->first = newChild; //A raiz recebe o novo n�
        newChild->depth = 0;
    }
    else{ //Caso contr�rio, ser�o inseridos filhos na arvore
        Node *aux = LookingFor(root->first, number); // Usa a fun��o LookingFor() para achar o progenitor do newChild e manda seu endere�o par o aux
        if(aux->value > number){
            aux->left = newChild; //O filho a esquerda ser� o novo n�
        }
        else{
            aux->right = newChild; //O filho a direita ser� o novo n�
        }
        newChild->depth = aux->depth + 1;
        newChild->father = aux; //o filho recebe aux como pai
    }
}

void Death(Node *father){

    if(father == NULL){ //Se o n� for nulo n�o h� como prosseguir em profunidade, ent�o deve-se voltar para eliminar outros n�s
        return;
     }
     else{
        Death(father->left); //faremos a procura no laod esquerdo
        printf("O %,2f foi retirado da �rvore \n", father->value); //imprimiremos o valor desse n� para sair em ordem crescente
        Death(father->right); //procura na direita
        free(father);
        return;
     }
}

void Chase(Node *father, float number){ //Retirada de um n� e de seus filhos
    //Diferentemente das outras estruturas, a remo��o n�o resultar� em retorno

    if(father == NULL){ //Se chegar em um n� nulo
        printf("O valor nao existe! \n"); //printa que o alor n�o exista
        return;
    }
    else{
        if(father->value == number){ //Condi��o de parada, se acharmos o valor
            Death(father); //Inicia a elimini��o
            return;
        }
        else{
            if(father->value > number){
                Chase(father->left, number); //procura na esquerda se o number for menor que o n�
                return;
            }
            else{
                Chase(father->right, number);//procura na direita se o number for maior que o n�
                return;
            }
        }
    }
}

void ShowTree(Node *node){ //imprimi a arvore de  lado
    int contador = 0;

    if(node == NULL){ //condi��o de parada
        return;
    }
    else{
        ShowTree(node->right); //impimi primeiro os n�s direita. Fiz isso para que os n�s maior ficassem em cima e os menores embaixo
        while(contador < node->depth){// conta, de acordo com a profundidade , quantos espa�os deve dar
            printf("\t");
            contador++;
        }
        printf("%.2f \n", node->value); // imprimi o valor do n�
        ShowTree(node->left); //chama o n� da esquerda
    }


}

void main(){

    Root tree;
    Initial(&tree);

    float number;

    int confirmation = 10;
    int option = 10;

    while(confirmation != 0){
        printf("Digite 1 (um) para fazer uma nova operacao e 0 (zero) para encerrar as operacoes: \n");
        scanf("%d", &confirmation);
        if(confirmation == 1){
            do{
                printf(" Digite 0 (zero) para inserir um item na arvore\n Digite 1 (um) para retirar um item da arvore\n Digite 2 (dois) para visualizar a arvore \n Digite 3 (tres) para ver a quantidade de nos da arvore \n");
                scanf("%d", &option);
                if(option < 0 || option > 4){
                    printf("Digite apenas uma das opcoes solicitadas.\n");
                }
            }while(option < 0 || option > 4);

            switch (option){

            case 0:
                printf("Digite o valor que deseja inserir na fila: \n");
                scanf("%f", &number);
                Insertion(&tree, number);
            break;

            case 1:
                printf("Digite o valor que deseja retirar da arvore: \n");
                scanf("%f", &number);
                Chase(tree.first, number);
            break;

            case 2:
                ShowTree(tree.first);
            break;

            case 3:
                printf("A arvore tem %d nos\n",tree.quantity);
            break;
            }

        }
        else{
            if(confirmation == 0){
                printf("Sua arvore ficou da seguinte maneira: \n");
                ShowTree(tree.first);
            }
        }
    }
}
