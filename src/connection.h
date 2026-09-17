//
// Created by Spitball Engineering on 9/11/26.
//

#ifndef MINBITT_HEAD_V2_CONNECTION_H
#define MINBITT_HEAD_V2_CONNECTION_H

//FIXME: needed for exit
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "raylib.h"

#include "blendshapes.h"

typedef struct {
    enum conneciton_type { PHONE, MOCK } type;

    union {
        struct {
            int ip;
            int port;
        } phone;

        FILE *f;
    };
} connection_t;

connection_t init_mock_connection(char*filename);
connection_t init_phone_connection();
int deinit_connection(connection_t connection);

int get_blendshapes(const connection_t connection, blendshapes_t *blendshapes);


int send_data(const connection_t connection);

#endif //MINBITT_HEAD_V2_CONNECTION_H