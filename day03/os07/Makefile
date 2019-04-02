TOOLPATH = ../../tools/
MAKE     = $(TOOLPATH)make.exe -r
NASK     = $(TOOLPATH)nask.exe
EDIMG    = $(TOOLPATH)edimg.exe
IMGTOL   = $(TOOLPATH)imgtol.com
COPY     = copy
DEL      = del

default :
	$(MAKE) run

# 生成二进制文件和列表文件
ipl.bin : ipl.nas Makefile
	$(NASK) ipl.nas ipl.bin ipl.lst

# 生成操作系统SYS文件
os.sys : os.nas Makefile
	$(NASK) os.nas os.sys os.lst
	
# 生成磁盘映像文件
os.img : ipl.bin os.sys Makefile
	$(EDIMG) imgin:../../tools/fdimg0at.tek \
	wbinimg src:ipl.bin len:512 from:0 to:0 \
	copy from:os.sys to:@: \
	imgout:os.img

# 命令
	
img :
	$(MAKE) os.img
	
run :
	$(MAKE) img
	$(COPY) os.img ..\..\tools\qemu\fdimage0.bin
	$(MAKE) -C ../../tools/qemu
	
install :
	$(MAKE) img
	$(IMGTOL) w a: os.img
	
clean :
	-$(DEL) ipl.bin
	-$(DEL) ipl.lst
	-$(DEL) os.sys
	-$(DEL) os.lst
	-$(DEL) os.img
	
src_only :
	$(MAKE) clean
	-$(DEL) helloos.img