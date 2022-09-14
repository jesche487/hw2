#include <sstream>
#include "movie.h"
#include "util.h"

Movie::Movie(const std::string name, double price, int qty, 
           const std::string genre, const std::string rating) :
    Product("movie", name, price, qty),
    genre_ (genre),
    rating_ (rating)
{
  //automatically parses the keywords for this product during construction
  auto temp = parseStringToWords(name);
  auto temp2 = parseStringToWords(genre);
  keyword_ = setUnion(temp, temp2);
}

Movie::~Movie()
{

}

std::set<std::string> Movie::keywords() const {
  return keyword_;
}

std::string Movie::displayString() const {
  std::ostringstream ss;
  ss << category_ << " " << name_ << " " << price_ << " " 
     << qty_ << " " << genre_ << " " << rating_;

  return ss.str();
}
 
void Movie::dump(std::ostream& os) const {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" 
       << qty_ << "\n" << genre_ << "\n" << rating_ << std::endl;
}

