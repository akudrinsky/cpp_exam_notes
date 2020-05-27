# ENV CC, CFLAGS
# compile with gcc for the last stable c++ standard
CC= g++
CFLAGS= -std=c++17 -Wall

# ENV SRCDIR
# c++ sources
SRCDIR= ./practice

# ENV OUTDIR, TARGET
# compiler output
OUTDIR= bin
TARGET= main

# ENV MSG
# default commit message
MSG= 'akudrinsky autocommit'

# TARGET ALL
# build all example files
all: $(SRCDIR)/*.cpp
	$(CC) $(CFLAGS) $(SRCDIR)/*.cpp -o $(OUTDIR)/$(TARGET)

# TARGET COMMIT
# commit all changes locally
# 	USAGE: make commit MSG='commit message'
commit:
	git add -A && git commit -m "$(MSG)"

# TARGET PUSH
# push local changes to the remote
push:
	git push -u origin master
