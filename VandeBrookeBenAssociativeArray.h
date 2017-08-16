//
//  VandeBrookeBenAssociativeArray.h
//  VandeBrookeBenAssociativeArray
//
//  Created by Ben Van de Brooke on 10/10/16.
//  Copyright (c) 2016 Ben Van de Brooke. All rights reserved.
//

#ifndef VandeBrookeBenAssociativeArray_VandeBrookeBenAssociativeArray_h
#define VandeBrookeBenAssociativeArray_VandeBrookeBenAssociativeArray_h

//#include "VandeBrookeBenLab4aDynamicArray.h"
#include <vector>

template <class K, class V>
class AssociativeArray
{
public:
  AssociativeArray(); // constructor
  AssociativeArray(const AssociativeArray<K,V>&); // copy constructor
  AssociativeArray(int); //parameterized constructor allowing user to give an initial capacity
  ~AssociativeArray(); // Destructor
  static V dummy;
  
  bool ContainsKey(K) const; //returns a true or false depending on if there is a value stored at the key
  bool DeleteKey(K); // deletes the data stored at the given key. returns false if no value there
  void Clear(); //calls delete key on all of the keys
  int size() const; // returns the size of the AA
  int capacity() const; //returns the capacity of the array
  std::vector<K> keys(); //returns a vector of all keys with data in them
  void Copy(const AssociativeArray<K,V>&); //copies the data from one AA to this one
  
  V operator[](const K) const; //getter [] returns the value at the given key
  V& operator[](const K); // setter [] allows the user to set the value at a given key
  AssociativeArray<K,V>& operator=(const AssociativeArray<K,V>&);
  
private:
  int Size;
  int Capacity;
  
  template<class I, class D>
  struct Element
  {
    I index;
    D datum;
    bool inUse;
    Element():index(K()),datum(D()),inUse(false){};
  };
  
  Element<K,V> *data; // dynamic array of elements
  
};

template<class K, class V>
V AssociativeArray<K,V>:: dummy = V();


//default constructor sets all values to not in use and is filled with type defaults
template<class K, class V>
AssociativeArray<K,V>::AssociativeArray()
{
  data = NULL;
  Capacity = 10;
  Size = 0;
  
  data = new Element<K,V> [Capacity];
  
  for(int x = 0; x < Capacity; x++)
  {
    data[x].inUse = false;
  }
  
}



//Parameterized constructor that allows the user to give the array its capaticy
template<class K, class V>
AssociativeArray<K,V>::AssociativeArray(int givenCap)
: data(NULL), Size(0),Capacity(10)
{
  if(givenCap > 0)
  {
    data = new Element<K,V> [givenCap];
    Size = 0;
    Capacity = givenCap;
    
    for(int x = 0; x < givenCap; x++)
    {
      data[x].inUse = false;
    }
    
  }
}






//copy constructor that allows the user to set an associative array with the values of a preexisting associative array
template<class K, class V>
AssociativeArray<K,V>::AssociativeArray(const AssociativeArray<K,V>& givenAA)
:data(NULL),Size(0),Capacity(0)
{
  Copy(givenAA);
}



// helper function that lets copies one dynamic array to another
template<class K, class V>
void AssociativeArray<K,V>::Copy(const AssociativeArray<K,V> &givenAA)
{
  Size  = givenAA.Size;
  Capacity = givenAA.Capacity;
  data = new Element<K,V> [Capacity];
  
  //sets all values to not inUse unless DynamicArray being copied is in use at that index. sets to in use and copies data
  for(int x = 0; x < Capacity; x ++)
  {
    data[x].inUse = false;
    
    if(givenAA.data[x].inUse)
    {
      data[x].inUse = true;
      data[x].index = givenAA.data[x].index;
      data[x].datum = givenAA.data[x].datum;
    }
    
  }
  
}




template<class K,class V>
AssociativeArray<K,V>::~AssociativeArray()
{
  Clear();
}

// clears the dynamic memeory holding the data and in use settings, makes them point to null and sets size and capacity to 0
template<class K, class V>
void AssociativeArray<K,V>::Clear()
{
  if(data)
  {
    delete [] data;
  }
  
  data = NULL;
  Capacity = Size = 0;
  
}



//setter
// Capcity will double until large enough to hold the value given by the user
// if negative values are given the function will return the default value of the data type the given instance of this class is holding
template<class K, class V>
V& AssociativeArray<K,V>::operator[](K key)
{
  
  //check to see if key is being used
  for (int x = 0; x < Capacity; x++)
  {
    if(data[x].inUse && data[x].index == key)
    {
      //data[x].inUse = true;
      return data[x].datum;
    }
  }
  
  
  //checking to see if the key there just not in use
  for(int x = 0; x < Capacity; x++)
  {
    
    if(!data[x].inUse)
    {
      Size++;
      data[x].index = key;
      data[x].inUse = true;
      return data[x].datum;
    }
  }
  
  //key was not found
  // add a new element to the dynamic array and return its datum, increment size and capacity;
  
  
  Element<K,V> *newData = new Element<K,V> [Capacity+1];
  
  for(int x = 0; x < Capacity; x++)
  {
    newData[x].datum = data[x].datum;
    newData[x].index = data[x].index;
    newData[x].inUse = data[x].inUse;
  }
  
  
  newData[Capacity].index = key;
  newData[Capacity].inUse = true;
  delete [] data;
  data = newData;
  
  Size++;
  Capacity++;
  
  return data[Capacity-1].datum;

}









//getter
// if an in valid input is given the function will return the default value of the data type the given instance of this class is holding
template<class K,class V>
V AssociativeArray<K,V>::operator[](K key) const
{
//  //check for valid input
//  if(index < 0 || index >= Capacity)
//  {
//    return dummy;
//  }
  
  // if the index is being used it will return the value stored there, otherwise it will return the default value of the data type the given instance of this class is holding
  
  for(int x = 0; x < Capacity; x++)
  {
    if(data[x].index == key && data[x].inUse)
    {
      return data[x].datum;
    }
    
  }
 
  return dummy;

}


template<class K,class V>
AssociativeArray<K,V>& AssociativeArray<K,V>::operator=(const AssociativeArray<K,V>& copyMe)
{
  if(this != &copyMe)
  {
    Clear();
    Copy(copyMe);;
      
  }
  
  return *this;
  
}


template<class K,class V>
int AssociativeArray<K,V>::size() const
{
  return Size;
}

template<class K,class V>
int AssociativeArray<K,V>::capacity() const
{
  return Capacity;
}



// tells the user if  the given index is currently occupied by value
//if an input is given greater than the current capacity it will return the default value of the data type the given instance of this class is holding
template<class K,class V>
bool AssociativeArray<K,V>:: ContainsKey(K key) const
{
  //loops through the stored values. if found returns its inUse status
  for(int x = 0; x < Capacity; x++)
  {
    if(data[x].index == key)
    {
      return data[x].inUse;
    }
    
    
  }
  
  //if not found is false
  return false;
}



// DeleteKey()
//loops through the DA of elements checking their keys
//if found it will set it to not in use and decrement the size
// if not returns false
template<class K, class V>
bool AssociativeArray<K,V>::DeleteKey(K key)
{
  
  //loop through the values checking for the key.
  for(int x = 0; x < Capacity; x++)
  {
    if(data[x].index == key)
    {
      data[x].datum = V();
      data[x].inUse = false;
      Size--;
      
      return true;
    }
  }
  
  return false;
  
}







#endif