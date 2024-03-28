#include "SockUtils.h"
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
WSADATA wsaData;
void SockUtils::init(){
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        LOG_DEBUG("初始化失败！");
        return;}
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        LOG_DEBUG("创建套接字失败!");
        WSACleanup();
        return;}
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(1100);
    serverAddress.sin_addr.s_addr = inet_addr("ipv6.ourtech.cc");
    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        LOG_DEBUG("连接服务器失败!");
        closesocket(clientSocket);
        WSACleanup();
        return;}
    const char* sendData = "Hello, server!";
    if (send(clientSocket, sendData, strlen(sendData), 0) == SOCKET_ERROR) {
        LOG_DEBUG("Failed to send data to server!");
        closesocket(clientSocket);
        WSACleanup();
        return ;
    }  
    char recvBuffer[256];
    memset(recvBuffer, 0, sizeof(recvBuffer));
    int bytesReceived = recv(clientSocket, recvBuffer, sizeof(recvBuffer) - 1, 0);
    if (bytesReceived == SOCKET_ERROR) {
        LOG_DEBUG("Failed to receive data from server!");}
    else {
        LOG_EVENT("Received data from server: {%s}",recvBuffer);}

    closesocket(clientSocket);
    WSACleanup();
}