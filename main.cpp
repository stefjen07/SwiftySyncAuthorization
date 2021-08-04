#define CLIENT
#define SERVER

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include "GoogleAuthorization.hpp"
#endif
#include "FacebookAuthorization.hpp"
#if !(defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__))
#include "GoogleAuthorization.hpp"
#endif
using namespace std;

int main() {
#ifdef CLIENT
    auto googleProvider = GoogleProvider();
    auto facebookProvider = FacebookProvider();
    cout << googleProvider.generateRequest("hello") << "\n";
    cout << facebookProvider.generateRequest("hello") << "\n";
#endif
#ifdef SERVER
    auto sGoogleProvider = GoogleProvider("client_id");
    auto sFacebookProvider = FacebookProvider("access_token", "app_id");
    cout << sGoogleProvider.isValid("G") << " " << sFacebookProvider.isValid("F") << "\n";
#endif


    cout << "Hello world!";
    return 0;
}
