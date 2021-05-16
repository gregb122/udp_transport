#Grzegorz Bielecki 288388

CFLAGS = -std=gnu17 -Wall -Wextra

transport: $(obj)
	gcc $(CFLAGS) -c -o transport.o transport.c
	gcc $(CFLAGS) -c -o segment.o segment.c
	gcc $(CFLAGS) -c -o segments_window.o segments_window.c
	gcc $(CFLAGS) -c -o connection.o connection.c
	gcc $(CFLAGS) -o transport connection.o segment.o segments_window.o transport.o

.PHONY: clean distclean
clean:
	rm -f *.o

distclean:
	rm  -f transport out/* *.o