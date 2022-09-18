#pragma once
#include <deque>
#include <unordered_map>
#include "datastore.h"
#include "util.h"

class MyDataStore : public DataStore {
public:
    ~MyDataStore();

    /**
     * Adds a product to the data store
     */
    void addProduct(Product* p) override;

    /**
     * Adds a user to the data store
     */
    void addUser(User* u) override;

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> search(std::vector<std::string>& terms, int type) override;

    /**
     * Reproduce the database file from the current Products and User values
     */
    void dump(std::ostream& ofile) override;

    /**
     * Adds the specified Product from the search result to the User's cart
     */
    void addUserProduct(std::string username, int index);

    /**
     * Views the specified User's cart
     */
    void viewCart(std::string username);

    /**
     * Buys the specified User's cart
     * If some products cannot be bought, they are left in the cart
     */
    void buyCart(std::string username);

private:
    std::unordered_map<std::string, std::set<Product*>> products_;
    std::unordered_map<std::string, User*> users_;
    std::unordered_map<std::string, std::deque<Product*>> carts_;
    std::vector<Product*> searchresults_;
};

