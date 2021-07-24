#include "Authorization.h"
#include "FacebookAuthorization.h"
#include "GoogleAuthorization.h"

int main() {
    auto googleProvider = GoogleProvider();
    auto facebookProvider = FacebookProvider();
    
    cout << "Hello world!";
    return 0;
}
