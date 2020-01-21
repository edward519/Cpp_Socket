#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define BUFFER_SIZE 512 //메세지 송수신에 사용될 버퍼사이즈

using namespace std;

void error(const char *msg)
{
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[])
{
	int server_socket;
	int client_socket;
	socklen_t client_addr_size;
	int msg_size;
	char buffer[BUFFER_SIZE];
	char temp[20];

	struct sockaddr_in server_addr, client_addr;

	if(argc!=2)
	{
		error("Error, Usege ./filename [PORT]");
	}//파일 실행시 포트번호를 입력 안했을 경우 오류 출력

	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if(server_socket==-1)
	{
		error("Error, Server: Can not Open Socket.");
	}//소켓 생성
	/*AF_INET:주소체계 ipv4
	  PF_INET:프로토콜체계 ipv4*/

	memset(&server_addr, 0x00, sizeof(server_addr));
	//server_addr 를 NULL 로 초기화
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=INADDR_ANY; //INADDR_ANY: 서버의 ip주소를 자동으로 찾아 대입
	server_addr.sin_port=htons(atoi(argv[1]));
	//server_addr setting

	if(bind(server_socket, (struct sockaddr *) &server_addr, sizeof(server_addr))<0)
	{
		error("Error, Server: Can not bind local eddress.");
	}//bind() 호출

	while(1)
	{
		if(listen(server_socket, 5)<0)
		{
			error("Error, Server: Can not listening connect.");
		}//대기상태 설정 및 오류처리 listen의 숫자는 최대 대기 클라이언트 수
		
		cout << "Server: Waiting client request." << endl;
		memset(buffer, 0x00, sizeof(buffer));
		
		client_addr_size=sizeof(client_addr);
		client_socket=accept(server_socket, (struct sockaddr *) &client_addr, &client_addr_size);
		if(client_socket<0)
		{
			error("Error, Server: Fail to connect with client.");
		}

		inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, temp, sizeof(temp));

		cout << "Server: Client " << temp << " connected." << endl;
		msg_size=read(client_socket, buffer, 1024);
		write(client_socket, buffer, msg_size);
		close(client_socket);
		cout << "Server: Client " << temp << " closed." << endl;
	}
	close(server_socket);

	return 0;
}