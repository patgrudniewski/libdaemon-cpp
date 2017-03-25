CC=g++
OBJ=$(patsubst %.cpp, %.o, $(shell find . -type f -name '*\.cpp'))

%.o: %.cpp
	$(CC) -fPIC -c $< -o $@

compile: $(OBJ)
	$(CC) -shared -Wl,-soname,libspawner.so -o libspawner.so $(OBJ)

clean:
	find . -type f -name '*\.o' -delete

install: compile
	cp libspawner.so /usr/lib64/
	mkdir /usr/include/spawner
	cd src && \
		find . -name '*.h' -exec cp --parents {} /usr/include/spawner/ \;

.PHONY: compile clean install
