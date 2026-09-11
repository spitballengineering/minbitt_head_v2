#include "connection.h"

void get_blendshapes(const connection_t connection, blendshapes *blendshapes) {
    // TODO: pass connecitons as ptr?
    if (connection.type == PHONE) {
        // from iPhone
    } else if (connection.type == MOCK) {
        // from prerecoreded file
    } else {
        // perror("invalid face_data mode");
        exit(1);
    }
}

int send_data(const connection_t connection) {

}

