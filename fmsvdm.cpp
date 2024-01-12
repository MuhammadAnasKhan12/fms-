#include <iostream>
#include <map>
#include <vector>

typedef unsigned int ProductID;
typedef double Product;
typedef unsigned int UserID;

struct CartItem
{
    ProductID productID;
    unsigned int quantity;
};

typedef std::map<UserID, std::vector<CartItem > > ShoppingCart;

const unsigned int MAX_PRODUCTS = 100;
const unsigned int MAX_QUANTITY = 10;

class OnlineShoppingCartSystem
{
public:
    std::map<ProductID, Product> productCatalog;
    ShoppingCart userCarts;

    OnlineShoppingCartSystem() {}

    void addProduct(ProductID productID, Product price)
    {
        if (productCatalog.find(productID) == productCatalog.end())
        {
            productCatalog[productID] = price;
        }
    }

    bool inProductCatalog(ProductID productID)
    {
        return productCatalog.find(productID) != productCatalog.end();
    }

    bool inCart(const std::vector<CartItem> &userCart)
    {
        for (std::vector<CartItem>::const_iterator it = userCart.begin(); it != userCart.end(); ++it)
        {
            if (!inProductCatalog(it->productID))
            {
                return false;
            }
        }
        return true;
    }

    void addToCart(UserID userID, const std::vector<CartItem> &cartItems)
    {
        if (inCart(cartItems))
        {
            userCarts[userID].insert(userCarts[userID].end(), cartItems.begin(), cartItems.end());
        }
    }

    void removeFromCart(UserID userID, ProductID productID)
    {
        std::vector<CartItem> &cart = userCarts[userID];
        for (std::vector<CartItem>::iterator it = cart.begin(); it != cart.end(); ++it)
        {
            if (it->productID == productID)
            {
                cart.erase(it);
                break; // Assuming each product appears only once in the cart
            }
        }
    }

    void clearCart(UserID userID)
    {
        userCarts[userID].clear();
    }
};

int main()
{
    OnlineShoppingCartSystem system;

    // Test Case 1: Add products to the catalog
    system.addProduct(1, 29.99);
    system.addProduct(2, 19.99);

    // Test Case 2: Create cart items
    std::vector<CartItem> cartItems;
    CartItem item1 = {1, 2};
    CartItem item2 = {2, 1};
    cartItems.push_back(item1);
    cartItems.push_back(item2);

    // Test Case 3: Add items to the cart
    if (system.inCart(cartItems))
    {
        std::cout << "Adding items to cart for user Anas\n";
        system.addToCart(123, cartItems);
    }

    // Test Case 4: Remove a product from the cart
    std::cout << "Removing product 1 from cart for user Anas\n";
    system.removeFromCart(123, 1);

    // Test Case 5: Clear the cart
    std::cout << "Clearing cart for user Anas\n";
    system.clearCart(123);

    // Print the contents of userCarts
    std::cout << "Contents of userCarts:\n";
    for (ShoppingCart::iterator it = system.userCarts.begin(); it != system.userCarts.end(); ++it)
    {
        std::cout << "User " << it->first << " - ";
        for (std::vector<CartItem>::iterator ci = it->second.begin(); ci != it->second.end(); ++ci)
        {
            std::cout << "(ProductID: " << ci->productID << ", Quantity: " << ci->quantity << ") ";
        }
        std::cout << "\n";
    }

    return 0;
}

