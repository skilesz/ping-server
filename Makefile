git-commit:
	git checkout master >> .local.git.out || echo
	git add -A >> .local.git.out || echo
	git commit -a -m "New commit" >> .local.git.out || echo
	git push -u origin master

ping-server: ping_server.c
	gcc -werror -wall -std=c99 -g -o ping_server ping_server.c
