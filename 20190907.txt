#include <stdio.h>
#include <stdlib.h>
#define ARRAY_INDEX_OUT_OF_BOUNDS_EXCEPTION_VALUE 2147483646

int functionOne(int *a1, int *a2, int *a3, int n1, int n2, int n3);
int functionTwo(int *a1, int n1);

void quickSort(int left, int right, int *data);
void swap(int & value1, int & value2);

void printArray(int *array, int length);
double findMedian(int *a1, int n1);

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int i;
	int n1, n2, n3;
	int *a1;
	int *a2;
	int *a3;
	
	scanf("%d %d %d", &n1, &n2, &n3);
	
	a1 =(int*)malloc(sizeof(int) * n1);
	a2 =(int*)malloc(sizeof(int) * n2);
	a3 =(int*)malloc(sizeof(int) * n3);
	
	if(n2 + n3 != n1){
		printf("Inaccurate allocation happened, Please check input values again..");
	}
	
	for(i=0; i<n2; i++){
		scanf("%d", &a2[i]);
	}
	for(i=0; i<n3; i++){
		scanf("%d", &a3[i]);
	}
	
	printf("=====Start of Function One=====\n\n");
	functionOne(a1, a2, a3, n1, n2, n3);
	printf("\n=====End of Function One=====\n\n");
	
	printf("=====Start of Function Two=====\n\n");
	functionTwo(a1, n1);
	printf("\n=====End of Function Two=====\n\n");
	
	free(a1);
	free(a2);
	free(a3);
	return 0;
}

int functionOne(int *a1, int *a2, int *a3, int n1, int n2, int n3)
{
	int i;
	int idxOdd = 0;
	int idxEven = 0;
	for(i=0; i<n1; i+=2){
		if(idxEven == n2){
			a1[i] = ARRAY_INDEX_OUT_OF_BOUNDS_EXCEPTION_VALUE;
		}
		else{
			a1[i] = a2[idxEven++];
		}
		a1[i+1] = a3[idxOdd++];
	}
	
	printf("a1 : ");
	printArray(a1, n1);
	printf("a2 : ");
	printArray(a2, n2);
	printf("a3 : ");
	printArray(a3, n3);
	return 0;
}

int functionTwo(int *a1, int n1)
{
	quickSort(0, n1-1, a1);
	
	int medianIdx = 0;
	
	int isEven = n1 % 2==0 ? 1:0;
	
	if(isEven == 1){
		printf("a1 : ");
		printArray(a1, n1);
		
		findMedian(a1, n1);
		
		a1[n1/2] = 2147483646;
		a1[n1/2 - 1] = 2147483646;
		quickSort(0, n1 - 1, a1);
		n1 -= 2;
		
		printf("a1 : ");
		printArray(a1, n1);
		findMedian(a1, n1);
	}
	else{
		printf("a1 : ");
		printArray(a1, n1);
		
		findMedian(a1, n1);
		
		a1[(int)(n1/2)] = 2147483646;
		quickSort(0, n1 - 1, a1);
		n1 -= 1;
		
		printf("a1 : ");
		printArray(a1, n1);
		findMedian(a1, n1);
	}
	return 0;
}

void printArray(int *array, int length)
{
	int i;
	for(i=0; i<length; ++i){
		printf("%d ", array[i]);
	}
	printf("\n");
}

double findMedian(int *a1, int n1)
{
	int isEven = n1 % 2==0 ? 1:0;
	double median;
	if(isEven == 1){
		median = ((double)a1[n1/2]+(double)a1[n1/2 - 1])/2;
	}
	else{
		median = a1[(int)(n1/2)];
	}
	printf("Median : %.1f\n", median);
	return median;
}

void swap(int & value1, int & value2)
{
	int tmp = value1;
	value1 = value2;
	value2 = tmp;
}

void quickSort(int left, int right, int* data)
{
	int pivot = left;
	int j = pivot;
	int i;

	if (left < right) {
		for (i = left + 1; i <= right; i++) {
			if (data[i] < data[pivot]) {
				j++;
				swap(data[j], data[i]);
			}
		}
		swap(data[left], data[j]);
		pivot = j;

		quickSort(left, pivot-1, data);
		quickSort(pivot+1, right, data);
	}
}
