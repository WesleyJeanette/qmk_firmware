#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "mousekey.h"

// BASE Layers
#define COLEDH 0 // Colemak
#define QWRT 1 // QWRTY

#define EXTEND 3

#define SYMB 4 // symbols
#define MEDI 5 // media keys
#define KEYW 6 // keyword macros

// my macros

#define UM_0x     M(1)  // 0x
#define UM_CEQ    M(2)  // :=
#define UM_STR    M(3)  // struct
#define UM_RET    M(4)  // return
#define UM_GITLOG M(5)  // git lola
#define UM_BREAK  M(7)  // break
#define UM_NEQ    M(8)  // !=

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD,
};

typedef struct {
  bool is_press_action;
  int state;
} tap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5, //send two single taps
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7
};

// tapdance
enum {
 TD_C_SC = 0,
 /* TD_BSP_DEL_CTRL, */
};

int cur_dance (qk_tap_dance_state_t *state);

//for the x tap dance. Put it here so it can be used in any keymap
void x_finished (qk_tap_dance_state_t *state, void *user_data);
void x_reset (qk_tap_dance_state_t *state, void *user_data);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Keymap Colemak layer
 *
 * ,----------------------------------------------------.           ,--------------------------------------------------.
 * |  =     |    1   |   2  |   3  |   4  |   5  | SYMB |           | SYMB |   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+--------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |    Q   |   W  |   F  |   P  |   B  |   :  |           |      |   J  |   L  |   U  |   Y  |;/MEDI|   \    |
 * |--------+--------+------+------+------+------|      |           |EXTEND|------+------+------+------+------+--------|
 * | `/LGUI |    A   |   R  |   S  |   T  |   G  |------|           |------|   M  |   N  |   E  |   I  |   O  | "/LGUI |
 * |--------+--------+------+------+------+------|  Del |           | OSL  |------+------+------+------+------+--------|
 * | LSft/( | Z/Ctrl |   X  |   C  |   D  |   V  |      |           | SYMB |   K  |   H  |   ,  |   .  |   /  | RSft/) |
 * `--------+--------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |SYMB/`|      |     |      |      |                                       |      |      |      |      | SYMB |
 *   `---------------------------------'                                       `----------------------------------'
 *                                        ,---------------.       ,---------------.
 *                                        | QWRT | EXTEND |       |   esc  |lead  |
 *                                 ,------|------|--------|       |--------+------+------.
 *                                 | Bsp  | Esc  |  Enter |       |  PgUp  | Enter|Space |
 *                                 |  /   |  /   |--------|       |--------|   /  |  /   |
 *                                 | Ctrl | Alt  |  Lead  |       |  Lead  |  Alt | Ctrl |
 *                                 `----------------------'       `----------------------'
 */
[COLEDH] = LAYOUT_ergodox(
    KC_EQUAL,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   TG(SYMB),
    KC_TAB, KC_Q,   KC_W,   KC_F,   KC_P,   KC_B,   TD(TD_C_SC),
    GUI_T(KC_GRAVE),  KC_A,   KC_R,   KC_S,   KC_T,   KC_G,
    KC_LSPO,    CTL_T(KC_Z),    KC_X,   KC_C,   KC_D,   KC_V,   KC_DELETE,
    LT(SYMB, KC_GRAVE), KC_NO,   KC_NO,    KC_NO,    KC_NO,
    DF(QWRT), TG(EXTEND),
    KC_ENTER,
    CTL_T(KC_BSPC),   ALT_T(KC_ESCAPE), KC_LEAD,

    TG(SYMB),  KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINUS,
    TG(EXTEND),    KC_J,   KC_L,   KC_U,   KC_Y,  LT(MEDI, KC_SCOLON), KC_BSLASH,
        KC_M,   KC_N,   KC_E,   KC_I,  KC_O,    GUI_T(KC_QUOTE),
    OSL(SYMB),  KC_K,   KC_H,   KC_COMMA,   KC_DOT, CTL_T(KC_SLASH),    KC_RSPC,
            KC_NO,  KC_NO,    KC_NO,    KC_NO,   TG(SYMB),
    KC_ESCAPE, KC_LEAD,
    KC_PGUP,
    KC_LEAD,  ALT_T(KC_ENTER),   CTL_T(KC_SPACE)
),
/* Keymap QWRT
 *
 * ,----------------------------------------------------.           ,--------------------------------------------------.
 * |  =     |    1   |   2  |   3  |   4  |   5  | SYMB |           | SYMB |   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+--------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |    Q   |   W  |   E  |   R  |   T  |   :  |           |      |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+--------+------+------+------+------|      |           |EXTEND|------+------+------+------+------+--------|
 * | `/LGUI |    A   |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |;/MEDI| "/LGUI |
 * |--------+--------+------+------+------+------|  Del |           | OSL  |------+------+------+------+------+--------|
 * | LSft/( | Z/Ctrl |   X  |   C  |   V  |   B  |      |           | SYMB |   N  |   M  |   ,  |   .  |   /  | RSft/) |
 * `--------+--------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |SYMB/`|      |     |      |      |                                       |      |      |      |      | SYMB |
 *   `---------------------------------'                                       `----------------------------------'
 *                                        ,---------------.       ,---------------.
 *                                        | COLE | EXTEND |       |   esc  |lead  |
 *                                 ,------|------|--------|       |--------+------+------.
 *                                 | Bsp  | Esc  |  Enter |       |  PgUp  | Enter|Space |
 *                                 |  /   |  /   |--------|       |--------|   /  |  /   |
 *                                 | Ctrl | Alt  |  Lead  |       |  Lead  |  Alt | Ctrl |
 *                                 `----------------------'       `----------------------'
 */
[QWRT] = LAYOUT_ergodox(
    KC_EQUAL,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   TG(SYMB),
    KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   TD(TD_C_SC),
    GUI_T(KC_GRAVE),  KC_A,   KC_S,   KC_D,   KC_F,   KC_G,
    KC_LSPO,    CTL_T(KC_Z),    KC_X,   KC_C,   KC_V,   KC_B,   KC_DELETE,
    LT(SYMB, KC_GRAVE), KC_NO,   KC_NO,    KC_NO,    KC_NO,
    DF(COLEDH), TG(EXTEND),
    KC_ENTER,
    CTL_T(KC_BSPC),   ALT_T(KC_ESCAPE), KC_LEAD,

    TG(SYMB),  KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINUS,
    TG(EXTEND),    KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_BSLASH,
        KC_H,   KC_J,   KC_K,   KC_L,   LT(MEDI, KC_SCOLON),   GUI_T(KC_QUOTE),
    OSL(SYMB),  KC_N,   KC_M,   KC_COMMA,   KC_DOT, CTL_T(KC_SLASH),    KC_RSPC,
            KC_NO,  KC_NO,    KC_NO,    KC_NO,    TG(SYMB),
    KC_ESCAPE, KC_LEAD,
    KC_PGUP,
    KC_LEAD,  ALT_T(KC_ENTER),   CTL_T(KC_SPACE)
),

/* Keymap extend Mode
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   ##   |  ##  |  ##  |  ##  |  ##  |  ##  |  ##  |           |  ##  |  ##  |  ##  |  ##  |  ##  |  ##  |   ##   |
 * |--------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |   ##   |  ##  |  ##  |  ##  |  ##  |  ##  |  ##  |           |  ##  | DOWN | RIGHT| END  |PGDOWN|  ##  |   ##   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |   ##   |  ##  |  ##  |  ##  |  ##  |  ##  |------|           |------|  C(UP)  | C(LEFT)  |  C(RIGHT)  |  ##  |  ##  |   ##   |
 * |--------+------+------+------+------+------|  ##  |           |  ##  |------+------+------+------+------+--------|
 * |   ##   | UNDO | CUT  | COPY |  ##  | PASTE|      |           |      |  UP  | LEFT | HOME | PGUP |  ##  |   ##   |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |  ##  |  ##  |  ##  |  ##  |  ##  |                                       |  ##  |  ##  |  ##  |  ##  |  ##  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |  ##  |  ##  |       |  ##  |  ##  |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |  ##  |       |  ##  |      |      |
 *                                 |  ##  |  ##  |------|       |------|  ##  |  ##  |
 *                                 |      |      |  ##  |       |  ##  |      |      |
 *                                 `--------------------'       `--------------------'
 */
[EXTEND] = LAYOUT_ergodox(
	// left hand
    // left hand
    KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,
    KC_TRNS, KC_NO,     KC_NO,  KC_MS_U, KC_NO,   KC_NO, KC_WH_U,
    KC_TRNS, KC_NO,     KC_MS_L, KC_MS_D, KC_MS_R,  KC_NO,
    KC_TRNS, KC_NO,     KC_NO,  KC_NO, KC_NO,   KC_NO,   KC_WH_D,
    KC_TRNS, KC_TRNS,   KC_BTN1, KC_BTN3, KC_BTN2,
                                                    KC_TRNS, KC_TRNS,
                                                             KC_WFWD,
                                          KC_BTN1,  KC_BTN2, KC_WBAK,

	// right hand
	KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
	KC_TRNS,    KC_DOWN,    KC_RIGHT,    KC_END,    KC_PGDN,    KC_TRNS,	KC_TRNS,
		   LCTL(KC_UP),    LCTL(KC_LEFT),    LCTL(KC_RIGHT),   KC_TRNS,     KC_TRNS, KC_TRNS,
	KC_TRNS,    KC_UP,    KC_LEFT,    KC_HOME,    KC_PGUP,    KC_TRNS,	KC_TRNS,
				            KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
	KC_TRNS,    KC_TRNS,
	KC_TRNS,
	KC_TRNS,    KC_TRNS,    KC_TRNS
),

/* Keymap Symbol Layer with F keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   Esc  |  F1  |  F2  |  F3  |  F4  |  F5  |  ##  |           |  ##  |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |   ##   |   !  |   @  |  {   |   }  |   |  |  ##  |           |  ##  |  UP  |   7  |   8  |   9  |   /  |   F12  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |   ##   |   #  |   $  |   (  |   )  |   `  |------|           |------| DOWN |   4  |   5  |   6  |   *  |   ##   |
 * |--------+------+------+------+------+------|  ##  |           |  ##  |------+------+------+------+------+--------|
 * |   ##   |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   -  |  Enter |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |  ##  |  ##  |  ##  |  ##  |  ##  |                                       |  0   |  .   |   =  |  +   |  ##  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |  ##  |  ##  |       |  ##  |  ##  |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |  ##  |       |  ##  |      |      |
 *                                 |  ##  |  ##  |------|       |------|  ##  |  ##  |
 *                                 |      |      |  ##  |       |  ##  |      |      |
 *                                 `--------------------'       `--------------------'
 */
[SYMB] = LAYOUT_ergodox(
	// left hand
	KC_ESCAPE,	    KC_F1,		    KC_F2,		    KC_F3,		    KC_F4,		    KC_F5,		    KC_TRNS,
	KC_TRNS,	    KC_EXLM,	    KC_AT,		    KC_LCBR,	    KC_RCBR,	    KC_PIPE,	    KC_TRNS,
	KC_TRNS,	    KC_HASH,	    KC_DLR,		    KC_LPRN,	    KC_RPRN,	    KC_GRAVE,
	KC_TRNS,	    KC_PERC,	    KC_CIRC,	    KC_LBRC,	    KC_RBRC,	    KC_TILD,	    KC_TRNS,
	KC_TRNS,	    KC_TRNS,	    KC_TRNS,	    KC_TRNS,	    KC_TRNS,
											                                        KC_TRNS,	    KC_TRNS,
													                                                KC_TRNS,
									                                KC_TRNS,	    KC_TRNS,	    KC_TRNS,

	// right hand
	KC_TRNS,	    KC_F6,		    KC_F7,		    KC_F8,		    KC_F9,		    KC_F10,		    KC_F11,
	KC_TRNS,	    KC_UP,	        KC_7,		    KC_8,		    KC_9,		    KC_KP_SLASH,	KC_F12,
			        KC_DOWN,	    KC_4,		    KC_5,		    KC_6,		    KC_ASTR,	    KC_TRNS,
	KC_TRNS,	    KC_AMPR,	    KC_1,		    KC_2,		    KC_3,		    KC_KP_MINUS,	KC_ENTER,
					                KC_KP_0,	    KC_DOT,		    KC_EQUAL,	    KC_KP_PLUS,	    KC_TRNS,
	KC_TRNS,	    KC_TRNS,
	KC_TRNS,
	KC_TRNS,	    KC_TRNS,	    KC_TRNS
),

/* Keymap Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   ##   |  ##  |  ##  |  ##  |  ##  |  ##  |  ##  |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |   ##   |      |      | MsUp |      |      |  MsW |           |      |      |      |  Up  |      |      |        |
 * |--------+------+------+------+------+------|   up |           |      |------+------+------+------+------+--------|
 * |   ##   |      |MsLeft|MsDown|MsRght|      |------|           |------|      | Left | Down | Rght |      |        |
 * |--------+------+------+------+------+------|  MsW |           |      |------+------+------+------+------+--------|
 * |   ##   |      |      |      |      |      |   dn |           |      |      | Play | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |   ## |MsBtnL|MsBtnM|MsBtnR|                                       | VolU | VolD | Mute |      |      |
 *   `---------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |  ##  |  ##  |       |  ##  |  ##  |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |  ##  |       |  ##  |  WWW |  WWW |
 *                                 |MsBtnL|MsBtnR|------|       |------|  FWD |  BCK |
 *                                 |      |      |  ##  |       |  ##  |      |      |
 *                                 `--------------------'       `--------------------'
 */
[MEDI] = LAYOUT_ergodox(
    // left hand
    KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,
    KC_TRNS, KC_NO,     KC_NO,  KC_MS_U, KC_NO,   KC_NO, KC_WH_U,
    KC_TRNS, KC_NO,     KC_MS_L, KC_MS_D, KC_MS_R,  KC_NO,
    KC_TRNS, KC_NO,     KC_NO,  KC_NO, KC_NO,   KC_NO,   KC_WH_D,
    KC_TRNS, KC_TRNS,   KC_BTN1, KC_BTN3, KC_BTN2,
                                                    KC_TRNS, KC_TRNS,
                                                             KC_TRNS,
                                          KC_BTN1,  KC_BTN2, KC_TRNS,

    // right hand
    KC_NO,   KC_NO,     KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_NO,
    KC_NO,   KC_NO,     KC_NO,   KC_UP,   KC_NO,    KC_NO,   KC_NO,
             KC_NO,     KC_LEFT, KC_DOWN, KC_RGHT,  KC_NO,   KC_NO,
    KC_NO,   KC_NO,     KC_MPLY, KC_MPRV, KC_MNXT,  KC_NO,   KC_NO,
                        KC_VOLU, KC_VOLD, KC_MUTE,  KC_NO,   KC_NO,
    KC_TRNS, KC_TRNS,
    KC_TRNS,
    KC_TRNS, KC_WFWD,   KC_WBAK
),


/* Keymap Keywords
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |         |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      |  Cut | Copy |      |PASTE |      |           |      |      |      |      |      |      |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |       |      |      |      |      |                                       |      |      |      |      |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |  ##  |       |  ##  |      |      |
 *                                 `--------------------'       `--------------------'
 */
[KEYW] = LAYOUT_ergodox(
        // left hand
        KC_NO,     KC_NO,     KC_NO,    KC_NO,   KC_NO,    KC_NO,  KC_NO,
        KC_NO,     KC_NO,     KC_NO,    KC_NO,   KC_NO,    KC_NO,  KC_NO,
        KC_NO,     KC_NO,     KC_NO,    KC_NO,   KC_NO,    KC_NO,
        KC_NO,     KC_NO,     KC_CUT,   KC_COPY, KC_NO, KC_PASTE,  KC_NO,
        KC_NO,     KC_NO,     KC_NO,    KC_NO,   KC_NO,
                                                                   KC_NO,    KC_NO,
                                                                             KC_NO,
                                                          KC_NO,   KC_NO,    KC_TRNS,
        // right hand
             KC_NO,     KC_NO, KC_NO,  KC_NO,  KC_NO, KC_NO,    KC_NO,
             KC_NO,     KC_NO, KC_NO,  KC_NO,  KC_NO, KC_NO,    KC_NO,
                        KC_NO, KC_NO,  KC_NO,  KC_NO, KC_NO,    KC_NO,
             KC_NO,     KC_NO, KC_NO,  KC_NO,  KC_NO, KC_NO,    KC_NO,
                               KC_NO,  KC_NO,  KC_NO, KC_NO,    KC_NO,
           KC_NO,  KC_NO,
           KC_NO,
           KC_TRNS,  KC_NO,   KC_NO
    ),

/* Keymap Blank
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   ##   |  ##  |  ##  |  ##  |  ##  |  ##  |  ##  |           |  ##  |  ##  |  ##  |  ##  |  ##  |  ##  |   ##   |
 * |--------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |   ##   |  ##  |  ##  |  ##  |  ##  |  ##  |  ##  |           |  ##  |  ##  |  ##  |  ##  |  ##  |  ##  |   ##   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |   ##   |  ##  |  ##  |  ##  |  ##  |  ##  |------|           |------|  ##  |  ##  |  ##  |  ##  |  ##  |   ##   |
 * |--------+------+------+------+------+------|  ##  |           |  ##  |------+------+------+------+------+--------|
 * |   ##   |  ##  |  ##  |  ##  |  ##  |  ##  |      |           |      |  ##  |  ##  |  ##  |  ##  |  ##  |   ##   |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |  ##  |  ##  |  ##  |  ##  |  ##  |                                       |  ##  |  ##  |  ##  |  ##  |  ##  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |  ##  |  ##  |       |  ##  |  ##  |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |  ##  |       |  ##  |      |      |
 *                                 |  ##  |  ##  |------|       |------|  ##  |  ##  |
 *                                 |      |      |  ##  |       |  ##  |      |      |
 *                                 `--------------------'       `--------------------'
 */
/* [] = KEYMAP( */
/* 	// left hand */
/* 	KC_TRNS,    KC_TRNS,    KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, */
/* 	KC_TRNS,    KC_TRNS,    KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, */
/* 	KC_TRNS,    KC_TRNS,    KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS, */
/* 	KC_TRNS,    KC_TRNS,    KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, */
/* 	KC_TRNS,    KC_TRNS,    KC_TRNS,   KC_TRNS,    KC_TRNS, */
/* 											                                        KC_TRNS,	    KC_TRNS, */
/* 													                                                KC_TRNS, */
/* 									                                KC_TRNS,	    KC_TRNS,	    KC_TRNS, */

/* 	// right hand */
/* 	KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, */
/* 	KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,	KC_TRNS, */
/* 			    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, */
/* 	KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,	KC_TRNS, */
/* 				            KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, */
/* 	KC_TRNS,    KC_TRNS, */
/* 	KC_TRNS, */
/* 	KC_TRNS,    KC_TRNS,    KC_TRNS */
/*), */
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_C_SC] = ACTION_TAP_DANCE_DOUBLE(KC_COLN, KC_SCOLON),
  // Other declarations would go here, separated by commas, if you have them
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)

{
  // MACRODOWN only works in this function
    switch(id) {
    case 1: // 0x
        if (record->event.pressed) {
            return MACRO(T(0), T(X), END);
        }
        break;
    case 2:
        if (record->event.pressed) {
            SEND_STRING(":=");
        }
        break;
    case 3: // struct
        if (record->event.pressed) {
            return MACRO(T(T), T(Y), T(P), T(E), T(SPC),
                    T(S), T(O), T(M), T(E), D(LSFT), T(N), U(LSFT), T(A),
                    T(M), T(E), T(SPC), T(S), T(T), T(R), T(U), T(C), T(T),
                    T(SPC), D(LSFT), T(LBRC), U(LSFT), T(ENT), T(ENT), D(LSFT),
                    T(RBRC), U(LSFT), T(UP), T(TAB), END);
        }
        break;
    case 4:
        if (record->event.pressed) {
            SEND_STRING("return");
        }
        break;
    case 5:
        if (record->event.pressed) {
            SEND_STRING("git log --oneline --graph --decorate=short");
        }
        break;
    case 6:
        if (record->event.pressed) {
            SEND_STRING("continue");
        }
        break;
    case 7:
        if (record->event.pressed) {
            SEND_STRING("break");
        }
        break;
    case 8:
        if (record->event.pressed) {
            SEND_STRING("!=");
        }
        break;
    }
    return MACRO_NONE;
}

LEADER_EXTERNS();

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();

    switch (layer) {
        case 1:
            // colemak
            ergodox_right_led_1_on();
            break;
        case 2:
            // EXTEND
            ergodox_right_led_2_on();
            break;
        case 3:
            ergodox_right_led_3_on();
            break;
        case 4:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            break;
        case 5:
            ergodox_right_led_1_on();
            ergodox_right_led_3_on();
            break;
        case 6:
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;
        case 7:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;
        default:
            break;
    }

    LEADER_DICTIONARY() {
        leading = false;

        SEQ_ONE_KEY(KC_W) {
            SEND_STRING(":w"SS_TAP(X_ENTER));
        }
        SEQ_ONE_KEY(KC_Q) {
            SEND_STRING(":q"SS_TAP(X_ENTER));
        }
        SEQ_TWO_KEYS(KC_G, KC_A) {
            SEND_STRING("git add .");
        }
        SEQ_TWO_KEYS(KC_G, KC_D) {
            SEND_STRING("git diff");
        }
        SEQ_THREE_KEYS(KC_G, KC_D, KC_S) {
            SEND_STRING("git diff --staged");
        }
        SEQ_TWO_KEYS(KC_G, KC_L) {
            SEND_STRING("git log");
        }
        SEQ_THREE_KEYS(KC_G, KC_L, KC_O) {
            SEND_STRING("git log --oneline");
        }
        SEQ_TWO_KEYS(KC_G, KC_F) {
            SEND_STRING("git fetch");
        }
        SEQ_TWO_KEYS(KC_G, KC_O) {
            SEND_STRING("git checkout");
        }
        SEQ_TWO_KEYS(KC_G, KC_P) {
            SEND_STRING("git pull");
        }
        SEQ_TWO_KEYS(KC_G, KC_S) {
            SEND_STRING("git status");
        }
        SEQ_TWO_KEYS(KC_G, KC_C) {
            SEND_STRING("git commit -m ''");
        }
        SEQ_THREE_KEYS(KC_G, KC_C, KC_A) {
            SEND_STRING("git commit --amend");
        }
        SEQ_TWO_KEYS(KC_F, KC_S) {
            SEND_STRING("fmt.Sprintf()");
        }
        SEQ_THREE_KEYS(KC_F, KC_P, KC_F) {
            SEND_STRING("fmt.Printf()");
        }
        SEQ_THREE_KEYS(KC_F, KC_P, KC_L) {
            SEND_STRING("fmt.Println()");
        }
        SEQ_THREE_KEYS(KC_T, KC_E, KC_F) {
            SEND_STRING("t.Errorf()");
        }
        leader_end();
    }
}
const uint16_t PROGMEM fn_actions[] = {
  [1] = ACTION_LAYER_TAP_TOGGLE(1)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
      break;

  }
  return true;
}

// tap dance functions

int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed)  return SINGLE_TAP;
    //key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'.
    else return SINGLE_HOLD;
  }
  else if (state->count == 2) {
    /*
     * DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
     * action when hitting 'pp'. Suggested use case for this return value is when you want to send two
     * keystrokes of the key, and not the 'double tap' action/macro.
    */
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  //Assumes no one is trying to type the same letter three times (at least not quickly).
  //If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
  //an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
  if (state->count == 3) {
    if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return 8; //magic number. At some point this method will expand to work for more presses
}

//instanalize an instance of 'tap' for the 'x' tap dance.
static tap bksp_tap_state = {
  .is_press_action = true,
  .state = 0
};

void bksp_finished (qk_tap_dance_state_t *state, void *user_data) {
  bksp_tap_state.state = cur_dance(state);
  switch (bksp_tap_state.state) {
    case SINGLE_TAP: register_code(KC_BSPC); break;
    case SINGLE_HOLD: register_code(KC_LCTRL); break;
    case DOUBLE_TAP: layer_on(EXTEND); break;
    case DOUBLE_HOLD: register_code(KC_LALT); break;
    case DOUBLE_SINGLE_TAP: register_code(KC_BSPC); unregister_code(KC_BSPC); register_code(KC_BSPC);
    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}

void bksp_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (bksp_tap_state.state) {
    case SINGLE_TAP: unregister_code(KC_BSPC); break;
    case SINGLE_HOLD: unregister_code(KC_LCTRL); break;
    case DOUBLE_TAP: layer_off(EXTEND); break;
    case DOUBLE_HOLD: unregister_code(KC_LALT);
    case DOUBLE_SINGLE_TAP: unregister_code(KC_BSPC);
  }
  bksp_tap_state.state = 0;
}

void tap_layer(keyrecord_t *record, uint8_t layer)
{
  if (record->event.pressed) {
    layer_on(layer);
  }
  else {
    layer_off(layer);
  }
}

/*
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        case 3:
            ergodox_right_led_3_on();
            break;
        case 4:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            break;
        case 5:
            ergodox_right_led_1_on();
            ergodox_right_led_3_on();
            break;
        case 6:
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;
        case 7:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;
        default:
            break;
    }

};
*/
