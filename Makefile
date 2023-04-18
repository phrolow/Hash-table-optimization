.PHONY: all

all:
	@g++ src/List/Functions/indexes.cpp src/List/Functions/insertion.cpp src/List/Functions/otheropers.cpp src/List/Functions/pointers.cpp src/List/Struct/list.cpp src/Text/parser.cpp src/Tests/tests.cpp src/Debug/debug.cpp src/hashfunctions.cpp src/HashTable/hashtable.cpp src/main.cpp -o hasht