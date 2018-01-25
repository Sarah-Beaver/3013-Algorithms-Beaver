// Title:            program_1
// Files:            main.cpp
// Semester:         3013 Advanced Algorithms Spring 2018
//
// Author:           Sarah Beaver
// Email:            sbeaver57@yahoo.com
// Description:
//       a priority queue that orders 
//       items in ascending order
#include <iostream>
#include <ctime>

using namespace std;

//Create a container for our list data
struct node{
  int data;
  node* next;
};

/**
* Class: intLinkedList
* Purpose:
*     Implements a singly linked list that holds integers. 
* Methods:
*     void  frontSert(int x)
*     void  ordersert(int x)
*     node* find(int key)
*     node* remove(int key)
*     void  print()
*/
class intLinkedList{
  private:
  node* Head;
  public:
  intLinkedList(){
    Head = NULL;
  }

//inserts item at the from of list
  void frontSert(int x){
    //empty list case
    if(!Head){
      Head = new node;
      Head->data = x;
      Head->next = NULL;
    }else{//not empty list
      node* T = new node;
      T->data = x;
      T->next = Head;
      Head = T;
    }
  }

//inserts an item into in ascending order
  void orderSert(int x)
  {
     //empty list case
    if(!Head){
      Head = new node;
      Head->data = x;
      Head->next = NULL;
    }
    else
    {//not empty list
      node* prev=Head;
      node* T = new node;
      T->data = x;
      //test if bigger than 1st value in list
      if(prev->data>x)
      {
        T->next=prev;
        Head=T;
      }
      //loops until finds where it goes
      else
      {
        while((prev->next!=NULL)&&(prev->next->data<x))
        {
          prev=prev->next;
        }
      T->next=prev->next;
      prev->next=T;
      }
    }
  }
  
//find the key returns null if not in the list  
  node* Find(int key){
    node* temp = Head;
    while(temp){
      if(temp->data == key){
        return temp;
      }
      temp = temp->next;
    }
    return NULL;
  }
 
 //removes the key from the queue 
  void Remove(int key){
    node* result = Find(key);
    if(result){
      node* temp = Head;
      while(temp->next != result){
        temp = temp->next;
      }
      temp->next = result->next;
      delete result;
    }
  }
  
//prints out the list   
  void print(){
    node* p = Head;
    while(p){
      cout<<p->data<<endl;
      p = p->next;
    }
  }
};

int main() {
  // seed random number generator
  srand(8734587);
  
  
  // declare instance of intLinkedList turning
  // a class definition into an "object"
  intLinkedList mylist;
  
  //Load 10 random ints into our list
  for(int i=0;i<10;i++){
    mylist.orderSert(rand()%100);
  }
  
  //test cases
  mylist.orderSert(7);
  mylist.orderSert(67);
  mylist.orderSert(98);
  
  //print the list
  mylist.print();
  
  //find some value
  cout<<mylist.Find(99)<<endl;
  
  //remove some value 
  mylist.Remove(58);
  
  //print the list again
  mylist.print();

  system("pause");
}
