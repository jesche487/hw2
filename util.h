#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
  std::set<T> returnset;

  //iterator through s1 elements, if it exists in s2, insert into return set
  //complexity: n log(n)
  for(const T& elem : s1) {
    if(s2.count(elem)) {
        returnset.insert(elem);
    }
  }

  return returnset;
}
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
  std::set<T> returnset;

  //insert all elements in both sets directly into set, since STL set will ensure all
  //elements are unique
  //complexity: n log(n)
  returnset = s1;
  for(const T&elem : s2) {
    returnset.insert(elem);
  }

  return returnset;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
