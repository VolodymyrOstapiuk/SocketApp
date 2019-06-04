
#include <iostream>           
#include <cstdlib>
#include <cstring>
#include "PracticalSocket.h"
#include <pthread.h> 
#include <stdint.h>
       #include <semaphore.h>
using namespace std;
const int RCVBUFSIZE = 1024;   
#define OK ok
#define LOG_FILE_PATH "log.txt"
char ok[]="acceptance";
void HandleTCPClient(TCPSocket *sock); 
void *ThreadMain(void *arg);              
void sendMessage(string IP, uint16_t port,string msg);
uint8_t equals(char first[],char second[]);
void *iostreamHandler(void* arg);
void threadSafeOutput(string msg);
void threadSafeConsoleOutput(string msg);
uint16_t ServerPort=55554;
sem_t semaphore;
FILE *file;
int main(int argc, char **argv) {

 pthread_t iostreamThreadID;

sem_init(&semaphore, 0, 1);
threadSafeConsoleOutput("Enter the server port:");
cin >> ServerPort;

 uint8_t *arg;
 arg=new uint8_t;
*arg=0;

    if (pthread_create(&iostreamThreadID, NULL, iostreamHandler,(void*)arg) != 0) {
        cerr << "Unable to create iostream thread" << endl;
        exit(1);
      }
  try{
    TCPServerSocket servSock(ServerPort);  
    for (;;) {      
      TCPSocket *clntSock = servSock.accept(); 
	threadSafeOutput("Socket accepted");
      pthread_t threadID;             
      if (pthread_create(&threadID, NULL, ThreadMain, 
              (void *) clntSock) != 0) {
        cerr << "Unable to create thread" << endl;
        exit(1);
      }
      
    }
  } catch (SocketException &e) {
    cerr << e.what() << endl;
    exit(1);
  }
return 0;
}

void sendMessage(string IP, uint16_t port,char* msg){
threadSafeOutput("Creating TCP socket\n");
TCPSocket *tempClient = new TCPSocket(IP,port);
threadSafeOutput("Sending message\n");
tempClient->send(msg,strlen(msg));
threadSafeOutput("After send message\n");
  char echoBuffer[RCVBUFSIZE];
  int recvMsgSize = tempClient->recv(echoBuffer, RCVBUFSIZE);
  threadSafeOutput(echoBuffer);
threadSafeOutput("\n");
  if (equals(echoBuffer,OK)){
threadSafeOutput("received acceptance");
 }
 else{
threadSafeOutput("No ACK");
 }
threadSafeOutput("continuing workflow");
delete tempClient;
threadSafeOutput("closed TCPSocket");
}




void HandleTCPClient(TCPSocket *sock) {
threadSafeOutput("Handling client ");

  try {
threadSafeOutput(sock->getForeignAddress());
threadSafeOutput(":");
  } catch (SocketException &e) {
    cerr << "Unable to get foreign address" << endl;
  }
  try {
threadSafeOutput(to_string(sock->getForeignPort()));
  } catch (SocketException &e) {
    cerr << "Unable to get foreign port" << endl;
  }
threadSafeOutput(" with thread ");
threadSafeOutput(to_string(pthread_self()));
threadSafeOutput("\n");
  char echoBuffer[RCVBUFSIZE];
  int recvMsgSize = sock->recv(echoBuffer, RCVBUFSIZE);
threadSafeOutput(echoBuffer);
threadSafeOutput("\n");
char* pok;
pok=ok;
  sock->send(pok,strlen(pok)+1);
//sendMessage(fIP,fServerPort,"after receiving a message vlad replied with this\n");
//cout<<echoBuffer; 
}

void *ThreadMain(void *clntSock) {
  pthread_detach(pthread_self()); 
threadSafeOutput("Before calling HandleTCPClient in ThreadMain\n");
  HandleTCPClient((TCPSocket *) clntSock);
  delete (TCPSocket *) clntSock;
  return NULL;
}  


void *iostreamHandler(void* arg) {
  pthread_detach(pthread_self());
  uint16_t PORT;
  while(1){
  char msg[1024] ;
  string  IP;
threadSafeConsoleOutput("any message to send?\n");
  cin>>msg;
threadSafeConsoleOutput(msg);
threadSafeConsoleOutput("\nIP:");
  cin>>IP;
threadSafeConsoleOutput(IP);
threadSafeConsoleOutput("\nPORT:");
  cin>>PORT;
threadSafeConsoleOutput(to_string(PORT));
threadSafeConsoleOutput("\n");
  sendMessage(IP,PORT,msg);

}
  return NULL;
}
void threadSafeOutput(string msg){
	sem_wait(&semaphore);
	file = fopen(LOG_FILE_PATH,"a");
	if(file == NULL){
        cerr << "Unable to open log file" << endl;
	exit(1);
}
	fputs(msg.c_str(), file);
	fputs("\n",file);
	fclose(file);
	sem_post(&semaphore);
}
void threadSafeConsoleOutput(string msg){
	sem_wait(&semaphore);
	cout << msg;	
	sem_post(&semaphore);
}
uint8_t equals(char first[],char second []){
if (strlen(first)!=strlen(second))
    return 0;
  for(uint16_t i=0;i<strlen(first);i++){
    if (first[i]!=second[i]){
      return 0;
    }
  }
  return 1;
}
/*
boot
creating server socket
creating thread for console interface
*/




