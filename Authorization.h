#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <Usage.h>
#include <string>

#define AUTHORIZED_LOCALIZE "S"
#define CORR_CRED_LOCALIZE "C"
#define AUTH_ERR_LOCALIZE "E"

using namespace std;

enum class AuthorizationStatus {
	authorized,
	corruptedCredentials,
	error
};

class AuthorizationResponse {
public:
	AuthorizationStatus status;
	string userId;

	AuthorizationResponse(AuthorizationStatus status, string userId) {
		this->status = status;
		this->userId = userId;
	}

	AuthorizationResponse() {
		status = AuthorizationStatus::error;
	}
};

class AuthorizationProvider {
public:
#ifdef SERVER
	virtual AuthorizationResponse authorize(string body) = 0;
	virtual bool isValid(string body) = 0;
#endif
#ifdef CLIENT
	virtual string generateRequest(string body) = 0;
#endif
};

#endif