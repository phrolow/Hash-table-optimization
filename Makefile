.PHONY: all

all:
	@g++ List/Functions/indexes.cpp List/Functions/insertion.cpp List/Functions/otheropers.cpp List/Functions/pointers.cpp List/Struct/list.cpp Text/parser.cpp Debug/debug.cpp hashfunctions.cpp hashtable.cpp main.cpp -fsanitize=address -o hasht