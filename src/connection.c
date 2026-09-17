#include "connection.h"


int parse_old_iFacialmocap(char *iFacialmocap_str, blendshapes_t *blendshapes) {
    //trackingStatus-1|eyeLookIn_R-7|eyeLookUp_R-0|mouthSmile_L-3|...|eyeLookOut_L-0|hapihapi-0|=head#-5.0568147,0.51878923,-1.9728191,-0.0022842719,-0.026130209,-0.55329144|rightEye#6.593492,2.801933,0.32198337|leftEye#6.60017,-1.5836788,-0.18207395|
    //TODO: do proper input cleaning

    char field[256];
    int offset = 0;
    int str_index = 0;

    int val = 0;
    while (iFacialmocap_str[str_index] != '=') {
        if (iFacialmocap_str[str_index] == '|') {
            strncpy(field, &iFacialmocap_str[offset], str_index-offset); //TODO: find safe solution
            field[str_index-offset] = '\0';
            // snprintf(field, str_index - offset, "%s", &iFacialmocap_str[offset]);
            // sscanf(buff, "%s-%d", field, &val);
            int split_index;
            for (split_index = str_index-offset; split_index > str_index-offset-3; --split_index) //TODO: check if correct
                if (field[split_index] == '-')
                    break;

            field[split_index] = '\0';
            val = (int)strtol(&field[split_index+1], NULL, 10);

            // printf("%s: %d\n", field, val);
            blendshapes_set_field(blendshapes, field, val);
            offset = str_index + 1;
        }
        str_index++;
    }
    str_index++;
    offset = str_index;
    bool first_time = true;
    float x, y, z, rx, ry, rz;
    while (iFacialmocap_str[str_index] != '\0') {
        if (iFacialmocap_str[str_index] == '|') {
            snprintf(field, str_index - offset, "%s", &iFacialmocap_str[offset]);
            //TODO: sscanf is sus
            if (first_time) sscanf(field, "%s#%f,%f,%f,%f,%f,%f", field, &x, &y, &z, &rx, &ry, &rz);
            else sscanf(field, "%s#%f,%f,%f", field, &x, &y, &z);
            first_time = false;
            // printf("%s: %f, %f, %f\n", val, x, y, z);
            offset = str_index + 1;
        }
        str_index++;
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
