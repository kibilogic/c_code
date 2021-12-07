#include <stdio.h>
#include <stdlib.h> // malloc

#define SIZE 100000

typedef struct snowflake_node{
	int snowflake[6];
	struct snowflake_node *next;

}snowflake_node;


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

void identify_identical(snowflake_node *snowflakes[]){

	snowflake_node *node1, *node2;

	int i;

	for(i=0; i<SIZE; i++){
		node1 = snowflakes[i];

		while(node1 != NULL){
			node2 = node1->next;

			while(node2 != NULL){
				if(are_identical(node1->snowflake, node2->snowflake)){
					printf("Twin snowflakes found. \n");
					return;
				}

				node2 = node2->next;
			}

			node1 = node1->next;
		}
	}

	printf("No two snowflakes are alike. \n");
}



int code(int snowflake[]){

	return(snowflake[0] + snowflake[1] + snowflake[2] + snowflake[3]
		+ snowflake[4] + snowflake[5]) % SIZE;
}



int main(void){

	static snowflake_node *snowflakes[SIZE] = {NULL};
	snowflake_node *snow;

	int n,i,j, snowflake_code;

	scanf("%d", &n);

	for(i=0;i<n;i++){

		snow = malloc(sizeof(snowflake_node));

		if(snow == NULL){

			fprintf(stderr, "malloc error \n");
			exit(1);
		}

		for(j=0; j<6; j++)
			scanf("%d", &snow->snowflake[j]);

		snowflake_code = code(snow->snowflake);
		snow->next = snowflakes[snowflake_code];
		snowflakes[snowflake_code] = snow;
	}

	identify_identical(snowflakes);


	return 0;
}
