# reliable-file-transfer-tcp
A modification of the TCP protocol to increase throughput on lossy links.


<<<<<<< HEAD
## Modifying TCP Backoff Through the Kernel
### 1. Network retry limit: 
    run following and get output
    '''
    iwconfig wlan0 | grep Retry
        Retry  long limit:7   RTS thr:off   Fragment thr:off
    '''

    set retry limit to 0
    '''
    iwconfig wlan0 retry limit 0
    '''

### 2. TCP stack:
    run following to get tcp options
    ''' 
    man 7 tcp 
    '''

    sysctl net.ipv4.tcp_foo=1 
    TCP options listed under 

Source: https://whitequark.org/blog/2011/09/12/tweaking-linux-tcp-stack-for-lossy-wireless-networks/
=======
zane:

Useful parts of TCP/IP Illustrated Books
- Algorithms: v1 Chapters 13 - 16
- Code comments: v2 Chapters 24 - 30
>>>>>>> 300eb0f07a605dd4d579fad06d0388bda8c028a6
