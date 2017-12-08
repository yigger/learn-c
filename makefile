cc = gcc
prom = list
deps = common/zmalloc.h link/adlist.h
obj = main.o common/zmalloc.o link/adlist.o

$(prom): $(obj)
	@$(cc) -o $(prom) $(obj)

%.o: %.c $(deps)
	@$(cc) -c $< -o $@
	
clean:
	@-rm -rf $(obj) $(prom)
	@echo "finish clean"