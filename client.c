#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 8080

int main(int argc, char* argv[]) {
	int new_socket = 0;
	long valread;
	struct sockaddr_in serv_addr;
	char *request = "Simple GET request";
	char buffer[1024] = {0};
	
	if((new_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\nSocket creation error\n");
		return -1;
	}
	
	memset(&serv_addr, '0', sizeof(serv_addr));
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
		printf("\nInvalid address\n");
		return -1;
	}
	
	if(connect(new_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		printf("\nConnection failed\n");
		return -1;
	}
	send(new_socket, request, strlen(request), 0);
	printf("Request sent\n");
	valread = read(new_socket, buffer, 1024);
	printf("%s\n", buffer);

	return 0;
}
