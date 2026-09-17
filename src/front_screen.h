//
// Created by Spitball Engineering on 9/11/26.
//

#ifndef MINBITT_HEAD_V2_FRONT_SCREEN_H
#define MINBITT_HEAD_V2_FRONT_SCREEN_H

//should support HUB75, mipi, hdmi, etc... at varous resoultions
void draw_to_front_screen(Image* front_screen_buff) {

    //TODO: split into mango pi and desktop

    ImageDrawCircle(front_screen_buff, 10,10, 5, MINBITT_BLUE);// DEBUG
}

#endif //MINBITT_HEAD_V2_FRONT_SCREEN_H