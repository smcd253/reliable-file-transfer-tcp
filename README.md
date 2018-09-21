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

### 3. Useful Links
Tune TCP for Linux: http://web.archive.org/web/20111213021347/http://fasterdata.es.net:80/fasterdata/host-tuning/linux
Simulate Link Delay Linux: https://bencane.com/2012/07/16/tc-adding-simulated-network-latency-to-your-linux-server/
Simulate Link Loss Linux: https://stackoverflow.com/questions/614795/simulate-delayed-and-dropped-packets-on-linux

### 4. Notes for Implementation
1. Try Scalable TCP
2. Try model-based window-sizing

### 5. To Do 9/20 12PM Meeting
1. Spencer: Try switching protocols on DETER through kernel commands you found (Tune TCP for Linux link above)
2. Spencer: Install new kernel on host VM
3. Spencer: Look into model-based window size (make as a function of BW Delay and Link Loss )

=======
zane:

Useful parts of TCP/IP Illustrated Books
- Algorithms: v1 Chapters 13 - 16
- Code comments: v2 Chapters 24 - 30
>>>>>>> 300eb0f07a605dd4d579fad06d0388bda8c028a6

Ali:

Custom Compiled Kernel for Ubuntu  
https://www.linode.com/docs/tools-reference/custom-kernels-distros/custom-compiled-kernel-debian-ubuntu/

This link will help you in understanding about what we have to do in a better way.   
https://lwn.net/Articles/308919/


Follow this guide to download and compile kernel  
https://medium.freecodecamp.org/building-and-installing-the-latest-linux-kernel-from-source-6d8df5345980


TCP congestion control algorithms  
https://linuxgazette.net/135/pfeiffer.html

Simulate latency . 
https://www.binarytides.com/linux-commands-monitor-network/

Simulate loss .
https://bencane.com/2012/07/16/tc-adding-simulated-network-latency-to-your-linux-server/

