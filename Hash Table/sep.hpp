//Karthik Venkat <kv39@zips.uakron.edu>

//Developed in collaboration with Adam Browne

#ifndef SEP_HPP
#define SEP_HPP

#include <vector>
#include <list>

template<typename T>struct HashTable
{
  //iterator for hash table operations
  typedef typename std::list<T>::iterator iter;
  std::vector<std::list<T>> buckets; //list of buckets for key storage
  int keys; //holds the number of keys in the table

  iter search(T key) //for searching through the list
  {
    int index = h(key) % bucketcount();
    auto first = buckets[index].begin(), last = buckets[index].end();
    if (first == last) return last;
    while(first != last)
    {
      if(*first == key) return first;
      ++first;
    }
  }

  template<typename T> HashTable() //default constructor
  :buckets(), keys(0)
  {
    buckets.resize(14);
  }

  template<typename T> HashTable(HashTable const& s)//copy cstr.
  :buckets(s.buckets), keys(s.keys)
  {}

  template<typename T> HashTable<T>&operator=(HashTable const& s)
  {   //copy assignment operator
    if(this == &s) return *this; //self assign guard
    buckets.clear();
    buckets = s.buckets;
    keys = s.keys;
    return *this;
  }

  template<typename T> double keycount() //Returns number of keys
  {
    return keys;
  }

  template<typename T> int h(T key) //hash function
  {
    return key % bucketcount();
  }

  //store current in a new holder vector and compute hash values for them
  template<typename T> void rehash(int n)
  {
    if(n >= bucketcount())
    {
      std::vector<std::list<T>> holder = buckets;
      buckets.clear();
      buckets.resize(n);
      for(auto list : holder)
        for(auto key : list)
          insert(key);
      }
  }

  template<typename T> int bucketcount()//returns number of buckets
  {
    return buckets.size();
  }

  template<typename T> double alpha()//returns load factor
  {
    return keycount() / bucketcount();
  }

  template<typename T> void insert(T key) //inserts key
  {
    int position = h(key) % bucketcount();
    bucket[position].push_back(key);
  }

  //rehashes if load factor exceeds 0.75
  template<typename T> void adjust(T key)
  {
   ++keys;
    if(alpha() <= .75) insert(key); //no need to adjust here
    else  //rehash if alpha is over 0.75
    {
      rehash(2 * bucketcount()); //rehash to a table that is 2X as big
      insert(key);
    }
  }

  ~HashTable() = default; //destructor, defaulted

};
#endif
