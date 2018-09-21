
1. make sure to do both every time, does not build without update
- ssh into node
- sudo apt-get update
- sudo apt-get install git fakeroot build-essential ncurses-dev xz-utils libssl-dev bison flex libelf-dev bc

2. Download the latest Build to /tmp in the node you want to build. I got warnings
from Deter when I put it elsewhere, it builds wherever you put it.
- cd /tmp
- wget "https://cdn.kernel.org/pub/linux/kernel/v4.x/linux-4.18.9.tar.xz"
- tar xf linux-4.18.9.tar.xz
- cd linux-4.18.9

3. Make; at the end in GUI, save then enter then exit.
- cp /boot/config-$(uname -r) .config
- make menuconfig

4. Do these one by one, while in the same kernel directory. If you put all
together the node freezes sometimes and you get forced out of ssh session. Each takes around one hour, reboot system first if there's an error.
- sudo make -j 4
- sudo make modules_install -j 4  
- sudo make install -j 4

5. Reboot, takes 5 minutes, check status in deterlab in browser, where the
physical addresses are a the bottom of the page. The other commands are not
necessary because we use a different pc at each swap in.
- sudo shutdown -r now
- uname -r
