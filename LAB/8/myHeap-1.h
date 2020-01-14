#ifndef MY_HEAP_
#define MY_HEAP_

#include <algorithm>
#include <iostream>
using namespace std;

template<class ItemType>
class myHeap {
private:
   // Start with a small default size
   static const int ROOT = 0;
   static const int DEFAULT_CAPACITY = 24;
   ItemType *items;

   int itemCount; // Current count of heap items
   int maxItems;  // Maximum capacity of the heap

   // Returns the array index of the left child (if exists).
   int getLeftChildIndex(const int nodeIndex) const;
   
   // Returns the array index of the right child (if exists).
   int getRightChildIndex(int nodeIndex) const;
   
   // Returns the array index of the parent node.
   int getParentIndex(int nodeIndex) const;
   
   // Tests whether this node is a leaf.
   bool isLeaf(int nodeIndex) const;
   
   // Converts a semiheap to a heap.
   void heapRebuild(int nodeIndex);
   
   // Creates a heap from an unordered array.
   void heapCreate();
   
public:
   myHeap();
   myHeap(const ItemType someArray[], const int arraySize);
   ~myHeap();
   
   // HeapInterface Public Methods:
   bool isEmpty() const;
   int getNumberOfNodes() const;
   
   ItemType peekTop() const;
   bool add(const ItemType& newData);
   bool remove();
   void clear();
};

template<class ItemType>
int myHeap<ItemType>::getLeftChildIndex(const int nodeIndex) const {
   return (2 * nodeIndex) + 1;
}

template<class ItemType>
int myHeap<ItemType>::getParentIndex(const int nodeIndex) const {
   return (nodeIndex - 1) / 2;
}

template<class ItemType>
bool myHeap<ItemType>::isLeaf(const int nodeIndex) const {
   return (getLeftChildIndex(nodeIndex) >= itemCount);
}

template<class ItemType>
int myHeap<ItemType>::getRightChildIndex(const int nodeIndex) const {
   return (2 * nodeIndex) + 2;
}

template<class ItemType>
void myHeap<ItemType>::heapRebuild(const int subTreeNodeIndex) {
   if(!isLeaf(subTreeNodeIndex))
   {
      int leftChildIndex = getLeftChildIndex(subTreeNodeIndex);

      int largerChildIndex = leftChildIndex;
      
      int rightChildIndex = getRightChildIndex(subTreeNodeIndex);

      if(rightChildIndex < itemCount)
      {
         if(items[rightChildIndex] > items[largerChildIndex])
            largerChildIndex = rightChildIndex;
      }

      if(items[subTreeNodeIndex] < items[largerChildIndex])
      {
         swap(items[largerChildIndex], items[subTreeNodeIndex]);
         heapRebuild(largerChildIndex);
      }
   }
}

template<class ItemType>
void myHeap<ItemType>::heapCreate() {
   for (int index = itemCount / 2; index >= 0; index--) {
      heapRebuild(index);  
   }
}

// Constructor that accepts an existing array
template<class ItemType>
myHeap<ItemType>::
myHeap(const ItemType someArray[], const int arraySize):
             itemCount(arraySize), maxItems(2 * arraySize) {

   items = new ItemType[2 * arraySize];
   for(int i = 0; i < itemCount; i++)
      items[i] = someArray[i];
   heapCreate();
}

// Default constructor
template<class ItemType>
myHeap<ItemType>::myHeap(): itemCount(0),
        maxItems(DEFAULT_CAPACITY) {
   items = new ItemType[DEFAULT_CAPACITY];
}

// Default destructor
template<class ItemType>
myHeap<ItemType>::~myHeap() {
        delete[] items; 
}

// Return whether the heap is empty
template<class ItemType>
bool myHeap<ItemType>::isEmpty() const {
   return itemCount == 0;
}

// Return the total number of nodes
template<class ItemType>
int myHeap<ItemType>::getNumberOfNodes() const {
   return itemCount;
}

// Remove the root of the heap and rebuild it
template<class ItemType>
bool myHeap<ItemType>::remove() {
   bool Successful = false;

   if(!isEmpty())
   {
      items[ROOT] = items[itemCount-1];
      itemCount--;
      heapRebuild(ROOT);
      Successful = true;
   }
   return Successful;
}

// Clear all items (note we do not resize the array here).
template<class ItemType>
void myHeap<ItemType>::clear() {
   itemCount = 0;
}

// Return the value at the root of the heap
template<class ItemType>
ItemType myHeap<ItemType>::peekTop() const {
   return items[0];
}

// Add a new item to the heap
template<class ItemType>
bool myHeap<ItemType>::add(const ItemType& newData) {

   bool Successful = false;

   if(itemCount < maxItems)
   {
      items[itemCount] = newData;

      bool inIndex = false;

      int newDataIndex = itemCount;

      while((newDataIndex > 0) && !inIndex)
      {
         int parentIndex = getParentIndex(newDataIndex);

         if(items[newDataIndex] < items[parentIndex])
         {
            inIndex = true;
         } else
         {
            swap(items[newDataIndex], items[parentIndex]);
            newDataIndex = parentIndex;
         }
         
      }
      itemCount++;
      Successful = true;
   }
   return Successful;
}
#endif /* !MY_HEAP_ */
