cc = gcc
prom = learn
deps = src/zmalloc.h src/adlist.h
obj = main.o src/zmalloc.o src/adlist.o

$(prom): $(obj)
	@$(cc) -o $(prom) $(obj)

%.o: %.c $(deps)
	@$(cc) -c $< -o $@
	
clean:
	@-rm -rf $(obj) $(prom)
	@echo "finish clean"