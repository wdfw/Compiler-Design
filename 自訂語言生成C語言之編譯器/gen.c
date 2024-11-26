#include<stdio.h>
#include<stdlib.h>
void transpose (int A[3][3]){
	int S[3][3] = {A[0][0] , A[0][1] , A[0][2] , A[1][0] , A[1][1] , A[1][2] , A[2][0] , A[2][1] , A[2][2]};
	printf("%s\n","matrix A is: ");
	printf("%d, %d, %d, %d, %d, %d, %d, %d, %d\n",A[0][0], A[0][1], A[0][2], A[1][0], A[1][1], A[1][2], A[2][0], A[2][1], A[2][2]);
	for(int i = 2;(i+1);(i=(i-1))){
		for(int j = 2;(j+1);(j=(j-1))){
			(A[i][j]=S[j][i]);
					}
	}
printf("%s\n","matrix of transpose A is: ");
	printf("%d, %d, %d, %d, %d, %d, %d, %d, %d\n",A[0][0], A[0][1], A[0][2], A[1][0], A[1][1], A[1][2], A[2][0], A[2][1], A[2][2]);
	return ;
	}
int main (){
	int A[3][3] = {1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9};
	transpose(A);
	printf("%s\n","transpose is a pointer operation, call function will pasaed it\'s pointer and change value like this:");
	printf("%d, %d, %d, %d, %d, %d, %d, %d, %d\n",A[0][0], A[0][1], A[0][2], A[1][0], A[1][1], A[1][2], A[2][0], A[2][1], A[2][2]);
	return 0;
	}
