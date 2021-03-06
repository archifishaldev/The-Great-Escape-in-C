#include <assert.h>
#include <string.h>

#include "TheGreatEscape/Main.h"
#include "TheGreatEscape/Messages.h"
#include "TheGreatEscape/State.h"
#include "TheGreatEscape/Text.h"

/* ----------------------------------------------------------------------- */

/* $7D87 */
static void wipe_message(tgestate_t *state);
/* $7D99 */
static void next_message(tgestate_t *state);

/* ----------------------------------------------------------------------- */

#define message_NEXT (1 << 7)

/* ----------------------------------------------------------------------- */

/**
 * $7D15: Add a message to the pending messages queue.
 *
 * Conversion note: The original code accepts BC combined as the message
 * index. However only one of the callers sets up C. We therefore ignore the
 * second argument here, treating it as zero.
 *
 * \param[in] state         Pointer to game state.
 * \param[in] message_index The message_t to display. (was B)
 */
void queue_message_for_display(tgestate_t *state,
                               message_t   message_index)
{
  uint8_t *qp; /* was HL */

  assert(state != NULL);
  assert(message_index >= 0 && message_index < message__LIMIT);

  qp = state->messages.queue_pointer; /* insertion point pointer */
  if (*qp == message_QUEUE_END)
    return; /* Queue full. */

  /* Is this message pending? */
  if (qp[-2] == message_index && qp[-1] == 0)
    return; /* Yes - skip adding it. */

  /* Add it to the queue. */
  qp[0] = message_index;
  qp[1] = 0;
  state->messages.queue_pointer = qp + 2;
}

/* ----------------------------------------------------------------------- */

/**
 * $7D48: Incrementally display queued game messages.
 *
 * \param[in] state Pointer to game state.
 */
void message_display(tgestate_t *state)
{
  uint8_t     index;   /* was A */
  const char *pmsgchr; /* was HL */
  uint8_t    *pscr;    /* was DE */

  assert(state != NULL);

  /* Proceed only if message_display_counter is zero. */
  if (state->messages.display_delay > 0)
  {
    state->messages.display_delay--;
    return;
  }

  index = state->messages.display_index;
  if (index == message_NEXT)
  {
    next_message(state);
  }
  else if (index > message_NEXT)
  {
    wipe_message(state);
  }
  else
  {
    pmsgchr = state->messages.current_character;
    pscr    = &state->speccy->screen[screen_text_start_address + index];
    (void) plot_glyph(pmsgchr, pscr);

    state->messages.display_index = index + 1; // Conv: Original used (pscr & 31). CHECK

    if (*++pmsgchr == '\0') /* end of string (0xFF in original game) */
    {
      /* Leave the message for 31 turns, then wipe it. */
      state->messages.display_delay = 31;
      state->messages.display_index |= message_NEXT;
    }
    else
    {
      state->messages.current_character = pmsgchr;
    }
  }
}

/* ----------------------------------------------------------------------- */

/**
 * $7D87: Incrementally wipe away any on-screen game message.
 *
 * Called while messages.display_index > 128.
 *
 * \param[in] state Pointer to game state.
 */
void wipe_message(tgestate_t *state)
{
  int      index; /* was A */
  uint8_t *scr;   /* was DE */

  assert(state != NULL);

  index = state->messages.display_index;

  state->messages.display_index = --index;

  /* Conv: Must remove message_NEXT from index to keep screen address sane. */
  index -= message_NEXT;
  assert(index < 128);

  scr = &state->speccy->screen[screen_text_start_address + index];

  /* Plot a single space character. */
  (void) plot_single_glyph(' ', scr);
}

/* ----------------------------------------------------------------------- */

/**
 * $7D99: Change to displaying the next queued game message.
 *
 * Called when messages.display_index == 128.
 *
 * \param[in] state Pointer to game state.
 */
void next_message(tgestate_t *state)
{
  /**
   * $7DCD: Game messages.
   *
   * Conv: These are 0xFF terminated in the original game.
   */
  static const char *messages_table[message__LIMIT] =
  {
    "MISSED ROLL CALL",
    "TIME TO WAKE UP",
    "BREAKFAST TIME",
    "EXERCISE TIME",
    "TIME FOR BED",
    "THE DOOR IS LOCKED",
    "IT IS OPEN",
    "INCORRECT KEY",
    "ROLL CALL",
    "RED CROSS PARCEL",
    "PICKING THE LOCK",
    "CUTTING THE WIRE",
    "YOU OPEN THE BOX",
    "YOU ARE IN SOLITARY",
    "WAIT FOR RELEASE",
    "MORALE IS ZERO",
    "ITEM DISCOVERED",

    "HE TAKES THE BRIBE", /* $F026 */
    "AND ACTS AS DECOY",  /* $F039 */
    "ANOTHER DAY DAWNS"   /* $F04B */
  };

  uint8_t    *qp;      /* was DE */
  const char *message; /* was HL */

  assert(state != NULL);

  qp = &state->messages.queue[2];
  if (state->messages.queue_pointer == qp)
    return; /* Queue pointer is at the start - nothing to display. */

  assert(*qp < message__LIMIT);

  message = messages_table[*qp];

  state->messages.current_character = message;

  /* Discard the first element. */
  memmove(&state->messages.queue[0], &state->messages.queue[2], 16);
  state->messages.queue_pointer -= 2;
  state->messages.display_index = 0;
}


/* ----------------------------------------------------------------------- */

// vim: ts=8 sts=2 sw=2 et
