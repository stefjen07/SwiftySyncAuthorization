#define SERVER
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
#ifdef CLIENT
    auto googleProvider = GoogleProvider();
    auto facebookProvider = FacebookProvider();
    cout << googleProvider.generateRequest("hello") << "\n";
    cout << facebookProvider.generateRequest("hello") << "\n";
#endif
#ifdef SERVER
    auto googleProvider = GoogleProvider("client_id");
    auto facebookProvider = FacebookProvider("access_token", "app_id");
    cout << googleProvider.isValid("G") << " " << facebookProvider.isValid("F") << "\n";
#endif


    cout << "Hello world!";
    return 0;
}
