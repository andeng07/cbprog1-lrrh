#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

/* Represents the possible movement directions for a GameObject. */
typedef enum ObjectDirection {
    UP,
    RIGHT,
    DOWN,
    LEFT,
    UNDEFINED /* Direction not specified */
} ObjectDirection;

/* Enumerates all possible object types that can exist on the game pBoard. */
typedef enum ObjectType {
    LITTLE_RED_RIDING_HOOD, /* Player-controlled character */
    GRANNY,
    PIT,
    WOLF,
    WOODSMAN,
    BAKESHOP,
    FLOWER,
    EMPTY
} ObjectType;

typedef struct ObjectTypeMetadata {
    ObjectType type;
    int nIsCollissionPersistent;
    char *pName;
    char *pSenseName;
    char cLandmark;
} ObjectTypeMetadata;

/* Indicates the visibility nStatus of an object. */
typedef enum Status {
    HIDDEN,
    VISIBLE
} Status;

/* Represents an interactive entity within the game world. */
typedef struct GameObject {
    ObjectType type;
    ObjectDirection direction;
    Status status;
    int nPosX; /* X-coordinate of the object on the pBoard */
    int nPosY; /* Y-coordinate of the object on the pBoard */
} GameObject;

typedef enum RotationDirection {
    ROTATE_LEFT,
    ROTATE_RIGHT
} RotationDirection;

/* Rotates the object 90 degrees clockwise.
 * Precondition: pObj must not be NULL.
 * @param pObj Pointer to the GameObject to rotate.
 * @return None.
 */
void rotate(GameObject *pObj, RotationDirection direction);

/* Sets the position of a GameObject.
 * Precondition: pObj must not be NULL.
 * @param pObj Pointer to the GameObject.
 * @param nPosX New X-coordinate.
 * @param nPosY New Y-coordinate.
 * @return None.
 */
void setPosition(GameObject *pObj, int nPosX, int nPosY);

/* Calculates the coordinates directly in front of the pObj based on its direction.
 * Precondition: pObj must not be NULL.
 * @param pObj Pointer to the GameObject.
 * @param pOutX Pointer to an integer to store the resulting X-coordinate.
 * @param pOutY Pointer to an integer to store the resulting Y-coordinate.
 * @return 1 if the pObj's direction is not undefined; 0 otherwise.
 */
int getForwardCoordinate(GameObject *pObj, int *pOutX, int *pOutY);

/* Creates a new empty GameObject instance.
 * Precondition: none.
 * @param nPosX X-coordinate of the new object.
 * @param nPosY Y-coordinate of the new object.
 * @param nStatus Visibility nStatus of the object (HIDDEN or VISIBLE).
 * @return Pointer to a newly allocated empty GameObject.
 */
GameObject *emptyGameObject(int nPosX, int nPosY, Status status);

/* Converts an ObjectType enum value into its corresponding metadata.
 * Precondition: none.
 * @param type The ObjectType value to convert.
 * @return Pointer to the metadata representing the type name.
 */
ObjectTypeMetadata *getTypeMetadata(ObjectType type);

#endif /* GAME_OBJECT_H */