#include "GoogleAuthorization.h"
#include <iostream>
using namespace std;

void GoogleResponse::encode(CoderContainer* container) {
    if (container->type == CoderType::json) {
        JSONEncodeContainer* jsonContainer = dynamic_cast<JSONEncodeContainer*>(container);
        jsonContainer->encode(iss, "iss");
        jsonContainer->encode(sub, "sub");
        jsonContainer->encode(azp, "azp");
        jsonContainer->encode(aud, "aud");
        jsonContainer->encode(iat, "iat");
        jsonContainer->encode(exp, "exp");
    }
}

void GoogleResponse::decode(CoderContainer* container) {
    if (container->type == CoderType::json) {
        JSONDecodeContainer* jsonContainer = dynamic_cast<JSONDecodeContainer*>(container);
        iss = jsonContainer->decode(string(), "iss");
        sub = jsonContainer->decode(string(), "sub");
        azp = jsonContainer->decode(string(), "azp");
        aud = jsonContainer->decode(string(), "aud");
        iat = jsonContainer->decode(string(), "iat");
        exp = jsonContainer->decode(string(), "exp");
    }
}