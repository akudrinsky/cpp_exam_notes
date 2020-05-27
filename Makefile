all:
	g++ -Wall example.cpp

commit:
	git add -A && git commit -m "akudrinsky auto commit" && git push -u origin master