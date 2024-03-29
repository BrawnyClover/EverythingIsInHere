// prj20191027.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable: 4996)

typedef struct node {
	int num;
	struct node *left, *right;
} Node;

node* stack[100];
int cnt = 0;

void init_node(node* root, int initNum) {
	root->num = initNum;
	root->left = root->right = NULL;
}

//insert a node into a BST
node* insert(node* root, int data) {
	if (root == NULL) {
		root = (node*)malloc(sizeof(Node));
		root->left = root->right = NULL;
		root->num = data;
		return root;
	}
	else {
		if (data < root->num)
			root->left = insert(root->left, data);
		else
			root->right = insert(root->right, data);
	}
	return root;
}

// translate a BST into an array
// 사용하지 않음
void traversal(node* root, int data[], int *p) {
	if (root != NULL) {
		traversal(root->left, data, p);
		data[*p] = root->num;
		(*p)++;
		traversal(root->right, data, p);
	}
}

// put nodes of tree into the stack
void traversal(node* root) {
	if (root != NULL) {
		stack[cnt++] = root;
		traversal(root->left);
		traversal(root->right);
	}
}

//sort the array in ascending order
void sort(int* num) {
	int size = sizeof(num) / sizeof(int);
	for (int i = 0; i < size; ++i) {
		for (int j = i + 1; j < size; ++j) {
			if (num[i] > num[j]) {
				int temp = num[i];
				num[i] = num[j];
				num[j] = temp;
			}
		}
	}
}

// third parameter is an array with front two arrays merged  
// 사용하지 않음
void mergeArray(int* num1, int* num2, int* num3) {
	int size1 = sizeof(num1) / sizeof(int);
	int size2 = sizeof(num2) / sizeof(int);
	
	for (int i = 0; i < size1; i++) {
		num3[i] = num1[i];
	}
	for(int i=0; i<size2; i++){
		num3[i+size1] = num2[i];
	}
	sort(num3);
}

// using merged array, make a BST
// 사용하지 않음
node* makePerfectTree(int* num, int start, int end) {
	if (start > end) return NULL;
	int mid = (start + end) / 2;
	node* root = (node*)malloc(sizeof(Node));
	insert(root, num[mid]);
	root->left = makePerfectTree(num, start, mid - 1);
	root->right = makePerfectTree(num, mid + 1, end);
}

// push nodes from stack to BST2
void mergeTree(node* bst2Root)
{
	int i;
	for (i = cnt - 1; i >= 0; i--) {
		insert(bst2Root, stack[i]->num);
	}
}

//put the average of two child nodes to parent node
node* avgNodes(node* root) {
	if (root == NULL) return root;

	if (root->left == NULL && root->right == NULL)
		root->num = 0;
	else if (root->left == NULL)
		root->num = root->right->num;
	else if (root->right == NULL)
		root->num = root->right->num;
	else
		root->num = (root->left->num + root->right->num) / 2;
	return root;

	avgNodes(root->left);
	avgNodes(root->right);
	return root;
}

// 사용하지 않음
void transform(node* root) {
	int n, i;
	int size = sizeof(root) / sizeof(node);
	int * arr = (int*)malloc(sizeof(int) * size);

	if (root == NULL) return;
	n = sizeof(root) / sizeof(node);
	i = 0;
	traversal(root, arr, &i);
	sort(arr);
	i = 0;
	// root = mergeTree(arr, 0, size);
}

void printBST(node* root, int level) {
	if (root == NULL) return;
	printf("LEVEL %d : %d\n", level, root->num);
	printBST(root->left, level + 1);
	printBST(root->right, level + 1);
}

int main(void) {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	node* BST1 = (node*)malloc(sizeof(Node));
	node* BST2 = (node*)malloc(sizeof(Node));
	node* BST3 = (node*)malloc(sizeof(Node));
	node* BT1 = (node*)malloc(sizeof(Node));
	
	init_node(BST3, 0);
	init_node(BT1, 0);

	int temp = 0;
	int check = 1, i = 0;
	const int bst1Size = 8;
	const int bst2Size = 8;

	scanf("%d", &temp);
	init_node(BST1, temp);
	for (int i = 1; i < bst1Size; i++) {
		scanf("%d", &temp);
		insert(BST1, temp);
	}
	traversal(BST1);

	scanf("%d", &temp);
	init_node(BST2, temp);
	for (int i = 1; i < bst2Size; i++) {
		scanf("%d", &temp);
		insert(BST2, temp);
	}

#pragma region InpurArea
	/*
	while (check == 1) {
		printf("\nEnter a number for BST1 : ");
		scanf("%d", &temp);
		insert(BST1, temp);

		printf("Want to continue inserting? (1 or 0) : ");
		scanf("%d", &check);
	}
	traversal(BST1, &arr1, &i);
	sort(&arr1);

	i = 0;
	check = 1;
	printf("\n=================================\n");
	while (check == 1) {
		printf("\nEnter a number for BST2 : ");
		scanf("%d", &temp);
		insert(BST2, temp);

		printf("Want to continue inserting? (1 or 0) : ");
		scanf("%d", &check);
	}
	traversal(BST2, &arr2, &i);
	sort(&arr2);
	*/
#pragma endregion
	
	mergeTree(BST2);

	BT1 = BST2;
	BT1 = avgNodes(BT1);

	int level = 0;
	printBST(BT1, level);

	system("pause");
	return 0;
}
