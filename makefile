cc = gcc
prom = learn
deps = src/zmalloc.h src/adlist.h src/sds.h src/dict.h
obj = main.o src/zmalloc.o src/adlist.o src/sds.o src/dict.o

$(prom): $(obj)
	@$(cc) -o $(prom) $(obj)

%.o: %.c $(deps)
	@$(cc) -c $< -o $@
	
clean:
	@-rm -rf $(obj) $(prom)
	@echo "finish clean"