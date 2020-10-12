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
