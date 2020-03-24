#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

int main()
{
	int client_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (client_fd == -1)
	{
		cout << "socket 创建失败" << endl;
		exit(-1);
	}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8080);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");


	int res = connect(client_fd,(struct sockaddr*)&addr,sizeof(addr));
	if (res == -1)
	{
		cout << "连接失败" << endl;
		exit(-1);
	}
	cout << "建立连接" << endl;
	char s[255] ={"hello server,I am client"};
	write(client_fd,s,sizeof(s));
	close(client_fd);

	return 0;

}