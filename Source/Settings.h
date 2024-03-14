//
// Created by oscar on 3/13/2024.
//

#ifndef FLAPPYBIRD_SETTINGS_H
#define FLAPPYBIRD_SETTINGS_H

#define PIPE_VERTICAL_GAP       100
#define PIPE_HORIZONTAL_GAP     (90 + 52)
#define PIPE_BOTTOM_MARGIN      40
#define PIPE_TOP_MARGIN         40

#define BIRD_RADIUS             14
#define PIPE_COUNT              3
#define HORIZONTAL_SPEED        100

/*
 * Physics collision bit and mask
 */
#define BIRD_BIT                1
#define GROUND_BIT              2
#define PIPE_BIT                4
#define COIN_BIT                8

#endif //FLAPPYBIRD_SETTINGS_H
