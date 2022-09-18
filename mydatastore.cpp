#include "mydatastore.h"

MyDataStore::~MyDataStore() {
  //deletes all Product and User pointers when the destructor is called to avoid memory leaks
  std::set<Product*> allproducts;
  for(std::pair<std::string, std::set<Product*>> tempproduct : products_) {
    allproducts = setUnion(allproducts, tempproduct.second);
  }

  std::set<User*> allusers;
  for(std::pair<std::string, User*> tempuser : users_) {
    allusers.insert(tempuser.second);
  }

  for(Product* p : allproducts) {
    delete p;
  }

  for(User* u : allusers) {
    delete u;
  }
}

/**
* Adds a product to the data store
*/
void MyDataStore::addProduct(Product* p) 
{
  //iterates through all keywords of the product,
  //will add the product to a set of other products that contain the same keyword
  for(std::string str : p->keywords()) {
    products_[str].insert(p);
  }
}

/**
* Adds a user to the data store
*/
void MyDataStore::addUser(User* u)
{
  //adds users to two maps, one map to find the User by string username easily,
  //and the other to find their cart easily
  users_[convToLower(u->getName())] = u;
  carts_[convToLower(u->getName())];
}

/**
* Performs a search of products whose keywords match the given "terms"
*  type 0 = AND search (intersection of results for each term) while
*  type 1 = OR search (union of results for each term)
*/
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
  searchresults_.clear();

  //if the user enters only AND or OR with no keywords, return
  if(terms.empty()) return searchresults_;

  std::set<Product*> temp = products_[terms[0]];

  //AND case
  if(type == 0) {
    for(unsigned i = 1; i < terms.size(); i++) {
      if(products_.count(terms[i])) {
        temp = setIntersection(temp, products_[terms[i]]);
      }
      //the moment the keyword does not exist, break, since an intersection does not exist
      else {
        temp.clear();
        break;
      }
    }
  }
  //OR case
  else {
    for(unsigned i = 1; i < terms.size(); i++) {
      //no need to break, can just add all sets together
      if(products_.count(terms[i])) {
        temp = setUnion(temp, products_[terms[i]]);
      }
    }
  }

  for(Product* pp : temp) {
    searchresults_.push_back(pp);
  }

  //sorts vector to match the displayed search results
  //this is so the hit_index the user types matches up with what is internally stored
  std::sort(searchresults_.begin(), searchresults_.end(), [](Product* a, Product* b){return a->getName() < b->getName();});

  return searchresults_;
}

/**
* Reproduce the database file from the current Products and User values
*/
void MyDataStore::dump(std::ostream& ofile) {
  std::set<Product*> allproducts;
  for(std::pair<std::string, std::set<Product*>> tempproduct : products_) {
    allproducts = setUnion(allproducts, tempproduct.second);
  }

  std::set<User*> allusers;
  for(std::pair<std::string, User*> tempuser : users_) {
    allusers.insert(tempuser.second);
  }

  ofile << "<products>" << std::endl;
  for(Product* p : allproducts) {
    p->dump(ofile);
  }
  ofile << "</products>" << std::endl;
  ofile << "<users>" << std::endl;
  for(User* u : allusers) {
    u->dump(ofile);
  }
  ofile << "</user>" << std::endl;
}

void MyDataStore::addUserProduct(std::string username, int index) {
  //checks for invalid entries
  if(index > int(searchresults_.size()) || index <= 0) {
    std::cout << "Invalid Request" << std::endl;
    return;
  }

  if(users_.count(username) == 0) {
    std::cout << "Invalid Request" << std::endl;
    return;
  }

  //adds the product to user's corresponding cart
  carts_[username].push_back(searchresults_[index - 1]);
}

void MyDataStore::viewCart(std::string username) {
  //checks for invalid entries
  if(users_.count(username) == 0) {
    std::cout << "Invalid Username" << std::endl;
  }

  //displays user's cart
  for(Product* p : carts_[username]) {
    std::cout << p->displayString() << std::endl;
  }
}

void MyDataStore::buyCart(std::string username) {
  //checks for invalid entries
  if(users_.count(username) == 0) {
    std::cout << "Invalid Username" << std::endl;
  }

  int size = carts_[username].size();

  //loops through the user's carts, checking if each item can be bought or not
  while(size > 0) {
    Product* p = carts_[username].front();
    carts_[username].pop_front();
    //if it can be bought, subtract qty and price
    //if it cannot be bought, push to the back of the cart
    if(p->getQty() > 0 && users_[username]->getBalance() - p->getPrice() >= 0) {
      users_[username]->deductAmount(p->getPrice());
      p->subtractQty(1);
    }
    else {
      carts_[username].push_back(p);
    }

    size--;
  }

}
