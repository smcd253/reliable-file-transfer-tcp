
1.  make sure to do both every time, does not build without this
- sudo apt-get update
- sudo apt-get install git fakeroot build-essential ncurses-dev xz-utils libssl-dev bison flex libelf-dev bc

2. Latest Kernel is copied to home directory which is mounted to each node
- cd Kernel/linux-4.18.9
- cp /boot/config-$(uname -r) .config
- make menuconfig
At the end in GUI, save then enter then exit

3. Do these one by one, while in the linux directory if you put all together the
node freezes sometimes and you get forced out of ssh session. Each takes around
one hour, reboot system first if there's an error.
- sudo make -j 4
- sudo make modules_install -j 4  
- sudo make install -j 4

4. Reboot, takes 5 minutes, check status in deterlab in browser, where the
physical addresses are a the bottom of the page. The other commands are not
necessary because we use a different node at each swap in.
- sudo shutdown -r now
- uname -r
