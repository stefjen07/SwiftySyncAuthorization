#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include "GoogleAuthorization.h"
#else
#include "Authorization.h"
#endif
#include "FacebookAuthorization.h"
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include "Authorization.h"
#else
#include "GoogleAuthorization.h"
#endif

int main() {
    auto googleProvider = GoogleProvider();
    auto facebookProvider = FacebookProvider();
    
    cout << "Hello world!";
    return 0;
}
