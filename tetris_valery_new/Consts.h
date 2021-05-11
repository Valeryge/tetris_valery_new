#ifndef CONSTS_H
#define CONSTS_H

#define BOARD_WIDTH 14
#define BOARD_HEIGHT 19
#define POS_FILLED_CHAR 219
#define BORDER_CHAR 240
#define NUM_OF_POINTS 4
#define LEFT_PLAYER_POS 0
#define RIGHT_PLAYER_POS 14
#define PIECE_START_POS 5
#define SHAPE_SIZE 4

#define BOMB_PROB 30
#define BOMB_SHAPE 64

#define START_NEW_GAME_HUMAN_VS_HUMAN '1'
#define START_NEW_GAME_HUMAN_VS_COMPUTER '2'
#define START_NEW_GAME_COMPUTER_VS_COMPUTER '3'
#define STOP_AND_CONTINUE_KEY '4'
#define INFO_KEY '8'
#define EXIT_KEY '9'
#define ESCAPE 27

#define SLEEP_TIME 500
#define GAME_OVER_SLEEP_TIME 1000

#define PRINT_WINNER_X_LOCATION 10
#define PRINT_WINNER_Y_LOCATION 5

#define LEFT_PLAYER_LEFT_KEY 65 //A
#define LEFT_PLAYER_RIGHT_KEY 68 //D
#define LEFT_PLAYER_CLOCKWISE_KEY 83 // S
#define LEFT_PLAYER_COUNTERCLOCKWISE_KEY 87 //W 
#define LEFT_PLAYER_DROP_KEY 88//X

#define RIGHT_PLAYER_LEFT_KEY 74 //J
#define RIGHT_PLAYER_RIGHT_KEY 76 //L
#define RIGHT_PLAYER_CLOCKWISE_KEY 75 // K
#define RIGHT_PLAYER_COUNTERCLOCKWISE_KEY 73 //I 
#define RIGHT_PLAYER_DROP_KEY 77 // M

const char shapeOptions[7][4][4][4] = {
    // Square
      {
       {
        {0, 0, 1, 1},
        {0, 0, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
        },
       {
        {0, 0, 1, 1},
        {0, 0, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        },
       {
        {0, 0, 1, 1},
        {0, 0, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
        },
       {
        {0, 0, 1, 1},
        {0, 0, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
        },
       },

    // I
      {
       {
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},

        },
       {
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0}
        },
       {
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        },
       {
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0}
        },
       }
      ,
    // L
      {
       {
        {0, 1, 1, 1},
        {0, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        },
       {
        {0, 1, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0}
        },
       {
        {0, 0, 0, 1},
        {0, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
        },
    {
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 1},
        {0, 0, 0, 0}
        }
       },
    // L mirrored
      {
       {
        {0, 1, 1, 1},
        {0, 0, 0, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
        },
       {
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
        },
       {
        {0, 1, 0, 0},
        {0, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
        },
       {
        {0, 0, 1, 1},
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0}
        }
       },
    // N
      {
       {
        {0, 0, 0, 1},
        {0, 0, 1, 1},
        {0, 0, 1, 0},
        {0, 0, 0, 0}
        },
       {
        {0, 1, 1, 0},
        {0, 0, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
        },
       {
        {0, 0, 0, 1},
        {0, 0, 1, 1},
        {0, 0, 1, 0},
        {0, 0, 0, 0}
        },
       {
        {0, 1, 1, 0},
        {0, 0, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
        }
       },
    // N mirrored
      {
       {
        {0, 0, 1, 0},
        {0, 0, 1, 1},
        {0, 0, 0, 1},
        {0, 0, 0, 0}
        },
       {
        {0, 0, 1, 1},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
        },
       {
        {0, 0, 1, 0},
        {0, 0, 1, 1},
        {0, 0, 0, 1},
        {0, 0, 0, 0}
        },
       {
        {0, 0, 1, 1},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
        }
       },
    // T
      {
       {
        {0, 1, 1, 1},
        {0, 0, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
        },
       {
        {0, 0, 0, 1},
        {0, 0, 1, 1},
        {0, 0, 0, 1},
        {0, 0, 0, 0}
        },
       {
        {0, 0, 1, 0},
        {0, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
        },
       {
        {0, 0, 1, 0},
        {0, 0, 1, 1},
        {0, 0, 1, 0},
        {0, 0, 0, 0}
        }
       }
};

#endif CONSTS_H
