mkdir -p isodir/boot/grub
sudo cp OSFiles/MaDaMiOS.bin isodir/boot/myos.bin
sudo cp grub.cfg isodir/boot/grub/grub.cfg
sudo grub-mkrescue -o OSFiles/MaDaMiOS.iso isodir
sudo rm -R isodir