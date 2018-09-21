1. make sure you cd in /tmp in both nodes
- cd /tmp

2. in the sender node make the file, overwrite with whatever size you want
- dd if=/dev/urandom of=data.bin bs=1M count=1000

3. look up the IP of the receiver node in visualization in browser
- scp data.bin usc542ee@10.1.1.1:/tmp

ping the receiver node if can't connect, sometimes the link is broken in DETER,
you need to swap out and back in for it to work. 
