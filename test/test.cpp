#define CLIENT
#define SERVER

#include "GoogleAuthorization.hpp"
#include "FacebookAuthorization.hpp"

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
    sGoogleProvider.authorize("G");
#endif


    cout << "Hello world!";
    return 0;
}
