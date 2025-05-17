setuser: setuser.c
	gcc -Wall -o setuser setuser.c

install:
	mkdir -p $(DESTDIR)/usr/bin
	install -m 755 setuser $(DESTDIR)/usr/bin/

clean:
	rm -f setuser

