/* by Felipe Gabriel
this code goes through the tree and prints the AVL tree by level (BFS)
this code have all the main functions off a AVL tree 
*/

#include <stdio.h>
#include <stdlib.h>


typedef struct node{
	int num;
	struct node* left;
	struct node* right;
}Node;

typedef Node* TreeBin;

TreeBin * newTree(){
	TreeBin* root = (TreeBin*) malloc(sizeof(TreeBin));
	if(root)
	    (*root) = NULL;

	return root;
}

void clearNode(Node* node){
	if(!node)	return;
	clearNode(node->left);
	clearNode(node->right);
	free(node);
	node = NULL;
}

void clearTree(TreeBin* Tree){
	if(!Tree)	return;
	clearNode(*Tree);
	free(Tree);
}

int isEmpty(TreeBin* Tree){
	if(!Tree)	return 1;
	if(!(*Tree))	return 1;
	return 0;
}

int countNode(TreeBin* Tree){
	int tleft, tright;

	if(isEmpty(Tree))	return 0;

	tleft = countNode(&((*Tree)->left));
	tright = countNode(&((*Tree)->right));

	return (tleft+tright+1);
}

int heightTree(TreeBin* Tree){
	int heightLeft, heightRight;

	if(isEmpty(Tree))	return -1;
	if(isEmpty(&((*Tree)->left)) && isEmpty(&((*Tree)->right)))	return 0;

	heightLeft = heightTree(&((*Tree)->left));
	heightRight = heightTree(&((*Tree)->right));

	if(heightLeft > heightRight)	return (heightLeft + 1);

	return (heightRight + 1);
}

//balancing functions
// [-1, 1] balanced tree
// [-2, 2] not balanced tree
int Balanced(TreeBin *Tree){
	return heightTree(&((*Tree)->left)) - heightTree(&((*Tree)->right));
}

void spinRight(TreeBin *Tree){
	Node *nod;
	nod = (*Tree)->left;
	(*Tree)->left = nod->right;
	nod->right = (*Tree);
	(*Tree) = nod;
}

void spinLeft(TreeBin *Tree){
	Node *nod;
	nod = (*Tree)->right;
	(*Tree)->right = nod->left;
	nod->left = (*Tree);
	(*Tree) = nod;
}

void balance(TreeBin *Tree, int n){
	int eb, it;

	if(!(*Tree))    return;

	eb = Balanced(Tree);
	if(eb >= -1 && eb <= 1)	return;

	else{

		if(n > (*Tree)->num){
			it = Balanced(&((*Tree)->right));

			if(eb <= -2){
				if(it == -1 || !it)	spinLeft(Tree);

				else{	
				    spinRight(&((*Tree)->right)); 
				    spinLeft(Tree);
				}
			}else{

				if(it == 1 || !it)	spinRight(Tree);

				else{	
				    spinLeft(&((*Tree)->right)); 
				    spinRight(Tree);

				}
			}
		}else{

			it = Balanced(&((*Tree)->left));

			if(eb <= -2){
				if(it == -1 || !it)	spinLeft(Tree);
				else{	
				    spinRight(&((*Tree)->left)); 
				    spinLeft(Tree);
				}
			}else{
				if(it == 1 || !it)	spinRight(Tree);
				else{	
				    spinLeft(&((*Tree)->left)); 
				    spinRight(Tree);

				}
			}
		}
		return;
	}
}

void insertTree(TreeBin* Tree, int n){
	Node *nod;
	if(!Tree)	return ;
	if(!(*Tree)){
		nod = (Node*)malloc(sizeof(Node));
		nod->num = n;
		nod->left = NULL;
		nod->right = NULL;
		(*Tree) = nod;
		return;
	}
	if(n > (*Tree)->num)	
	    insertTree(&((*Tree)->right), n);
	else	
	    insertTree(&((*Tree)->left), n);

	balance(Tree, n);
}

//Get the higher element of the left sub-tree
void subleftTree(TreeBin *Tree, TreeBin *next){
	Node *nod;
	if(!((*next)->right)){
		(*Tree)->num = (*next)->num;
		nod = (*next);
		(*next) = (*next)->left;
		free(nod);
	}else{
		subleftTree(Tree, &((*next)->right));
	}
}

void removeNode(TreeBin *Tree){
	Node *nod;
	if(!((*Tree)->left)){
		nod = (*Tree);
		(*Tree) = (*Tree)->right;
		free(nod);
	}else{
		if(!((*Tree)->right)){
			nod = (*Tree);
			(*Tree) = (*Tree)->left;
			free(nod);
		}else{
			subleftTree(Tree, &((*Tree)->left));
		}
	}
}

int removeTree(TreeBin* Tree, int n){
	Node *nod;
	if(isEmpty(Tree))	return 0;
	if((*Tree)->num == n){
		removeNode(Tree);
		balance(Tree, n);
		return 1;
	}
	if((*Tree)->num < n)	removeTree(&((*Tree)->right), n);
	else	removeTree(&((*Tree)->left), n);
	balance(Tree, n);
	return 1;
}

void printPreOrd(TreeBin Tree){
	if(isEmpty(&Tree))	return;
	printf("%d ", Tree->num);
	printPreOrd(Tree->left);
	printPreOrd(Tree->right);
}

void printEmOrd(TreeBin Tree){
	if(isEmpty(&Tree))	return;
	printEmOrd(Tree->left);
	printf("%d ", Tree->num);
	printEmOrd(Tree->right);
}

void printPosOrd(TreeBin Tree){
	if(isEmpty(&Tree))	return;
	printPosOrd(Tree->left);
	printPosOrd(Tree->right);
	printf("%d ", Tree->num);
}

/*queue functions
this part of the code will be some parts in Portuguese because there are many variables with similar names if i try to translate
*/

struct elemento{
	Node *ele;
	struct elemento *prox;
};

typedef struct elemento Elem;

typedef struct{
	Elem *inicio;
	Elem *final;
	int size;
}Fila;

//create a new queue
Fila * newFila(){
	Fila *f;
	f = (Fila*) malloc(sizeof(Fila));
	
	if(f){
		f->inicio = NULL;
		f->final = NULL;
		f->size = 0;
	}
	
	return f;
}

//verify the size of the queue, fila == queue
int tamanhoFila(Fila *f){
	if(!f){
		return 0;
	}	
	return f->size;
}

//insert in the queue
int insFila(Fila *f, Node *ele){
	Elem *no;
	
	if(!f){
		return 0; //queue dont exist
	} 
	no = (Elem*)malloc(sizeof(Elem));
	
	if(!no){
		return 0;	
	} 
	no->ele = ele;
	no->prox = NULL;
	if(f->final == NULL)	f->inicio = no;
	else	f->final->prox = no;
	f->final = no;
	f->size++;
	return 1;
}

//remove from queue
int rmvFila(Fila *f){
	Elem *no;
	if(!f){
		return 0; //queue dont exist
	}	
	if(!f->inicio){
		return 0;
	}	
	no = f->inicio;
	f->inicio = f->inicio->prox;
	if(!f->inicio){
		f->final = NULL;
	}	
	free(no);
	f->size--;
	return 1;
}

//clear queue
void limpaFila(Fila *f){
	if(!f->inicio){
		free(f);
	}	
	else{
		rmvFila(f);
		limpaFila(f);
	}
}

//
void larguraArv(TreeBin* Tree){
	int i, size;
	Fila *f;
	Elem *no;
	
	f = newFila();
	size = countNode(Tree);
	no = f->inicio;
	for(i = 0; i < size; i++){
		if(!no){
			insFila(f, (*Tree));
			no = f->inicio;
			continue;
		}
		if(no->ele->left)	insFila(f, no->ele->left);
		if(no->ele->right)	insFila(f, no->ele->right);
		no = no->prox;
	}
	
	size = tamanhoFila(f);
	for(i = 0; i < size; i++){
		printf("%d ", f->inicio->ele->num);
		rmvFila(f);
	}
	printf("\n");
	limpaFila(f);
}

int main(){
	int n, alt, op, num;
	TreeBin* Tree;
	
	Tree = newTree();
	printf("Insert the amount of numbers to be operated:\n");
	scanf("%d", &n);
	while(n--){
		printf("1- Insert numbers;\n2- Remove numbers;\n enter the number to be inserted or removed:\n");
		scanf("%d %d", &op, &num);
		if(op == 1)	insertTree(Tree, num);
		if(op == 2)	removeTree(Tree, num);
	}
	
	larguraArv(Tree);
	
	clearTree(Tree);
	return 0;
}
