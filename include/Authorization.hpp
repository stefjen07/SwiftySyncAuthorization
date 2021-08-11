#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <string>

#define AUTHORIZED_LOCALIZE "S"
#define CORR_CRED_LOCALIZE "C"
#define AUTH_ERR_LOCALIZE "E"

enum class AuthorizationStatus {
	authorized,
	corruptedCredentials,
	error
};

class AuthorizationResponse {
public:
	AuthorizationStatus status;
	std::string userId;

	AuthorizationResponse(AuthorizationStatus status, std::string userId) {
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
    virtual AuthorizationResponse authorize(std::string body) = 0;
	virtual bool isValid(std::string body) = 0;
#endif
#ifdef CLIENT
	virtual std::string generateRequest(std::string body) = 0;
#endif
};

#endif
