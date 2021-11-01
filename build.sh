I686_TOOLS="Tools/cross/`uname -m`/bin"
mkdir -p temp
sudo chmod 777 Source/Asm/*.asm
sudo chmod 777 Source/C/*.c
sudo chmod 777 Source/C/*.h
if [[ :$PATH: != *:$I686_TOOLS:* ]]; then
export PATH=$I686_TOOLS:$PATH
fi

if sudo nasm -felf32 Source/Asm/*.asm -o temp/boot.o; then
  echo Загрузчик готов!
  if i686-elf-gcc -c Source/C/*.c -o temp/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra; then
    echo Ядро готово!
	if i686-elf-gcc -T linker.ld -o OSFiles/MaDaMiOS.bin -ffreestanding -O2 -nostdlib temp/*.o -lgcc; then
	  echo Линковка прошла успешно!
	else
	  echo Ошибка линковки!
	fi
  else 
    echo Ошибка! Ядро не смогло компилироватся!
  fi
else
  echo Ошибка! Загрузчик не смог компилироватся!
fi
sudo rm -R temp