#ifndef GOOGLE_AUTHORIZATION_H 
#define GOOGLE_AUTHORIZATION_H

#include "Usage.h"

#define CPPHTTPLIB_OPENSSL_SUPPORT

#include "httplib.h"
#include "Codable.h"
#include "JSON.h"
#include "Authorization.h"
#include <string>

#define GOOGLE_AUTH_PREFIX "G"

using namespace std;

class GoogleResponse : public Codable {
public:
	string iss, sub, azp, aud, iat, exp;

	void encode(CoderContainer* container);

	void decode(CoderContainer* container);
};

class GoogleProvider: public AuthorizationProvider {
public:
#ifdef SERVER
	string client_id;

	AuthorizationResponse authorize(string body);

	bool isValid(string body);

	GoogleProvider(string client_id) {
		this->client_id = client_id;
	}
#endif

#ifdef CLIENT
	string generateRequest(string body);

	GoogleProvider() {}
#endif
};

#endif
