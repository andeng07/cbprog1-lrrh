#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

/* Represents the possible movement directions for a GameObject. */
typedef enum ObjectDirection {
    UP,
    RIGHT,
    DOWN,
    LEFT,
    UNDEFINED // Direction not specified
} ObjectDirection;

/* Enumerates all possible object types that can exist on the game board. */
typedef enum ObjectType {
    LITTLE_RED_RIDING_HOOD, // Player-controlled character
    GRANNY,
    PIT,
    WOLF,
    WOODSMAN,
    BAKESHOP,
    FLOWER,
    EMPTY
} ObjectType;

/* Indicates the visibility status of an object. */
typedef enum Status {
    HIDDEN,
    VISIBLE
} Status;

/* Represents an interactive entity within the game world. */
typedef struct GameObject {
    ObjectType type;
    ObjectDirection direction;
    Status status;
    int x; // X-coordinate of the object on the board
    int y; // Y-coordinate of the object on the board
} GameObject;

/* Rotates the object 90 degrees clockwise.
 * Precondition: obj must not be NULL.
 * @param obj Pointer to the GameObject to rotate.
 * @return None.
 */
void rotate(GameObject *obj);

/* Sets the position of a GameObject.
 * Precondition: obj must not be NULL.
 * @param obj Pointer to the GameObject.
 * @param x New X-coordinate.
 * @param y New Y-coordinate.
 * @return None.
 */
void set_pos(GameObject *obj, int x, int y);

/* Calculates the coordinates directly in front of the object based on its direction.
 * Precondition: object must not be NULL.
 * @param object Pointer to the GameObject.
 * @param out_x Pointer to an integer to store the resulting X-coordinate.
 * @param out_y Pointer to an integer to store the resulting Y-coordinate.
 * @return 1 if the object's direction is not undefined; 0 otherwise.
 */
int get_forward_coordinate(GameObject *object, int *out_x, int *out_y);

/* Creates a new empty GameObject instance.
 * Precondition: none.
 * @param x X-coordinate of the new object.
 * @param y Y-coordinate of the new object.
 * @param status Visibility status of the object (HIDDEN or VISIBLE).
 * @return Pointer to a newly allocated empty GameObject.
 */
GameObject *empty_game_object(int x, int y, Status status);

/* Converts an ObjectType enum value into its corresponding name string.
 * Precondition: none.
 * @param type The ObjectType value to convert.
 * @return Pointer to a string representing the type name.
 */
char *get_type_name(ObjectType type);

#endif // GAME_OBJECT_H