#include <stdio.h>

#define SIZE 100000


// moving right
int identical_right(int snow1[], int snow2[], int start){

	int offset;

	for(offset = 0; offset < 6; offset++){
		// wraps around behaviour for starting back at zero
		printf("right start  %d  start + offset %d   %d : %d\n", start , start+offset, snow1[offset] , snow2[(start + offset) % 6]);

		if(snow1[offset] != snow2[(start + offset) % 6]){
			//printf("right no match  %d - %d \n", snow1[offset] , snow2[(start + offset) % 6]);
			return 0;


		}
	}
	return 1;
}

// moving left
int identical_left(int snow1[], int snow2[], int start){
	int offset, snow2_index;

	for(offset=0; offset<6; offset++){
		snow2_index = start - offset;
		//printf("  left offset %d snow2_index %d  start %d   %d : %d \n", offset, snow2_index, start, snow1[offset], snow2[snow2_index]);

		// reset index
		if(snow2_index < 0)
			snow2_index = snow2_index + 6;

		printf("  left offset %d snow2_index %d  start %d   %d : %d \n", offset, snow2_index, start, snow1[offset], snow2[snow2_index]);
		
		if(snow1[offset] != snow2[snow2_index]){
			//printf("left no match %d - %d\n ", snow1[offset], snow2[snow2_index]);
			return 0;
		}
	}

	return 1;
}

// working with 6 integers at a time...each row is a snowflake
int are_identical(int snow1[], int snow2[]){

	int start;

	for(start=0; start < 6; start++){

		if(identical_right(snow1,snow2,start)){
			//printf("areIdentical right  %d \n", snow1[start]);
			return 1;
		}

		if(identical_left(snow1, snow2, start)){
			//printf("areIdentical left  %d \n", snow1[start]);
			return 1;
		}
	}

	return 0;
}

void identify_identical(int snowflakes[][6], int n){

	int i,j;

	for(i=0; i<n; i++){
		for(j=i+1; j<n; j++){
			printf("\n \n snowflakes[%d][%d]  %d %d\n",i,j, *snowflakes[i], *snowflakes[j] );
			if(are_identical(snowflakes[i], snowflakes[j])){
				printf("Twin snowflakes found. rows [%d,%d] \n", i,j ); //, *snowflakes[i], *snowflakes[j]
				return;
			}
		}
	}

	printf("No two snowflakes are alike. \n");
}

int compare(const void *first, const void *second){

	int i;
	const int *snowflake1 = first;
	const int *snowflake2 = second;

	if(are_identical(snowflake1, snowflake2))
		return 0;

	for(i=0; i<6; i++)
		if(snowflake1[i] < snowflake2[i])
			return -1;

		return 1;
}

int code(int snowflake[]){

	return(snowflake[0] + snowflake[1] + snowflake[2] + snowflake[3]
		+ snowflake[4] + snowflake[5]) % SIZE;
}



int main(void){

	static int snowflakes[SIZE][6];

	int n,i,j;

	scanf("%d", &n);

	for(i=0;i<n;i++)
		for(j=0; j<6; j++)
			scanf("%d", &snowflakes[i][j]);

	identify_identical(snowflakes, n);

	return 0;
}