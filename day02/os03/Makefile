default :
	../../tools/make.exe run

# 生成二进制文件和列表文件
ipl.bin : ipl.nas Makefile
	../../tools/nask.exe ipl.nas ipl.bin ipl.lst

# 生成磁盘映像文件
os.img : ipl.bin Makefile
	../../tools/edimg.exe imgin:../../tools/fdimg0at.tek \
	wbinimg src:ipl.bin len:512 from:0 to:0 imgout:os.img

# 命令

asm : 
	../../tools/make.exe -r ipl.bin
	
img :
	../../tools/make.exe -r os.img
	
run :
	../../tools/make.exe img
	copy os.img ..\..\tools\qemu\fdimage0.bin
	../../tools/make.exe -C ../../tools/qemu
	
install :
	../../tools/make.exe img
	../../tools/imgtol.com w a: os.img
	
clean :
	-del ipl.bin
	-del ipl.lst
	
src_only :
	../../tools/make.exe clean
	-del helloos.img