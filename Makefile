all: git-commit ping_server

git-commit:
	git checkout master >> .local.git.out || echo
	git add -A >> .local.git.out || echo
	git commit -a -m "New commit" >> .local.git.out || echo
	git push -u origin master

ping-server: ping_server.c
	gcc -werror -wall -g -o ping_server ping_server.c -I

.PHONY: clean

clean:
	rm ping_server
