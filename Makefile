.PHONY: all

all:
	@g++ src/List/Functions/indexes.cpp src/List/Functions/insertion.cpp src/List/Functions/otheropers.cpp src/List/Functions/pointers.cpp src/List/Struct/list.cpp src/Text/parser.cpp src/Debug/debug.cpp src/hashfunctions.cpp src/hashtable.cpp src/main.cpp -fsanitize=address -o hasht