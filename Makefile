all: git-commit ping_server

git-commit:
	git checkout master >> .local.git.out || echo
	git add -A >> .local.git.out || echo
	git commit -a -m "New commit" >> .local.git.out || echo
	git push -u origin master

ping-server: ping_server.c ping_server.h
	gcc -g -Wall -Werror -o ping_server ping_server.c ping_server.h

.PHONY: clean

clean:
	rm ping_server
