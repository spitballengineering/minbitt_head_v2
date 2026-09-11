//
// Created by Spitball Engineering on 9/11/26.
//

#ifndef MINBITT_HEAD_V2_CONNECTION_H
#define MINBITT_HEAD_V2_CONNECTION_H

//FIXME: needed for exit
#include <stdlib.h>
#include "blendshapes.h"

typedef struct {
    enum { PHONE, MOCK } type;

    union {
        struct {
            int ip;
            int port;
        } phone;

        char *path;
    };
} connection_t;

void get_blendshapes(const connection_t connection, blendshapes *blendshapes);


int send_data(const connection_t connection);

#endif //MINBITT_HEAD_V2_CONNECTION_H