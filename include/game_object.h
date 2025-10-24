#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

typedef enum ObjectDirection {
    UP,
    DOWN,
    LEFT, 
    RIGHT, 
    UNDEFINED
} ObjectDirection;

typedef enum ObjectType {
    LITTLE_RED_RIDING_HOOD,
    GRANNY,
    PIT,
    WOODSMAN,
    BAKESHOP,
    FLOWER,
    EMPTY
} ObjectType;

typedef enum Status {
    VISIBLE, HIDDEN
} Status;

typedef struct GameObject {
    ObjectType type;
    ObjectDirection direction;
    Status status;
    int x;
    int y;
} GameObject;

void rotate(GameObject *obj); 

void set_pos(GameObject *obj, int x, int y);

GameObject *empty_game_object(int x, int y, Status status);

#endif // GAME_OBJECT_H