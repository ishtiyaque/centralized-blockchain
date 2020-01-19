#include "utils.h"

int main(int argc, char *argv[]) {
	FILE *fp;
	
	int my_id;
	
	if(argc < 2) {
		printf("Missing Client id. Exiting...\n");
		exit(1);
	}
	my_id = atoi(argv[1]);
	if(!(fp = fopen("../config.txt", "r"))) {
		printf("config.txt NOT FOUND\n");
		exit(1);
	}
	fscanf(fp,"%s%d%d",server_ip, &portno, &num_client);
