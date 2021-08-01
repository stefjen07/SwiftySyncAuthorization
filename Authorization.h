#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include "Usage.h"
#include <string>

#ifdef SCAPIX_BRIDGE
#include <scapix/bridge/object.h>
#endif

#define AUTHORIZED_LOCALIZE "S"
#define CORR_CRED_LOCALIZE "C"
#define AUTH_ERR_LOCALIZE "E"

using namespace std;

enum class AuthorizationStatus {
	authorized,
	corruptedCredentials,
	error
};

#ifdef SCAPIX_BRIDGE
class AuthorizationResponse: public scapix::bridge::object<AuthorizationResponse> {
#else
class AuthorizationResponse {
#endif
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

#ifdef SCAPIX_BRIDGE
class AuthorizationProvider: public scapix::bridge::object<AuthorizationResponse> {
#else
class AuthorizationProvider {
#endif
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
