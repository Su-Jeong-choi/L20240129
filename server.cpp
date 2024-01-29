#include <iostream>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32")

using namespace std;

int main()
{
	WSADATA wsaData;
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET ListenSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	struct sockaddr_in ListenSockAddr;
	memset(&ListenSockAddr, 0, sizeof(ListenSockAddr));

	ListenSockAddr.sin_family = AF_INET;
	ListenSockAddr.sin_addr.s_addr = INADDR_ANY;
	ListenSockAddr.sin_port = htons(5001);

	bind(ListenSocket, (SOCKADDR*)&ListenSockAddr, sizeof(ListenSockAddr));
	listen(ListenSocket, 5);

	struct sockaddr_in ClientSockAddr;
	memset(&ClientSockAddr, 0, sizeof(ClientSockAddr));
	int ClientSockAddrLength = sizeof(ClientSockAddr);
	SOCKET ClientSocket = accept(ListenSocket, (SOCKADDR*)&ListenSockAddr, &ClientSockAddrLength);

	const char SendMessage[] = { "서버가 보냄." };
	int SentByte = send(ClientSocket, SendMessage, strlen(SendMessage), 0);
	cout << SendMessage << endl;

	char RecvMessage[1024] = { 0, };
	int RecvByte = recv(ClientSocket, RecvMessage, sizeof(RecvMessage), 0);
	cout << "받은 메세지 : " << RecvMessage << endl;

	closesocket(ListenSocket);
	closesocket(ClientSocket);

	WSACleanup();

	return 0;
	
}