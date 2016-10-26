#ifndef MASKS_H
#define MASKS_H

#include <stdint.h>

#include "TheGreatEscape/Types.h"

#define MASK_RUN_FLAG (1 << 7)

extern const uint8_t *mask_pointers[30];
extern const mask_t exterior_mask_data[58];

#endif /* MASKS_H */
