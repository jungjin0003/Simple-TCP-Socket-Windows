# Simple-TCP-Socket-Windows

한국어
매번 C언어로 소켓을 사용할때 코드 작성하기가 너무 귀찮아서 TCP 전용으로 한번 만들어봄

English
When I used socket in C language, I was tired of writing code so I made it for TCP only

# example code

#include <stdio.h>
#include <stdlib.h>
#include "T_socket.h"

int main()
{
	T_socket socket;
	T_socket C_socket;
	char Data[100];
	socket_reset(&socket);
	socket_bind("127.0.0.1", 8080, &socket);
	socket_listen(&socket);
	socket_accept(&socket, &C_socket);
	socket_receive(Data, sizeof(Data), &C_socket);
	printf("%s", Data);
	system("pause");
	return 0;
}
