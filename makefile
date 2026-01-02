bin/testTableEntry: testTableEntry.cpp TableEntry.h
	mkdir -p bin
	g++ -o bin/testTableEntry testTableEntry.cpp
clean:
	rm -rf *.o *.gch bin
	
bin/testHashTable: testHashTable.cpp HashTable.h TableEntry.h Dict.h
	mkdir -p bin
	g++ -o bin/testHashTable testHashTable.cpp

bin/testBSTree: testBSTree.cpp BSTree.h BSNode.h
	mkdir -p bin
	g++ -o bin/testBSTree testBSTree.cpp

bin/testBSTreeDict: testBSTreeDict.cpp Dict.h BSTreeDict.h BSNode.h TableEntry.h BSTree.h
	mkdir -p bin
	g++ -o bin/testBSTreeDict testBSTreeDict.cpp

