#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


using namespace std;


#define NUM_THREAD 2


const int BUF_SIZE = 1024;


void *recv(void *arg)
{
	int fd = *((int*)arg);
	char buffer[BUF_SIZE] = {};
	while(1)
	{
		memset(buffer,0x00,BUF_SIZE);
		int ret = recv(fd,buffer,BUF_SIZE,0);	
		if (ret < 0)
		{
			cout << "找不到服务器";
			break;
		}	
		cout << "server:" << buffer << endl; 
	}
	close(fd);
}

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
	

	pthread_t tids[NUM_THREAD];
	int ret = pthread_create(&tids[0],NULL,recv,(void *)&client_fd);
	if (ret != 0)
    {
    	cout << "接收线程创建失败" << endl;
    }


	while (1)
	{
	    char buffer[BUF_SIZE] = {};
		cin >> buffer;
		send(client_fd,buffer,BUF_SIZE,0);	
		// cout << "已发送" << endl;
	}


	pthread_exit(NULL);
	return 0;
}