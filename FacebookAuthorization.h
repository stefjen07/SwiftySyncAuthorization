#ifndef FACEBOOK_AUTHORIZATION_H
#define FACEBOOK_AUTHORIZATION_H

#include "Usage.h"

#include "Authorization.h"
#include "Codable.h"
#include "JSON.h"
#include <string>

#define FACEBOOK_AUTH_PREFIX "F"

using namespace std;

class FacebookResponse : public Codable {
public:
	long long app_id, user_id, expires_at;

	void encode(CoderContainer* container);

	void decode(CoderContainer* container);
};

class FacebookProvider: public AuthorizationProvider {
public:
#ifdef SERVER
	string access_token;
	string app_id;

	AuthorizationResponse authorize(string body);

	bool isValid(string body);

	FacebookProvider(string access_token, string app_id) {
		this->access_token = access_token;
		this->app_id = app_id;
	}
#endif

#ifdef CLIENT
	string generateRequest(string body);

	FacebookProvider() {}
#endif
};

#endif
