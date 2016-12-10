#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <string>
#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include <iostream>

int main() {
   struct sockaddr_in addr;
   int fd, cnt;
   struct ip_mreq mreq;

   if ((fd=socket(AF_INET,SOCK_DGRAM,0)) < 0) {
      perror("socket");
      exit(1);
   }
   /* set up destination address */
   memset(&addr,0,sizeof(addr));
   addr.sin_family=AF_INET;
   addr.sin_addr.s_addr=inet_addr("127.0.0.1");
   addr.sin_port=htons(1234);

   int count = 0;
   while (count < 20) {
      std::string s = std::to_string(count);
      char const * c = s.c_str();
      if (sendto(fd,c,sizeof(c),0,(struct sockaddr *) &addr, sizeof(addr)) < 0) {
	      perror("sendto");
	      exit(1);
      }
      std::cout << "Multicast value: " << count << "/19" << std::endl;
      sleep(1);
      ++count;
   }
}

