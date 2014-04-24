obj-m := dm-void.o

fakeall :
	sh make.sh

.PHONY : clean
clean :
	-rm -fr .tmp*
	-rm -f *.o *.ko* *.mod.* .* modules.order Module.symvers
	# -make -C ebtables/ clean
