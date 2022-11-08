#include <sstream>
#include "book.h"
#include "util.h"

Book::Book(const std::string name, double price, int qty, 
           const std::string author, const std::string ISBN) :
    Product("book", name, price, qty),
    author_ (author),
    ISBN_ (ISBN)
{
  //automatically parses the keywords for this product during construction
  std::set<std::string> temp = parseStringToWords(name);
  std::set<std::string> temp2 = parseStringToWords(author);
  keyword_ = setUnion(temp, temp2);
  keyword_.insert(ISBN);
}

Book::~Book()
{

}

std::set<std::string> Book::keywords() const {
  return keyword_;
}

std::string Book::displayString() const {
  std::ostringstream ss;
  ss << name_ << "\n"
     << "Author: " << author_ << " ISBN: " << ISBN_ <<  "\n"
     << price_ << " " << qty_ << " left." << "\n";
     
  return ss.str();
}
 
void Book::dump(std::ostream& os) const {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" 
       << qty_ << "\n" << ISBN_<< "\n" << author_  << std::endl;
}

