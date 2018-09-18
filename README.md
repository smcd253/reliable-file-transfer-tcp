# reliable-file-transfer-tcp
A modification of the TCP protocol to increase throughput on lossy links.


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