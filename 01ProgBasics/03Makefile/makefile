target=app
depend=$(wildcard *.c ./*.c)
midfle=$(patsubst %.c, %.o, $(depend))

$(target):$(midfle)
	$(CC) $^ -o $(target)

%.o:%.c
	$(CC) $< -c -o $@

.PHONY:clean
clean:
	rm $(midfle) -f