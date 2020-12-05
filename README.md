# Algoritmos e Estrutura de Dados

 Este repositório contém códigos solicitados durante a graduação, na Unidade Curricular Algoritmo e Estrutura de Dados (I e II). Todos os algoritmos foram implementados em C. 
 

## Estruturas presentes no repositório até o dado momento: 

### - Pilha com Limite de Dados Armazenados
Nessa estrutura, os dados são enseridos de tal forma que só é possível acessar um por vez. Eles devem, obrigatoriamente, ser retornados na ordem inversa em que foram inseridos.
A quantidade de informações que podem ser armazenadas é passada pelo usuário antecipadamente.

Composto por duas *structs*:
- *Block*: Contém o valor do elemento (*float*) e um ponteiro que aponta para o próximo bloco da pliha.
- *Stack*: Simboliza a pilha como um todo. Ele guarda o tamanho da pilha (quantidade de elementos), a quantidade máxima permitida e um ponteiro para o topo da pilha. 

Conta com as seguintes funções:
- OverFlow(pilha (*struct Stack**)): Verifica se a pilha está cheia.
- Push(pilha (*struct Stack**), numero(*float*)): Aloca uma variável do tipo *Block** e faz ela recebe o topo da pilha como próximo elemento. Depois seu valor recebe o número e o topo da pilha aponta pra ele. Há um caso especial que deve ser levados em conta: Quando não há elemento na pilha.
- Pop(pilha (*struct Stack**)): Retorna o valor do topo da pilha. Atualiza o seu topo para o elemento seguinte e libera o espaço de memória da variável retornada.
- EmptyStack(pilha (*struct Stack**)): Verifica se a pilha está vazia.
- SeeTop(pilha (*struct Stack**)): Retorna o topo da pilha.
- Initial(pilha (*struct Stack**)): Inicial a pilha com tamanho 0 (zero) e o topo apontando para *null*.

### - Pilha sem Limite de Armazenamento
Nessa estrutura, os dados são inseridos de tal forma que só é possível acessar um por vez. Eles devem, obrigatoriamente, ser retornados na ordem inversa em que foram inseridos. Ou seja, o primeiro bloco que foi inserido só irá ser devolvido após todos os outros terem sido.
Nesse caso, não há um limite, imposto pelo software, de informações que possam ser armazenadas na estrutura.

Composto por duas *structs*:
- *Block*: Contém o valor do elemento (*float*) e um ponteiro que aponta para o próximo bloco da pliha.
- *Stack*: Simboliza a pilha como um todo. Ele guarda o tamanho da pilha (quantidade de elementos) e um ponteiro para o topo da pilha. 

Conta com as seguintes funções:
- Size(pilha (*struct Stack**)): Retorna o tamanho da pilha.
- Push(pilha (*struct Stack**), numero(*float*)): Aloca uma variável do tipo *Block** e ela passa a ter o topo da pilha como próximo elemento. Depois seu valor recebe o número e o topo da pilha aponta pra ele. Há um caso especial que deve ser levados em conta: Quando não há elemento na pilha.
- Pop(pilha (*struct Stack**)): Retorna o valor do topo da pilha. Atualiza o seu topo para o elemento seguinte e libera o espaço de memória da variável retornada.
- EmptyStack(pilha (*struct Stack**)): Verifica se a pilha está vazia.
- SeeTop(pilha (*struct Stack**)): Retorna o topo da pilha.
- Initial(pilha (*struct Stack**)): Inicial a pilha com tamanho 0 (zero) e o topo apontando para *null*.

### - Fila 
Nessa estrutura, os dados são enseridos de tal forma que só é possível acessar um por vez. Eles devem ser, obrigatoriamente, retornados na mesma ordem em que foram inseridos. Ou seja, a última informação a ser inserida só será acessada quando todas as outras já tiverem sido retornadas.

Composto por duas *structs*:
- *Block*: Contém o valor do elemento (*float*) e um ponteiro que aponta para o próximo bloco da fila.
- *Line*: Simboliza a fila como um todo. Ele guarda o tamanho da fila (quantidade de elementos) e um ponteiro para o inicio (*front*) e para o fim da fila (*ending*). 

Conta com as seguintes funções:
- Initial(fila (*struct Line**)): Inicia a fila com tamanho 0 (zero) e os ponteiros inicial e final apontando para *null*.
- Insertion(fila (*struct Line**), numero (*float*)): Aloca uma variável do tipo *Block** e seu valor receber o número. Faz o *ending* tê-lo como seu próximo elemento. Depois o final da fila passa a pontar para esse bloco. Há um caso especial que deve ser levados em conta: Quando não há elemento na fila.
- Removal(fila (*struct Line**)): Retorna o valor do *front* e faz o inicio da fila apontar para o próximo elemento.
- Size(*fila (struct Line**)): Retorna o tamanho da fila.
- ShowTheLine(fila (*struct Line**)): Imprime na tela todos os elementos da fila em sequência.

### - Lista Duplamente Encadeada
Nessa estrutura, os dados serão alocados de forma crescente e poderão ser retirados de duas formas, escolher uma posição ou um valor para retornar. 

Composto por duas *structs*:
- *Block*: Contém o valor do elemento (*float*) e dois ponteiros um para o bloco antecessor e outro para o sucessor.
- *List*: Simboliza a lista como um todo. Contém o tamanho dela e 3 (três) ponteiros, um aponta para o inicio da lista (*front*), o outro para final (*ending*) e o terceiro aponta para o último elemento inserido (*lastBlock*).

Conta com as seguintes funções:
- Initial(lista (*struct List**)): Incia a lista com tamanho 0 (zero) e todos os ponteiros apontando para *null*.
- GoRight(depois (*struct Block**), meio (*struct Block*)): Essa função foi implementada usando recursividade e tem o *lastBlock* como ponto de partida. Percorre a lista da esquerda para a direita até atingir a condição que o valor do "depois" é menor que o do "meio", o "meio" recebe o "depois como antecessor e os dois passam a ter o mesmo sucessor. Feito isso, o sucessor do "depois" começa a ser o "meio".

- GoLeft(depois (*struct Block**), meio (*struct Block**)): Percorre a lista da direita para a esquerda. Essa função foi implementada usando recursividade e tem o *lastBlock* como ponto de partida.
- Insertion(lista (*struct List**), numero (*float*)): Aloca uma variável do tipo *Block** e seu valor recebe o algarismo passado como parâmetro. Feito isso, compara o o numero dado com valor do *lastBlock**. Caso seja menor ou igual, chama o GoLeft() e caso seja maior chama o GoRight().
- 
- 
- 
- 
- 
- 
- 
- 
- 

### - Arvore Binaria
### - Arvore AVL (em desenvolvimento)
