#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define BUFFER_SIZE 512

using namespace std;

void error(const char *msg)
{
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[])
{
	int server_socket;
	struct sockaddr_in server_addr;
	char buffer[BUFFER_SIZE];

	if(argc!=2)
	{
		error("Error, Usege ./filename [PORT]");
	}//파일 실행시 포트번호를 입력 안했을 경우 오류 출력

	//socket()
	server_socket=socket(AF_INET, SOCK_STREAM, 0);
	if(server_socket<0)
	{
		error("Error, Client: Can not Open Socket.");
	}

	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	/* "127.0.0.1" localhost. You can switch another server address to want to connect.
		접속할 서버 ip 주소를 입력*/
	server_addr.sin_port=htons(atoi(argv[1]));

	//connect()
	if(connect(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr))<0)
	{
		cout << "Error, Client: Can not connect to server." << endl;
		close(server_socket);
		exit(1);
	} else
	{
		cout << "Client: Connect Success!" << endl;
		cout << "To end connect, type 'exit'" << endl;
	}
	
	while(1)
	{
		cout << "Type message : " ;
		
		//read()
		/*memset(buffer, 0x00, BUFFER_SIZE);
		if(read(server_socket, buffer, BUFFER_SIZE)<0)
		{
			cout << "Client: Read Error." << endl;
			exit(1);
		}*/
		
		cin.getline(buffer, BUFFER_SIZE);
		if(strcmp(buffer,"exit")==0)
		{
			break;
		}
		
		//write()
	/*	memset(buffer, 0x00, BUFFER_SIZE);
		if(write(server_socket, buffer, BUFFER_SIZE)<0)
		{
			cout << "Client: Write Error." << endl;
		}*/
		
	}

	//close()
	close(server_socket);
	return 0;
}


