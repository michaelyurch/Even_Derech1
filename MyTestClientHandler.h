#ifndef PROJ2_MYTESTCLIENTHANDLER_H
#define PROJ2_MYTESTCLIENTHANDLER_H

#include "ClientHandler.h"

namespace server_side {
    class MyTestClientHandler : public ClientHandler {
    public:
        void handleClient(const std::istream &in, std::ostream &out);
    };
}


#endif //PROJ2_MYTESTCLIENTHANDLER_H
