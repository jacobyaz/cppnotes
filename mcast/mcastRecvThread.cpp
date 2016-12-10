#include <pthread.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <vector>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <string>
#include <cstdlib>
#include <cstring>

std::vector<int> vbuf;
bool endsignal = false;

void * t1f(void * arg1) {
   struct sockaddr_in addr;
   int fd, nbytes;
   struct ip_mreq mreq;
   int const bufsize=256;
   char buf[bufsize];
   if ((fd=socket(AF_INET,SOCK_DGRAM,0)) < 0) {
      perror("socket");
      exit(1);
   }

   /* allow multiple sockets to use the same PORT number */
   
   
   unsigned int yes = 1;
   if (setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(yes)) < 0) {
      perror("Reusing ADDR failed");
      exit(1);
   }

   /* set up destination address */
   
   memset(&addr,0,sizeof(addr));
   addr.sin_family=AF_INET;
   addr.sin_addr.s_addr=htonl(INADDR_ANY);
   addr.sin_port=htons(1234);
   
   /* bind to receive address */
   if (bind(fd,(struct sockaddr *) &addr,sizeof(addr)) < 0) {
      perror("bind");
      exit(1);
   }
   
   /* use setsockopt() to request that the kernel join a multicast group */
   mreq.imr_multiaddr.s_addr=inet_addr("127.0.0.1");
   mreq.imr_interface.s_addr=inet_addr("127.0.0.1");
   if (setsockopt(fd,IPPROTO_IP,IP_MULTICAST_LOOP,&mreq,sizeof(mreq)) < 0) {      
   	perror("setsockopt");
      exit(1);
   }

	struct timeval tv;
	tv.tv_sec = 2;
	tv.tv_usec = 0;
	if (setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &tv,sizeof(timeval)) <0) {
 		perror("setsockopt RCVTIMEO");
 		exit(1);
	}   

   int count =0;
   while(endsignal == false) {
      socklen_t addrlen=sizeof(addr);
      if ((nbytes=recvfrom(fd,buf,bufsize,0,
                           (struct sockaddr *)&addr,&addrlen))<0) {
         perror("recvfrom");
         break;
      }
      vbuf.push_back(count);
      ++count;
   }
}

int main() {
   pthread_t t1;
   pthread_create(&t1, NULL, t1f, (void *)NULL);
   sleep(10);
   endsignal = true;
   std::cout << "main end signal:" << endsignal << std::endl;
   pthread_join(t1,NULL);
   for (auto & v : vbuf) {
      std::cout << v << std::endl;
   } 
   return 0;
   
}

