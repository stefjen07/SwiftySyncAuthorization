#ifndef GOOGLE_AUTHORIZATION_H 
#define GOOGLE_AUTHORIZATION_H

#include "Usage.h"

#define CPPHTTPLIB_OPENSSL_SUPPORT

#ifdef SERVER
#include "httplib.h"
#endif
#include "Codable.hpp"
#include "JSON.hpp"
#include "Authorization.hpp"
#include <string>

#define GOOGLE_AUTH_PREFIX "G"

class GoogleResponse : public Codable {
public:
	std::string iss, sub, azp, aud, iat, exp;

	void encode(CoderContainer* container);

	void decode(CoderContainer* container);
};

class GoogleProvider: public AuthorizationProvider {
public:
#ifdef SERVER
    std::string client_id;

    AuthorizationResponse authorize(std::string body) {
        AuthorizationResponse result;
        result.status = AuthorizationStatus::error;
        std::string token = body;
        httplib::SSLClient cli("https://oauth2.googleapis.com");
        httplib::Params params;
        params.emplace("id_token", token);

        auto response = cli.Post("/tokeninfo", params);

        if (response == nullptr) {
#ifdef AUTH_DEBUG
            cout << "There is no response for request\n";
#endif
        }
        else {
            if (response->status == 200) {
                JSONDecoder decoder;
                auto container = decoder.container(response->body);
                const auto decoded = container.decode(GoogleResponse());
                if (decoded.aud == client_id) {
                    result.status = AuthorizationStatus::authorized;
                    result.userId = GOOGLE_AUTH_PREFIX + decoded.sub;
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
        return body.find(GOOGLE_AUTH_PREFIX) == 0;
    }

	GoogleProvider(std::string client_id) {
		this->client_id = client_id;
	}
#endif

#ifdef CLIENT
    std::string generateRequest(std::string body) {
        return GOOGLE_AUTH_PREFIX + body;
    }

	GoogleProvider() {}
#endif
};

#endif
