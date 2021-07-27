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

    AuthorizationResponse authorize(string body) {
        string input_token = body;
        AuthorizationResponse result;
        result.status = AuthorizationStatus::error;
        httplib::SSLClient cli("https://graph.facebook.com");
        httplib::Params params;
        params.emplace("input_token", input_token);
        params.emplace("access_token", access_token);

        auto response = cli.Post("/debug_token", params);

        if (response == nullptr) {
#ifdef AUTH_DEBUG
            cout << "There is no response for request\n";
#endif
        }
        else {
            if (response->status == 200) {
                JSONDecoder decoder;
                auto container = decoder.container(response->body);
                const auto decoded = container.decode(FacebookResponse(), "data");
                if (to_string(decoded.app_id) == app_id) {
                    result.status = AuthorizationStatus::authorized;
                    result.userId = FACEBOOK_AUTH_PREFIX + to_string(decoded.user_id);
                }
            }
            else {
#ifdef AUTH_DEBUG
                cout << "Request returned " << response->status << "\n";
#endif
            }
        }

        return result;
    }

    bool isValid(string body) {
        return body.find(FACEBOOK_AUTH_PREFIX) == 0;
    }

	FacebookProvider(string access_token, string app_id) {
		this->access_token = access_token;
		this->app_id = app_id;
	}
#endif

#ifdef CLIENT
    string generateRequest(string body) {
        return FACEBOOK_AUTH_PREFIX + body;
    }

	FacebookProvider() {}
#endif
};

#endif
