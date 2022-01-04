#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 8080

int main(int argc, char* argv[]) {
	int server_fd, new_socket;
	long valread;
	struct sockaddr_in address;
	int addrlen = sizeof(address);
	
	char *response = "HTTP/1.1 200 OK\nContent-Type: text/html;charset=UTF-8\nContent-Length: 72\n\n<!doctype HTML><html><head></head><body><p>Hello World</p></body></html>";

	
	if(!(server_fd = socket(AF_INET, SOCK_STREAM, 0))) {
		perror("Can't create socket!");
		exit(EXIT_FAILURE);
	}

	memset(address.sin_zero, '\0', sizeof(address.sin_zero));
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	address.sin_port = htons(PORT);
	
	if(bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
		perror("Bind failed");
		return 0;
	}
	
	if(listen(server_fd, 3) < 0) {
		perror("Error in listen");
		exit(EXIT_FAILURE);
	}
	while(1) {
		printf("server waiting at port %d\n", PORT);
		if((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
			perror("Error in accept");
			exit(EXIT_FAILURE);	
		}
	
		char buffer[10000] = {0};
		
		valread = read(new_socket, buffer, 10000);
		printf("%s\n", buffer);
		
		write(new_socket, response, strlen(response));
		
		close(new_socket);
	}
	return 0;
}
