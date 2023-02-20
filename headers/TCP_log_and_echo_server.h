#pragma once

#define WINVER 0x0502         /// to activate functions getnameinfo and inet_ntoa in WinXP
#define _WIN32_WINNT 0x0502   /// see WS2tcpip.h
#define _WIN32_IE 0x600

#include "ShowLastError.h"
#include "LogToFile.h"

#include <iomanip>
#include <iostream>
#include "../headers/ws2tcpip.h"
#include <winsock.h>           /// sockets
#pragma comment (lib, "ws_32.lib")

#ifndef TCP_LOG_AND_ECHO_SERVER_H_INCLUDED
#define TCP_LOG_AND_ECHO_SERVER_H_INCLUDED
int TCP_log_and_echo_server();
#endif // TCP_LOG_AND_ECHO_SERVER_H_INCLUDED





