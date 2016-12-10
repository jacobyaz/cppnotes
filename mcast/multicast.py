import socket
import time

MCAST_GRP = 'localhost'
MCAST_PORT = 1234

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
sock.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_TTL, 2)

count = 0
while count < 20 :
   s = str(count)
   sock.sendto(s, (MCAST_GRP, MCAST_PORT))
   print "Sending %s / 19" % s
   time.sleep(1)
   count = count + 1

