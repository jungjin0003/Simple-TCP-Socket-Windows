#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "T_socket.h"

int main()
{
	T_socket socket;
	T_socket C_socket[2];
	char Data[100];
	socket_reset(&socket);
	socket_bind("127.0.0.1", 8080, &socket);
	socket_listen(&socket);
	socket_accept(&socket, &C_socket[0]);
	socket_receive(Data, sizeof(Data), &C_socket[0]);
	printf("%s", Data);
	system("pause");
	return 0;
}
