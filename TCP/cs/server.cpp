#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h> //互联网地址族头文件。地址族 简单来说就是底
						//层是使用的哪种通信协议来递交数据的，如 AF_INET
						// 用的是 TCP/IPv4；AF_INET6使用的是 TCP/IPv6；
						//而 AF_LOCAL 或者 AF_UNIX 则指的是本地通信
						//（即本次通信是在当前主机上的进程间的通信），一般
						// 用绝对路径的形式来指明 
#include <arpa/inet.h>	//信息转换，将客户端信息，转换为字符串信息。
#include <unistd.h>		//是 C 和 C++ 程序设计语言中提供对 POSIX 
						//(可移植操作系统接口)操作系统 API 的访问功能的头文件的名称。


using namespace std;


const int BUF_SIZE = 1024;
int main()
{
	/*+++++++++++++++++++++++++++++++++++++++++++++++
	函数原型											+
	int socket(int domain, int type, int protocol); +
	domain 用于选择网络通信的域，选择通信协议族，通信协议族	+
	在文件socket.h中定义								+
	type 用于选择套接字类型							+
	protocol 制定某个协议的特定类型，即type类型中的某个类	+
	型。通常某协议中只有一种特定类型，这样protocol参数仅能	+
	设置为0；但是有些协议有多种特定的类型，就需要设置这个参	+
	数来选择特定的类型。								+
	++++++++++++++++++++++++++++++++++++++++++++++++*/
    
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd == -1)
    {
    	cout << "socket 创建失败" << endl;
    	exit(-1);
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");


    int res = bind(server_fd,(struct sockaddr*)&addr,sizeof(addr));

    if (res == -1)
    {
    	cout << "bind 失败" << endl;
    	exit(-1);
    }

    cout << "等待客户端的连接" << endl;

    listen(server_fd,30);

    
    while (1)
    {

    	struct sockaddr_in client;
    	socklen_t len = sizeof(client);
    
    	int fd = accept(server_fd, (struct sockaddr*)&client, &len);
	    if (fd == -1)
	    {
	    	cout << "accept 错误\n" <<endl;
	    	continue;
	    }

	    while (1)
	    {
			
	    	char buffer[BUF_SIZE] = {};

			int ret = recv(fd,buffer,BUF_SIZE-1,0);
			if (ret == -1)
			{
				cout << "recv 错误" << endl;
				continue;
			}


			char *ip = inet_ntoa(client.sin_addr);//将网络地址转换成“.”点隔的字符串格
		    cout << "client: " << buffer << endl;

		    memset(buffer,0x00,BUF_SIZE);
		    cin >> buffer;
		    send(fd,buffer,BUF_SIZE,0);

	    }
	    
		close(fd);	
    }
	
	close(server_fd);
    	
    return 0;

}
