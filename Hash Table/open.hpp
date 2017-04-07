
//Karthik Venkat <kv39@zips.uakron.edu>
//Developed in collaboration with Adam Browne

#ifndef OPEN_HPP
#define OPEN_HPP

#include <vector>
template<typename T> struct HashTable
{
  //iterator for hash table operations
  typedef typename std::vector<T>::iterator iter;
  //buckets, where the keys will be stored
  std::vector<T> buckets;
  int keys;

  iter search(T key)
  {
    int numBuckets = bucketcount();
    int index = h(key) % numBuckets; //calculate index for open addressing
    //compute the iterators as follows:
    auto current = buckets.begin() + index, last = buckets.end();
    if(*current == key) return current; //cover the first position
    auto first = ++current;
    if (first == last) return first; //no point going through the loop
    while(first != last)
    {
      if(*first == key) return first;
      if((first + 1) == last) first = buckets.begin();
      else if((current - 1) == first) return last;
      ++first;
    }
    return last;
  }

  template<typename T> HashTable()//default constructor
  :buckets(10, T()), keys(0)
  {}

  template<typename T> HashTable(HashTable const& s)//copy constructor
  :buckets(s.buckets), keys(s.keys)
  {}

  template<typename T> HashTable<T>&operator=(HashTable const& x)//copy assign
  {
    if(this == &x) return *this; //self assign guard
    buckets.clear(); //clears the table
    keys = x.keys;
    buckets = x.buckets; //copies contents of x to table
    return *this;
  }

  template<typename T> double keycount() //returns number of keys in table
  {
    return keys;
  }

  template<typename T> int h(T key) //hash function
  {
    return key % bucketcount();
  }

  template<typename T> int bucketcount() //returns number of buckets
  {
    return buckets.size();
  }

  template<typename T> double alpha() //returns load factor
  {
    return keycount() / bucketcount();
  }

  template<typename T> void adjust(T key)//rehashes if load factor exceeds 0.75
  {
    ++keys;
    if(alpha() <= .75) insert(key); //no need to adjust here
    else //rehash if alpha is over 0.75
    {
      rehash(2 * bucketcount()); //rehash to a table that is 2X as big
      insert(key);
    }
  }

  template<typename T> void insert(T key)
  {

    int numBuckets = bucketcount(); //number of buckets in table
    int index = h(key) % numBuckets; //index of insertion
    T dv = T(); //default constructed value
    if(buckets[index] == dv) //cover the first position
    {
      buckets[index] = key;
      return;
    }
    for(int position = ++index; position < buckets.size(); ++position)
    {
      if(buckets[position] == dv)
      {
        buckets[position] = key; //insert into bucket
        break;
      }
      if((position+1) == buckets.size()) position = -1;//wrap around table
    }
  }

  //store current in a new holder vector and compute hash values for them
  template<typename T> void rehash(int n)
  {
    if(n >= bucketcount())
    {
      std::vector<T> holder = buckets;
      buckets.clear(); //clear the table
      buckets.resize(n); //change size to n
      for(auto key : holder) //range based for loop to iterate through values
        insert(key); //insert keys
      holder.clear();
    }
  }

  ~HashTable() = default; //destructor, defaulted

};
#endif
