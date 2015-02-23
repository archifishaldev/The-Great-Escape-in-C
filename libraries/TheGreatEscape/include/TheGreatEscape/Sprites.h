#ifndef SPRITES_H
#define SPRITES_H

#include "TheGreatEscape/SpriteBitmaps.h"

/**
 * A sprite (a bitmap + mask pair);
 */
typedef struct sprite
{
  uint8_t        width; /* in bytes + 1 */
  uint8_t        height;
  const uint8_t *bitmap;
  const uint8_t *mask;
}
sprite_t;

// in these names could s/TOP_LEFT/AWAY/ and s/BOTTOM_RIGHT/TOWARDS/
enum
{
  sprite_STOVE,
  sprite_CRATE,
  sprite_PRISONER_FACING_TOP_LEFT_4,
  sprite_PRISONER_FACING_TOP_LEFT_3,
  sprite_PRISONER_FACING_TOP_LEFT_2,
  sprite_PRISONER_FACING_TOP_LEFT_1,
  sprite_PRISONER_FACING_BOTTOM_RIGHT_1,
  sprite_PRISONER_FACING_BOTTOM_RIGHT_2,
  sprite_PRISONER_FACING_BOTTOM_RIGHT_3,
  sprite_PRISONER_FACING_BOTTOM_RIGHT_4,
  sprite_CRAWL_FACING_BOTTOM_LEFT_2,
  sprite_CRAWL_FACING_BOTTOM_LEFT_1,
  sprite_CRAWL_FACING_TOP_LEFT_1,
  sprite_CRAWL_FACING_TOP_LEFT_2,
  sprite_DOG_FACING_TOP_LEFT_1,
  sprite_DOG_FACING_TOP_LEFT_2,
  sprite_DOG_FACING_TOP_LEFT_3,
  sprite_DOG_FACING_TOP_LEFT_4,
  sprite_DOG_FACING_BOTTOM_RIGHT_1,
  sprite_DOG_FACING_BOTTOM_RIGHT_2,
  sprite_DOG_FACING_BOTTOM_RIGHT_3,
  sprite_DOG_FACING_BOTTOM_RIGHT_4,
  sprite_GUARD_FACING_TOP_LEFT_4,
  sprite_GUARD_FACING_TOP_LEFT_3,
  sprite_GUARD_FACING_TOP_LEFT_2,
  sprite_GUARD_FACING_TOP_LEFT_1,
  sprite_GUARD_FACING_BOTTOM_RIGHT_1,
  sprite_GUARD_FACING_BOTTOM_RIGHT_2,
  sprite_GUARD_FACING_BOTTOM_RIGHT_3,
  sprite_GUARD_FACING_BOTTOM_RIGHT_4,
  sprite_COMMANDANT_FACING_TOP_LEFT_4,
  sprite_COMMANDANT_FACING_TOP_LEFT_3,
  sprite_COMMANDANT_FACING_TOP_LEFT_2,
  sprite_COMMANDANT_FACING_TOP_LEFT_1,
  sprite_COMMANDANT_FACING_BOTTOM_RIGHT_1,
  sprite_COMMANDANT_FACING_BOTTOM_RIGHT_2,
  sprite_COMMANDANT_FACING_BOTTOM_RIGHT_3,
  sprite_COMMANDANT_FACING_BOTTOM_RIGHT_4,
  sprite__LIMIT
};

extern const sprite_t sprites[sprite__LIMIT];

#endif /* SPRITES_H */

