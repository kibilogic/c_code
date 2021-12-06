#include <stdio.h>

/*
Find all pairs with the given sum in an array.

Given an unsorted integer array, find a pair with the given sum in it
*/

int findPair(int nums[], int n, int target){

	int count = 0; 

	for(int i=0; i<n-1; i++){

		for(int j=i+1; j<n; j++){

			if(nums[i] + nums[j]==target){

				printf("Pair found (%d, %d)\n", nums[i], nums[j]);
				count++;
				//return;
			}
		}
	}

	//printf("Pair not found\n");
	return count;
}

int main(void){

	int nums[] = {8,7,2,5,3,1};
	
	int target = 10;

	int n = sizeof(nums)/sizeof(nums[0]);

	int res = findPair(nums, n, target);

	printf("number of pairs found %d\n", res);

	return 0;
}