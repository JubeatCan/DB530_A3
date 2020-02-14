
#ifndef SORT_C
#define SORT_C

#include "MyDB_PageReaderWriter.h"
#include "MyDB_TableRecIterator.h"
#include "MyDB_TableRecIteratorAlt.h"
#include "MyDB_TableReaderWriter.h"
#include "Sorting.h"
#include <memory>
#include <vector>

using namespace std;

void mergeIntoFile (MyDB_TableReaderWriter &sortIntoMe, vector <MyDB_RecordIteratorAltPtr> &mergeUs, function <bool ()> comparator, MyDB_RecordPtr lhs, MyDB_RecordPtr rhs) {}

vector <MyDB_PageReaderWriter> mergeIntoList (MyDB_BufferManagerPtr parent, MyDB_RecordIteratorAltPtr leftIter, MyDB_RecordIteratorAltPtr rightIter, function <bool ()> comparator,
	MyDB_RecordPtr lhs, MyDB_RecordPtr rhs) {return vector <MyDB_PageReaderWriter> (); }
	
void sort (int runSize, MyDB_TableReaderWriter &sortMe, MyDB_TableReaderWriter &sortIntoMe, function <bool ()> comparator, MyDB_RecordPtr lhs, MyDB_RecordPtr rhs) {
    MyDB_BufferManagerPtr BufferPtr = sortMe.getBufferMgr();
    vector<MyDB_RecordIteratorAlt> mergeUs;

    for (int i = 0; i < sortMe.getNumPages();) {
        vector< vector<MyDB_PageReaderWriter>> mergeHelper;
        vector< MyDB_PageReaderWriter> tempVector;

        // Record the progress
        int j;
        for (j = i; j < sortMe.getNumPages() && j < i + runSize; j++) {
            tempVector.clear();
            tempVector.push_back(*sortMe[j].sort(comparator, lhs, rhs));
            mergeHelper.push_back(tempVector);
        }

        int endThisRun = j;
        while (mergeHelper.size() != 1) {
            mergeHelper.insert(mergeIntoList(BufferPtr, mergeHelper[0]));
        }
    }
}

#endif
