# reliable-file-transfer-tcp
A modification of the TCP protocol to increase throughput on lossy links.

## Modifying TCP Backoff Through the Kernel
### 1. Network Retry Limit
##### run the following to get current retry limit settings:
    iwconfig wlan0 | grep Retry

##### run the following to set retry limit to 0:
    iwconfig wlan0 retry limit 0

### 2. TCP Stack
##### run following to get tcp options:
    man 7 tcp 

##### run the following to make a modification to a tcp parameter:
    sysctl net.ipv4.tcp_foo=1 

Source: https://whitequark.org/blog/2011/09/12/tweaking-linux-tcp-stack-for-lossy-wireless-networks/
=======
zane:

Useful parts of TCP/IP Illustrated Books
- Algorithms: v1 Chapters 13 - 16
- Code comments: v2 Chapters 24 - 30
>>>>>>> 300eb0f07a605dd4d579fad06d0388bda8c028a6
