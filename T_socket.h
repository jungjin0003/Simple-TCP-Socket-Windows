#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock.h>

typedef struct T_socket T_socket;

struct T_socket {
	struct sockaddr_in socket_address;
	unsigned int server_socket;
	unsigned int toClient;
};


int socket_reset(T_socket *Socket);
int socket_close(T_socket *Socket);
int socket_bind(char IP[], int PORT, T_socket *Socket);
int socket_listen(T_socket *Socket);
int socket_accept(T_socket *Socket, T_socket *Client_Socket);
int socket_connect(char IP[], int PORT, T_socket *Socket);
int socket_send(char message[], T_socket *Socket);
int socket_receive(char *message, int array_size, T_socket *Socket);

int socket_reset(T_socket *Socket)
{
	WSADATA wsaData;;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("WSAStartup() ERROR");
		return -1;
	}
	Socket->server_socket = socket(PF_INET, SOCK_STREAM, 0);
	Socket->toClient = socket(PF_INET, SOCK_STREAM, 0);
	if (Socket->server_socket == -1 || Socket->toClient == -1)
	{
		printf("Cannot create socket\n");
		return -1;
	}
	return 0;
}

int socket_close(T_socket *Socket)
{
	closesocket(Socket->toClient);
	closesocket(Socket->server_socket);
	WSACleanup();
	return 0;
}

int socket_bind(char IP[], int PORT, T_socket *Socket)
{
	memset(&Socket->socket_address, 0x00, sizeof(Socket->socket_address));
	Socket->socket_address.sin_family = AF_INET;
	Socket->socket_address.sin_port = htons(PORT);
	Socket->socket_address.sin_addr.s_addr = inet_addr(IP);
	if (bind(Socket->server_socket, (struct sockaddr *)&Socket->socket_address, sizeof(Socket->socket_address)) == -1)
	{
		printf("bind() ERROR\n");
		return -1;
	}
	return 0;
}

int socket_listen(T_socket *Socket)
{
	if (listen(Socket->server_socket, 3) == -1)
	{
		printf("listen() ERROR\n");
		return -1;
	}
	return 0;
}

int socket_accept(T_socket *Server_Socket, T_socket *Client_Socket)
{
	int size = sizeof(Client_Socket->socket_address);
	Client_Socket->toClient = accept(Server_Socket->server_socket, (struct socketaddr *)&Client_Socket->socket_address, &size);
	if (Client_Socket->toClient < 0)
	{
		printf("accept() ERROR");
		return -1;
	}
	return 0;
}

int socket_connect(char IP[], int PORT, T_socket *Socket)
{
	memset(&Socket->socket_address, 0x00, sizeof(Socket->socket_address));
	Socket->socket_address.sin_family = AF_INET;
	Socket->socket_address.sin_port = htons(PORT);
	Socket->socket_address.sin_addr.s_addr = inet_addr(IP);
	if (connect(Socket->toClient, (struct sockaddr *)&Socket->socket_address, sizeof(Socket->socket_address)) == -1)
	{
		printf("connect() ERROR");
		return -1;
	}
	return 0;
}

int socket_send(char message[], T_socket *Socket)
{
	send(Socket->toClient, message, (int)strlen(message), 0);
	return 0;
}

int socket_receive(char *message, int array_size, T_socket *Socket)
{
	char *Data = (char*)malloc(array_size); //[100]
	int status;
	status = recv(Socket->toClient, Data, array_size - 1, 0); //[99]
	if (status == -1)
	{
		printf("recv() ERROR");
		return -1;
	}
	Data[status] = '\0';
	strcpy_s(message, array_size, Data);
	return 0;
}