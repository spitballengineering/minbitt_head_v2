#include "connection.h"


int parse_old_iFacialmocap(char *iFacialmocap_str, blendshapes_t *blendshapes) {
    //trackingStatus-1|eyeLookIn_R-7|eyeLookUp_R-0|mouthSmile_L-3|...|eyeLookOut_L-0|hapihapi-0|=head#-5.0568147,0.51878923,-1.9728191,-0.0022842719,-0.026130209,-0.55329144|rightEye#6.593492,2.801933,0.32198337|leftEye#6.60017,-1.5836788,-0.18207395|
    //TODO: do proper input cleaning

    char *field = strtok(iFacialmocap_str, "-");
    char *val_str;
    int val;
    float cord;
    for (int i = 0; i < NUM_BLENDSHAPES + 1; ++i) {
        val_str = strtok(NULL, "|");
        val = (int) strtol(val_str, NULL, 10);
        blendshapes_set_field(blendshapes, field, val);
        // printf("%s: %d\n", field, val);
        field = strtok(NULL, "-");
    }
    strtok(NULL, "=");
    field = strtok(NULL, "#");
    for (int i = 0; i < 5; ++i) {
        val_str = strtok(NULL, ",");
        cord = strtof(val_str,NULL);
        // printf("%s: %2.2f\n", field, cord);
        *(&blendshapes->head.x+i) = cord; // jank
    }
    val_str = strtok(NULL, "|");
    cord = strtof(val_str,NULL);
    // printf("%s: %2.2f\n", field, cord);
    blendshapes->head.az = cord; // jank
    for (int i = 0; i < 2; ++i) {
        field = strtok(NULL, "#");
        for (int j = 0; j < 2; ++j) {
            val_str = strtok(NULL, ",");
            cord = strtof(val_str,NULL);
            // printf("%s: %2.2f\n", field, cord);
            *((float*)(&blendshapes->right_eye+i)+j) = cord; // jank
        }
        val_str = strtok(NULL, "|");
        cord = strtof(val_str,NULL);
        // printf("%s: %2.2f\n", field, cord);
        blendshapes->left_eye.z = cord;
    }

    return 0;
}

int read_old_iFacialmocap_recording(const connection_t connection, blendshapes_t *blendshapes) {
    char buff[2048]; //TODO: confirm size

    if (fgets(buff, sizeof(buff), connection.f) == NULL) {
        if (fseek(connection.f, 0, SEEK_SET)) {
            //TODO: print err log
            return 1;
        }

        fgets(buff, sizeof(buff), connection.f);
    }

    parse_old_iFacialmocap(buff, blendshapes);

    return 0;
}

connection_t init_mock_connection(char *filename) {
    printf("open file"); // TODO: change to log
    connection_t connection;
    connection.type = MOCK;
    if ((connection.f = fopen(filename, "r")) == NULL) {
        //TODO: print error log
        exit(1);
    }
    return connection;
}

connection_t init_phone_connection() {
    connection_t connection;
    connection.type = PHONE;
    connection.phone.ip = 0;
    connection.phone.port = 49983;
    return connection;
}

int deinit_connection(connection_t connection) {
    if (connection.type == MOCK) {
        fclose(connection.f);
    } else {
    }
    return 0;
}

int get_blendshapes(const connection_t connection, blendshapes_t *blendshapes) {
    // TODO: pass connecitons as ptr?
    if (connection.type == PHONE) {
        // from iPhone
    } else if (connection.type == MOCK) {
        // from prerecoreded file
        //TODO: maybe mux between the diffrent msg formats?
        return read_old_iFacialmocap_recording(connection, blendshapes);
    } else {
        // perror("invalid face_data mode");
        exit(1);
    }
}

int send_data(const connection_t connection) {
}
