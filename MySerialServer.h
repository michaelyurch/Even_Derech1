//
// Created by sharon_i4 on 04/01/2019.
//

#ifndef PROJ2_MYSERIALSERVER_H
#define PROJ2_MYSERIALSERVER_H

#include "Server.h"

namespace server_side {
    class MySerialServer : public Server {
    public:
        void open(int port);
        void stop();
    };
}

#endif //PROJ2_MYSERIALSERVER_H
