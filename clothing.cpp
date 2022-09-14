#include <sstream>
#include "clothing.h"
#include "util.h"

Clothing::Clothing(const std::string name, double price, int qty, 
           const std::string size, const std::string brand) :
    Product("clothing", name, price, qty),
    size_ (size),
    brand_ (brand)
{
  //automatically parses the keywords for this product during construction
  auto temp = parseStringToWords(name);
  auto temp2 = parseStringToWords(brand);
  keyword_ = setUnion(temp, temp2);
}

Clothing::~Clothing()
{

}

std::set<std::string> Clothing::keywords() const {
  return keyword_;
}

std::string Clothing::displayString() const {
  std::ostringstream ss;
  ss << category_ << " " << name_ << " " << price_ << " " 
     << qty_ << " " << size_ << " " << brand_;

  return ss.str();
}
 
void Clothing::dump(std::ostream& os) const {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" 
       << qty_ << "\n" << size_ << "\n" << brand_ << std::endl;
}

