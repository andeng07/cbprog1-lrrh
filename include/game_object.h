#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

typedef enum ObjectDirection {
    UP,
    RIGHT,
    DOWN,
    LEFT,
    UNDEFINED
} ObjectDirection;

typedef enum ObjectType {
    LITTLE_RED_RIDING_HOOD,
    GRANNY,
    PIT,
    WOLF,
    WOODSMAN,
    BAKESHOP,
    FLOWER,
    EMPTY
} ObjectType;

typedef enum Status {
    HIDDEN, VISIBLE
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

//  1: success, 2: failure
int get_forward_coordinate(GameObject *object, int *outX, int *outY);

GameObject *empty_game_object(int x, int y, Status status);

char* get_type_name(ObjectType type);

#endif // GAME_OBJECT_H