// #include <stdio.h>
// #include "priority_queue.h"

// int tree_array_size = 50;
// int heap_size = 0;
// const int INF = 100000;

// void swap( process *a, process *b ) {
//   process t;
//   t = *a;
//   *a = *b;
//   *b = t;
// }

// //function to get right child of a node of a tree
// int get_right_child(process **A, int index) {
//   if((((2*index)+1) < tree_array_size) && (index >= 1))
//     return (2*index)+1;
//   return -1;
// }

// //function to get left child of a node of a tree
// int get_left_child(process **A, int index) {
//     if(((2*index) < tree_array_size) && (index >= 1))
//         return 2*index;
//     return -1;
// }

// //function to get the parent of a node of a tree
// int get_parent(process **A, int index) {
//   int size = sizeof(A)/sizeof(A[0]);
//   if ((index > 1) && (index < size)) {
//     return index/2;
//   }
//   return -1;
// }

// void min_heapify(process **A, int index) {
//   int left_child_index = get_left_child(A, index);
//   int right_child_index = get_right_child(A, index);

//   // finding smallest among index, left child and right child
//   int smallest = index;

//   if ((left_child_index <= heap_size) && (left_child_index>0)) {
//     if (A[left_child_index] < A[smallest]) {
//       smallest = left_child_index;
//     }
//   }

//   if ((right_child_index <= heap_size && (right_child_index>0))) {
//     if (A[right_child_index] < A[smallest]) {
//       smallest = right_child_index;
//     }
//   }

//   // smallest is not the node, node is not a heap
//   if (smallest != index) {
//     swap(&A[index], &A[smallest]);
//     min_heapify(A, smallest);
//   }
// }

// void build_min_heap(process **A) {
//   int i;
//   for(i=heap_size/2; i>=1; i--) {
//     min_heapify(A, i);
//   }
// }

// int minimum(process** A) {
//   return A[1];
// }

// process * extract_min(process **A) {
//   printf("minnnnnnnn%d\n", sizeof(A)/sizeof(A[0]));
//   // process* minm = A[1];
//   // A[1] = A[heap_size];
//   // heap_size--;
//   // min_heapify(A, 1);
//   // return minm;
//   return NULL;
// }

// void decrease_key(process **A, int index, process* key) {
//   // A[index] = key;
//   // printf("*********************%d\t%.1f\t%d\n", key->id, key->arrival_time, key->service_time);
//   // printf("********************* %d, %.1f, %.1f, %i\n", key->id, key->arrival_time, key->service_time, key->priority);
//   printf("####### %.1f\n", A[get_parent(A, index)]->service_time);
//   while((index>1) && (A[get_parent(A, index)]->service_time > A[index]->service_time)) {
//     swap(&A[index], &A[get_parent(A, index)]);
//     index = get_parent(A, index);
//   }
// }

// void increase_key(int A[], int index, int key) {
//   A[index] = key;
//   min_heapify(A, index);
// }

// void insert(process **A, process* key) {
//   printf("aaaaaaa, %d\n", heap_size);
//   heap_size++;
//   A[heap_size] = NULL;
//   decrease_key(A, heap_size, key);
// }

// // void print_heap(process* A[]) {
// //   int i;
// //   for(i=1; i<=heap_size; i++) {
// //     printf("%d\n",A[i]);
// //   }
// //   printf("\n");
// // }

// // int main() {
// //   int A[tree_array_size];
// //   insert(A, 20);
// //   insert(A, 15);
// //   insert(A, 8);
// //   insert(A, 10);
// //   insert(A, 5);
// //   insert(A, 7);
// //   insert(A, 6);
// //   insert(A, 2);
// //   insert(A, 9);
// //   insert(A, 1);

// //   print_heap(A);

// //   increase_key(A, 5, 22);
// //   print_heap(A);

// //   printf("%d\n\n", minimum(A));
// //   printf("%d\n\n", extract_min(A));

// //   print_heap(A);

// //   printf("%d\n", extract_min(A));
// //   printf("%d\n", extract_min(A));
// //   printf("%d\n", extract_min(A));
// //   printf("%d\n", extract_min(A));
// //   printf("%d\n", extract_min(A));
// //   printf("%d\n", extract_min(A));
// //   printf("%d\n", extract_min(A));
// //   printf("%d\n", extract_min(A));
// //   printf("%d\n", extract_min(A));
// //   return 0;
// // }
#include "priority_queue.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 50

process* intArray[MAX];
int itemCount = 0;

process* peek(){
   return intArray[itemCount - 1];
}

bool isEmpty(){
   return itemCount == 0;
}

bool isFull(){
   return itemCount == MAX;
}

int size(){
   return itemCount;
}  

void insert(process * data){
   int i = 0;

   if(!isFull()){
      // if queue is empty, insert the data 
      if(itemCount == 0){
         intArray[itemCount++] = data;        
      }else{
         // start from the right end of the queue 
      
         for(i = itemCount - 1; i >= 0; i-- ){
            // if data is larger, shift existing item to right end 
            if(data->service_time > intArray[i]->service_time){
               intArray[i+1] = intArray[i];
            }else{
               break;
            }            
         }  
      
         // insert the data 
         intArray[i+1] = data;
         itemCount++;
      }
   }
}

process* removeData(){
  if(itemCount > 0){
     return intArray[--itemCount];  
  }
   return NULL; 
}