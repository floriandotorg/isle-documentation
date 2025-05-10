#ifndef __VERSION_H
#define __VERSION_H

/**
 * @def MODEL_VERSION
 * @brief [AI] Represents the version number of the game model/resources. Used for resource management and compatibility checks between code and data files.
 * @details [AI] This version number should be incremented when the structure of game models or associated resources has changed in an incompatible way (such as new/removed fields or significant data layout changes) to force proper handling in loaders or tools that depend on a matching version. [AI]
 */
#define MODEL_VERSION 19

#endif // __VERSION_H