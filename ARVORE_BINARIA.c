#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

typedef struct Node{ //estrutura de cada nó
    struct Node *father; // Nó pai do nó atual
    struct Node *right; //Filho a direita do pai
    struct Node *left; // Filho a esquerda do pai
    float value; // valor
    int depth;
} Node;

typedef struct Root{ //estrutura da raiz
    struct Node *first; //origem da arvore//
    int quantity; //quantidade de nós
} Root;

void Initial (Root *x){ //Inicia a raiz
    x->quantity = 0; // zera seu tamanho
    x->first = NULL; // Faz o nó apontar para nulo
}

Node* LookingFor(Node *progenitor, float number){ //Função para procurar o progenitor do novo nó inseridor
    if(progenitor->value > number){ //Se o valor do nó atual for maior do que o número que será inserido a função continua procurando à esquerda
        if(progenitor->left == NULL){ // Se o próximo nó for nulo, achasse a condição de parada e retorna o Nó atual
            return progenitor; // retorno
        }
        else{
            return LookingFor(progenitor->left, number); //Se não achar um valor nulo, a função é chamada novamente
        }

    }
    else{ //Se o valor do nó atual for menor do que o número que será inserido a função continua procurando à esquerda
        if(progenitor->right == NULL){ // Se o próximo nó for nulo, achasse a condição de parada e retorna o Nó atual
            return progenitor; //retorno
        }
        else{
            return LookingFor(progenitor->right, number); //Se não achar um valor nulo, a função é chamada novamente
        }
    }
}

void Insertion(Root *root, float number){ //Função de inserção
    Node *newChild = (Node*) calloc(1 , sizeof(Node)); //Aloca espaço do novo nó da arvore
    newChild->value = number;  //Guarda o numero passado como parâmetro dentro do Nó

    root->quantity++; // Atualiza o tamanho da arvore
    if(root->first == NULL){ //CASO ESPECIAL 1: Nõa tem nenhum nó na arvore
        root->first = newChild; //A raiz recebe o novo nó
        newChild->depth = 0;
    }
    else{ //Caso contrário, serão inseridos filhos na arvore
        Node *aux = LookingFor(root->first, number); // Usa a função LookingFor() para achar o progenitor do newChild e manda seu endereço par o aux
        if(aux->value > number){
            aux->left = newChild; //O filho a esquerda será o novo nó
        }
        else{
            aux->right = newChild; //O filho a direita será o novo nó
        }
        newChild->depth = aux->depth + 1;
        newChild->father = aux; //o filho recebe aux como pai
    }
}

void Death(Node *father){

    if(father == NULL){ //Se o nó for nulo não há como prosseguir em profunidade, então deve-se voltar para eliminar outros nós
        return;
     }
     else{
        Death(father->left); //faremos a procura no laod esquerdo
        printf("O %,2f foi retirado da árvore \n", father->value); //imprimiremos o valor desse nó para sair em ordem crescente
        Death(father->right); //procura na direita
        free(father);
        return;
     }
}

void Chase(Node *father, float number){ //Retirada de um nó e de seus filhos
    //Diferentemente das outras estruturas, a remoção não resultará em retorno

    if(father == NULL){ //Se chegar em um nó nulo
        printf("O valor nao existe! \n"); //printa que o alor não exista
        return;
    }
    else{
        if(father->value == number){ //Condição de parada, se acharmos o valor
            Death(father); //Inicia a eliminição
            return;
        }
        else{
            if(father->value > number){
                Chase(father->left, number); //procura na esquerda se o number for menor que o nó
                return;
            }
            else{
                Chase(father->right, number);//procura na direita se o number for maior que o nó
                return;
            }
        }
    }
}

void ShowTree(Node *node){ //imprimi a arvore de  lado
    int contador = 0;

    if(node == NULL){ //condição de parada
        return;
    }
    else{
        ShowTree(node->right); //impimi primeiro os nós direita. Fiz isso para que os nós maior ficassem em cima e os menores embaixo
        while(contador < node->depth){// conta, de acordo com a profundidade , quantos espaços deve dar
            printf("\t");
            contador++;
        }
        printf("%.2f \n", node->value); // imprimi o valor do nó
        ShowTree(node->left); //chama o nó da esquerda
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
