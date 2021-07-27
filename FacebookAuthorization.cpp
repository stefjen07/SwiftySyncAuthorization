#include "FacebookAuthorization.h"
#include <iostream>

using namespace std;

void FacebookResponse::encode(CoderContainer* container) {
    if (container->type == CoderType::json) {
        JSONEncodeContainer* jsonContainer = dynamic_cast<JSONEncodeContainer*>(container);
        jsonContainer->encode(app_id, "app_id");
        jsonContainer->encode(user_id, "user_id");
        jsonContainer->encode(expires_at, "expires_at");
    }
}

void FacebookResponse::decode(CoderContainer* container) {
    if (container->type == CoderType::json) {
        JSONDecodeContainer* jsonContainer = dynamic_cast<JSONDecodeContainer*>(container);
        app_id = jsonContainer->decode(0LL, "app_id");
        user_id = jsonContainer->decode(0LL, "user_id");
        expires_at = jsonContainer->decode(0LL, "expires_at");
    }
}