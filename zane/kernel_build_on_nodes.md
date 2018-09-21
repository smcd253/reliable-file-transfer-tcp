
1.  sudo apt-get update
- make sure to do this every time, does not build without this

2. sudo apt-get install git fakeroot build-essential ncurses-dev xz-utils libssl-dev bison flex libelf-dev bc

3. cd Kernel/linux-4.18.9
- already copied the latest kernel to home directory wich is mounted to each node

4. cp /boot/config-$(uname -r) .config

1. make menuconfig
- at the end in GUI, save then enter then exit

2. One by one is better, if you put all together the node freezes sometimes
and you get forced out of ssh session
- sudo make -j 4
- sudo make modules_install -j 4  
- sudo make install -j 4

3. sudo shutdown -r now
- reboot, takes 5 minutes, check status in deterlab in browser

4. uname -r

Reboot system first if this doesn't work
