#include "../headers/TCP_log_and_echo_server.h"

//#include <iostream>

int main() {
  std::cout<<"I'm a TCP server which receives messages directed to 127.0.0.1 port 12345"<<std::endl;
  std::cout<<"I log the messages and their date/time to TCP_log.txt file"<<std::endl;
  std::cout<<"Then I echo back the message to sender."<<std::endl;
  std::cout<<"To stop the server please enter ""exit""."<<std::endl<<std::endl;;
  TCP_log_and_echo_server();
  system("pause");
  return 0;
}
