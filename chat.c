#include<stdio.h>
#include<netdb.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<stdbool.h>
#include<arpa/inet.h>
#define MAX 140  //max characters
#define SA struct sockaddr //alias for socket structure
char* globalIP;

bool isvalidIP(char* ip) //determine whether or not an IP address is a valid one.
{
    struct sockaddr_in sa;
    int res = inet_pton(AF_INET,ip,&(sa.sin_addr));
    return res != 0;
}

void serverfunc(int sockfd) //server func
{ 
    char buff[MAX]; 
    int n; 
while(true)  //infinite loop , Ctrl C will end it
{ 
    // bzero(Points to a buffer that zeros are copied into,Is the number of zeros to be copied into the buffer)
	bzero(buff, MAX);
	read(sockfd, buff, sizeof(buff));
	printf("Friend: %sYou: ", buff); //buff is gonna be the friend (client) message
	bzero(buff, MAX); //clear
  	n = 0; 
 	while ((buff[n++] = getchar()) != '\n');
    
    int messageLength = strlen(buff);
    
    if(strlen(buff) > MAX)
    {
    printf("Server: Please enter a message size less than 140 characters\n");
    return 0; //ask again
    }
    //if the message is valid (less than 140) write it
	write(sockfd, buff, sizeof(buff));     	
    } 
} 
void server()
{
    int sockfd, connfd, len; 
    struct sockaddr_in servaddr, cli;
    printf("Welcome to Chat!\n");
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    //if failed to create the socket
    if (sockfd == -1) 
    { //useful error  message
		printf("Socket creation failed... :( \n"); 
		exit(0); 
    } 
    
 

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET; //ipv4
	servaddr.sin_addr.s_addr = inet_addr("10.0.2.15");  //ip address of local machine running this program
 	servaddr.sin_port = htons(3007); //port 
    
    
    char printIP[INET_ADDRSTRLEN];
    inet_ntop(AF_INET,&servaddr.sin_addr,printIP,sizeof(printIP));
    printf("Waiting for a connection on %s Port %i\n",printIP,3007); 
// 	
	// status = bind(sockid,&addrport, size)	
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) 
    { 
        //useful error messages
		printf("Socket bind failed...\n"); 
		exit(0); 
    } 
    else 
    { int a = 5; } //useless statement
		
	
	// status = listen(sockid, queuelimit)
    if ((listen(sockfd, 5)) != 0)  //waits for 5 
    { //useful error messages
		printf("Server: Listen failed...\n"); 
		exit(0); 
    }


    len = sizeof(cli);

    connfd = accept(sockfd, (SA*)&cli, &len);
    struct sockaddr_in* pV4Addr = (struct sockaddr_in*)&cli;
    struct in_addr ipAddr = pV4Addr->sin_addr;

    if (connfd< 0) 
    { 
		printf("Server couldn't acccept the client connection...\n"); 
		exit(0); 
    } 
    else
        printf("Found a friend! You recieve first.\n");
    
    serverfunc(connfd); 
    close(sockfd); 
}
void clientfunc(int sockfd) 
{ 
    char buff[MAX];
    int n; 

while (true) //run indefinetly until you Ctrl C 
{
	bzero(buff, sizeof(buff)); 

	printf("You : ");
    n = 0; 
    while ((buff[n++] = getchar()) != '\n');
    write(sockfd, buff, sizeof(buff)); 
    bzero(buff, sizeof(buff)); 
    read(sockfd, buff, sizeof(buff)); 
    if(strlen(buff) > MAX)
    {
        printf("Client : Please enter a message size less than 140 characters\n");
        exit(1); //exit
    }
	printf("Friend : %s", buff);
} 
}
void client(char* Port, char* Ip)
{    
    int sockfd, connfd; 
    struct sockaddr_in servaddr, cli;   

    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    printf("Connecting to server...\n");
    if (sockfd == -1) 
    { 
	printf("Socket creation failed. :(\n"); 
	exit(0);
    } 
    else
    {
        printf("Connected!\n"); 
    }
	bzero(&servaddr, sizeof(servaddr)); 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = inet_addr(Ip); 
	servaddr.sin_port = htons(atoi(Port)); 

    
    // Connect(sockid,&address,addrlen) <--definition of function
    
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) { 
        
		printf("Connection with the server failed...\n"); 
		exit(0); 
    } 
    else
	printf("Connected to a Friend! You send first. \n"); 
	
	clientfunc(sockfd); 
  	close(sockfd); 
}

int main(int argc, char** argv)
{
    char* inPort; //port from cmd
    char* inIP; //ip from cmd
    
    if(argc == 2  && argv[1][0] == '-' && argv[1][1] == 'h' ) //help message 
    {
        printf("1 - Open up a terminal window and navigate to the folder containing the  .c file (chat.c)\n");
        printf("2 - Run the makefile by typing make \n");
        printf("3 - Run the server by typing ./chat\n");
        printf("4 - In another terminal window type ./chat -p {PORTNUMBERHERE} -s {valid IP here}.\n You can also enter the IP address first in this manner: ./client -s {valid IP here} -p {PORTNUMBERHERE}\n\n");


        printf("Please view the README.md for more details\n");
        return 0; 
    }
    if(argc == 1) //if it's just the program name
        server(); // running the server

    
    if(argc == 5) //running the client (after sanity checking parameters)
    {                   
        if(argv[1][1] = 'p' && argv[3][1] == 's') //port then ip address
        {
            inPort = argv[2];
            inIP = argv[4];
        }
        if(argv[1][1] = 's' && argv[3][1] == 'p') //port then ip address
        {
            inPort = argv[4];
            inIP = argv[2];
        }
        
        if(isvalidIP(inIP)) //make sure IP is valid
            
        //pass IP and PORT to client() below
        
        client(inPort,inIP); //running the client
    }
}
