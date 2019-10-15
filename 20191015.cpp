#include<stdio.h>
#include<stdlib.h>
#include <algorithm>

typedef struct node {
	int num, sum; 
	struct node *left, *right; 
} Node;

Node* nums_in(Node* root, int data) {
	if (root == NULL)
	{
		root = (Node*)malloc(sizeof(Node));
		root->left = root->right = NULL;
		root->num = data;
		return root;
	}
	else
	{
		if (root->num > data)
			root->left = nums_in(root->left, data);
		else
			root->right = nums_in(root->right, data);
	}
	return root;
}

Node* sums_in(Node* root) {
	if (root->left == NULL && root->right == NULL)
		root->sum = 0;
	else if (root->left == NULL)
		root->sum = root->right->num;
	else if (root->right == NULL)
		root->sum = root->left->num;
	else
		root->sum = root->left->num + root->right->num; 

	return root; 
}

void BST_ChildValue(Node * node)
{
	if(node == NULL){
		return;
	}
	node = sums_in(node);
	BST_ChildValue(node->left);
	BST_ChildValue(node->right);
}

void printBST(Node *root, int level) {
	if (root == NULL) return ; 
	printf("%d : (%d, %d) c:%d l:%d r:%d\n", level, root->num, root->sum, root, root->left, root->right);
	printBST(root->left, level+1);
	printBST(root->right, level+1); 
}

int main(void) {
	freopen("output.txt","w",stdout);
	const int size = 9;
	int num[size] = {0};
	Node* root = NULL;
	int level = 0;

	// std::sort(num, num+size);
	
	//Fill the array with 9 random number.
	srand(7);     //seed
	printf("Array: "); 
	for (int i = 0; i < size; i++) {
		int j = rand();
		//num[i] = j;
		printf("%d ", num[i]);
	}
	printf("\n");
	
	//Sort the array
	for (int k = 0; k < size; k++) {
		for (int j = 0; j < size; j++) {
			if (num[j] > num[j + 1]) {
				int temp = num[j];
				num[j] = num[j + 1];
				num[j + 1] = temp;
			}
		}
	}

	//Make BST
	root = nums_in(root, num[4]);
	root = nums_in(root, num[1]);
	root = nums_in(root, num[0]);
	root = nums_in(root, num[2]);
	root = nums_in(root, num[3]);
	root = nums_in(root, num[6]);
	root = nums_in(root, num[5]);
	root = nums_in(root, num[7]);
	root = nums_in(root, num[8]);
	BST_ChildValue(root);
	printBST(root, level);

	system("pause");
	return 0;
}