#ifndef FACEBOOK_AUTHORIZATION_H
#define FACEBOOK_AUTHORIZATION_H

#define CPPHTTPLIB_OPENSSL_SUPPORT

#include "Usage.h"

#ifdef SERVER
#include "httplib.h"
#endif
#include "Authorization.hpp"
#include "Codable.hpp"
#include "JSON.hpp"
#include <string>

#define FACEBOOK_AUTH_PREFIX "F"

class FacebookResponse : public Codable {
public:
	long long app_id, user_id, expires_at;

	void encode(CoderContainer* container);

	void decode(CoderContainer* container);
};

class FacebookProvider: public AuthorizationProvider {
public:
#ifdef SERVER
    std::string access_token;
	std::string app_id;

    AuthorizationResponse authorize(std::string body) {
        std::string input_token = body;
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
                if (std::to_string(decoded.app_id) == app_id) {
                    result.status = AuthorizationStatus::authorized;
                    result.userId = FACEBOOK_AUTH_PREFIX + std::to_string(decoded.user_id);
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

    bool isValid(std::string body) {
        return body.find(FACEBOOK_AUTH_PREFIX) == 0;
    }

	FacebookProvider(std::string access_token, std::string app_id) {
		this->access_token = access_token;
		this->app_id = app_id;
	}
#endif

#ifdef CLIENT
    std::string generateRequest(std::string body) {
        return FACEBOOK_AUTH_PREFIX + body;
    }

	FacebookProvider() {}
#endif
};

#endif
