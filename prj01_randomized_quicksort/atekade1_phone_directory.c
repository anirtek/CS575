#include <stdio.h>

int main(int argc, char **argv) {
	FILE *f = fopen(argv[1], "r"); // "r" for read	



    printf("I'm reading the file. . .\n");	
	return 0;
}

void create() {
}

void sort_contact(){
    //use randomized quick-sort algorithm for sorting
}

void search(char* name) {
    //use binary search method for quick searching
}

void delete(char* name){
    //use binary search menthod --> you may be able to use the void search()
    //method for this.
}

void insert(char* name, char* phone_number){
}
