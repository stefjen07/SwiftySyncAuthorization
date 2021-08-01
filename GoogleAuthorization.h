#ifndef GOOGLE_AUTHORIZATION_H 
#define GOOGLE_AUTHORIZATION_H

#include "Usage.h"

#define CPPHTTPLIB_OPENSSL_SUPPORT

#ifdef SCAPIX_BRIDGE
#include <scapix/bridge/object.h>
#endif

#include "httplib.h"
#include "Codable.h"
#include "JSON.h"
#include "Authorization.h"
#include <string>

#define GOOGLE_AUTH_PREFIX "G"

using namespace std;

#ifdef SCAPIX_BRIDGE
class GoogleResponse: public Codable, scapix::bridge::object<AuthorizationResponse> {
#else
class GoogleResponse: public Codable {
#endif
public:
	string iss, sub, azp, aud, iat, exp;

	void encode(CoderContainer* container);

	void decode(CoderContainer* container);
};

#ifdef SCAPIX_BRIDGE
class GoogleProvider: public AuthorizationProvider, scapix::bridge::object<AuthorizationResponse> {
#else
class GoogleProvider: public AuthorizationProvider {
#endif
public:
#ifdef SERVER
	string client_id;

    AuthorizationResponse authorize(string body) {
        AuthorizationResponse result;
        result.status = AuthorizationStatus::error;
        string token = body;
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

    bool isValid(string body) {
        return body.find(GOOGLE_AUTH_PREFIX) == 0;
    }

	GoogleProvider(string client_id) {
		this->client_id = client_id;
	}
#endif

#ifdef CLIENT
    string generateRequest(string body) {
        return GOOGLE_AUTH_PREFIX + body;
    }

	GoogleProvider() {}
#endif
};

#endif
