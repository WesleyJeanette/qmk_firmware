#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "mousekey.h"

#define QWRT 0 // default base
#define SYMB 1 // symbols
#define MEDI 2 // media keys
#define NUMB 3 // numbers and hex
#define KEYW 4 // keyword macros
#define CLMK 5 // Colmak


// my macros
#define MACRO_TODO 9

#define UM_ECET   M(0)  // { }
#define UM_0x     M(1)  // 0x
#define UM_CEQ    M(2)  // :=
#define UM_STR    M(3)  // struct
#define UM_RET    M(4)  // return
#define UM_GITLOG M(5)  // git lola
#define UM_CONT   M(6)  // continue
#define UM_BREAK  M(7)  // break
#define UM_NEQ    M(8)  // !=

#define MUL   (40) // mouse up left
#define MUR   (41) // mouse up right
#define MDL   (42) // mouse down left
#define MDR   (43) // mouse down right

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Base layer
 *
 * ,----------------------------------------------------.           ,--------------------------------------------------.
 * |  =     |    1   |   2  |   3  |   4  |   5  |  L3  |           |  L1  |   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+--------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |    Q   |   W  |   E  |   R  |   T  |   :  |           |  [   |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+--------+------+------+------+------|      |           |  {   |------+------+------+------+------+--------|
 * | Esc    |    A   |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |;/SYMB| "/LGUI |
 * |--------+--------+------+------+------+------| Esc  |           |  ]   |------+------+------+------+------+--------|
 * | LSft/( | Z/Ctrl |   X  |   C  |   V  |   B  |      |           |  }   |   N  |   M  |   ,  |   .  |   /  | RSft/) |
 * `--------+--------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |L1/`| " |   [  | Left |Right |                                       |  Up  | Down |   ]  | Del  | M1  |
 *   `-----------------------------'                                       `----------------------------------'
 *                                        ,---------------.       ,---------------.
 *                                        | NUMB |  lead  |       |  lead  |  Ins |
 *                                 ,------|------|--------|       |--------+------+------.
 *                                 | Space| Bsp  |  Home  |       |  PgUp  | Enter|Space |
 *                                 |  /   |  /   |--------|       |--------|   /  |  /   |
 *                                 | Ctrl | Alt  |End/KEYW|       |PDn/KEYW|  Alt | Ctrl |
 *                                 `----------------------'       `----------------------'
 */
[QWRT] = KEYMAP(
    KC_EQUAL,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   TG(3),
    KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_COLN,
    KC_ESCAPE,  KC_A,   KC_S,   KC_D,   KC_F,   KC_G,
    KC_LSPO,    CTL_T(KC_Z),    KC_X,   KC_C,   KC_V,   KC_B,   KC_ESCAPE,
    LT(1,KC_GRAVE), KC_QUOTE,   KC_LBRACKET,    KC_LEFT,    KC_RIGHT,
    TG(NUMB),  KC_LEAD,
    KC_HOME,
    CTL_T(KC_SPACE),   ALT_T(KC_BSPC),  LT(KEYW,KC_END),

    TG(1),  KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINUS,
    KC_LBRACKET,    KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_BSLASH,
        KC_H,   KC_J,   KC_K,   KC_L,   LT(MEDI, KC_SCOLON),    GUI_T(KC_QUOTE),
    KC_RBRACKET,  KC_N,   KC_M,   KC_COMMA,   KC_DOT, CTL_T(KC_SLASH),    KC_RSPC,
            KC_UP,  KC_DOWN,    KC_RBRACKET,    KC_DELETE,    MO(SYMB),
    KC_LEAD,    CTL_T(KC_ESCAPE),
    KC_PGUP,
    LT(KEYW,KC_PGDOWN),  ALT_T(KC_ENTER),   CTL_T(KC_SPACE)
),

/* Keymap 0: colmak layer
 *
 * ,----------------------------------------------------.           ,--------------------------------------------------.
 * |  =     |    1   |   2  |   3  |   4  |   5  |  L3  |           |  L1  |   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+--------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |    Q   |   W  |   F  |   P  |   B  |   :  |           |  [  |   J  |   L  |   U  |   Y  |   ;  |   \    |
 * |--------+--------+------+------+------+------|      |           |  }  |------+------+------+------+------+--------|
 * | BkSp   |    A   |   R  |   S  |   T  |   G  |------|           |------|   K  |   N  |   E  |   I  |   O  |Enter/L2|
 * |--------+--------+------+------+------+------| Esc  |           |  ]   |------+------+------+------+------+--------|
 * | LSft/( | Z/Ctrl |   X  |   C  |   D  |   V  |      |           |  }   |   M  |   H  |   ,  |   .  |   /  | RSft/) |
 * `--------+--------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |L1/`| " |   [  | Left |Right |                                       |  Up  | Down |   ]  | Del  | M1  |
 *   `-----------------------------'                                       `----------------------------------'
 *                                        ,---------------.       ,---------------.
 *                                        | NUMB |  lead  |       |  lead  |  Ins |
 *                                 ,------|------|--------|       |--------+------+------.
 *                                 | Space| Bsp  |  Home  |       |  PgUp  | Enter|Space |
 *                                 |  /   |  /   |--------|       |--------|   /  |  /   |
 *                                 | Ctrl | Alt  |End/KEYW|       |PDn/KEYW|  Alt | Ctrl |
 *                                 `----------------------'       `----------------------'
 */
[CLMK] = KEYMAP( // layer 5 : colmak
	// left hand
	    KC_EQUAL,	    KC_1,		    KC_2,		    KC_3,		KC_4,		    KC_5,		            TG(3),
    	KC_TAB,         KC_Q,	    	KC_W,	    	KC_F,		KC_P,		    KC_B,		            KC_COLN,
	    KC_BSPACE,	    KC_A,		    KC_R,		    KC_S,		KC_T,		    KC_G,
	    KC_LSPO,	    CTL_T(KC_Z),	KC_X,	    	KC_C,		KC_D,		    KC_V,		            KC_ESCAPE,
    	LT(1,KC_GRAVE),	KC_QUOTE,	    KC_LBRACKET,	KC_LEFT,	KC_RIGHT,
				    						                                        TG(NUMB),                  KC_LEAD,
                                                                                                            KC_HOME,
                                                                    CTL_T(KC_SPACE),   ALT_T(KC_BSPACE),   LT(KEYW,KC_END),

	// right hand
    	TG(SYMB),		    KC_6,	    	KC_7,	    	KC_8,		KC_9,	    	KC_0,		            KC_MINUS,
	    KC_LBRACKET,    	KC_J,		    KC_L,	    	KC_U,		KC_Y,	    	KC_SCOLON,	            KC_BSLASH,
    			        KC_K,   		KC_N,	    	KC_E,		KC_I,	    	LT(MEDI,KC_O), 	        GUI_T(KC_QUOTE),
        KC_RBRACKET,	    KC_M,	    	KC_H,	    	KC_COMMA,   KC_DOT,	    	CTL_T(KC_SLASH),        KC_RSPC,
	    			                	KC_UP,		    KC_DOWN,   	KC_RBRACKET,	KC_CAPSLOCK,    	    MO(SYMB),
    	KC_LEAD,        CTL_T(KC_ESCAPE),
        KC_PGUP,
        LT(KEYW,KC_PGDOWN),  ALT_T(KC_ENTER),   CTL_T(KC_SPACE)
    ),

/* Keymap 1: Symbol Layer with F keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   Esc  |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |  ##  |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |   ##   |   !  |   @  |  {   |   }  |   |  |  L3  |           |  ##  |  UP  |   7  |   8  |   9  |   /  |   F12  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |   ##   |   #  |   $  |   (  |   )  |   `  |------|           |------| DOWN |   4  |   5  |   6  |   *  |   ##   |
 * |--------+------+------+------+------+------|  L0  |           |  ##  |------+------+------+------+------+--------|
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
[SYMB] = KEYMAP( // layer 1 : symbols
	// left hand
	KC_ESCAPE,	    KC_F1,		    KC_F2,		    KC_F3,		    KC_F4,		    KC_F5,		    KC_NO,
	KC_TRNS,	    KC_EXLM,	    KC_AT,		    KC_LCBR,	    KC_RCBR,	    KC_PIPE,	    TO(3),
	KC_TRNS,	    KC_HASH,	    KC_DLR,		    KC_LPRN,	    KC_RPRN,	    KC_GRAVE,
	KC_TRNS,	    KC_PERC,	    KC_CIRC,	    KC_LBRC,	    KC_RBRC,	    KC_TILD,	    TO(0),
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

/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   ##   |  ##  |  ##  |  ##  |  ##  |  ##  |  ##  |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |   ##   |      |MsUpLf| MsUp |MsUpRt|      |  MsW |           |      |      |      | MsUp |      |      |        |
 * |--------+------+------+------+------+------|   up |           |      |------+------+------+------+------+--------|
 * |   ##   |      |MsLeft|MsDown|MsRght|      |------|           |------|      | Left | Down | Rght |      |        |
 * |--------+------+------+------+------+------|  MsW |           |      |------+------+------+------+------+--------|
 * |   ##   |      |MsDnLf|MsDown|MsDnRt|      |   dn |           |      |      | Play | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |   ## |MsBtnL|MsBtnM|MsBtnR|                                       | VolU | VolD | Mute |      |      |
 *   `---------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |  WWW |  WWW |
 *                                 |MsBtnL|MsBtnR|------|       |------|  FWD |  BCK |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[MEDI] = KEYMAP( // layer 2 : media
    // left hand
    KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,
    KC_TRNS, KC_NO,     M(MUL),  KC_MS_U, M(MUR),   KC_TRNS, KC_WH_U,
    KC_TRNS, KC_NO,     KC_MS_L, KC_MS_D, KC_MS_R,  KC_TRNS,
    KC_TRNS, KC_NO,     M(MDL),  KC_MS_D, M(MDR),   KC_NO,   KC_WH_D,
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

/* Keymap 3: Numerics and hex
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |   ##    |  A   |  B   |  C   |  D   |  E   |  F   |           |  ##  |  ##  |  ##  |  /   |   *  |  ##  |   ##   |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |   ##    |  *   |  7   |  8   |  9   |  *   |  0x  |           |  ##  | V UP |   7  |   8  |   9  |   -  |   ##   |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |   ##    |  /   |  4   |  5   |  6   |  /   |------|           |------| V DN |   4  |   5  |   6  |   +  |   ##   |
 * |---------+------+------+------+------+------|  T1  |           |  ##  |------+------+------+------+------+--------|
 * |   ##    |  -   |  1   |  2   |  3   |  -   |      |           |      | MUTE |   1  |   2  |   3  |  RTN |   ##   |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |   =   |  +   |  0   |  ,   |  .   |                                       |   0  |   .  |  ##  |  ##  |  ##  |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |  ##  |  ##  |       |  ##  |  ##  |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |  ##  |       |  ##  |      |      |
 *                                 |  ##  |  ##  |------|       |------|  ##  | ##   |
 *                                 |      |      |  ##  |       |  ##  |      |      |
 *                                 `--------------------'       `--------------------'
 */
[NUMB] = KEYMAP(
    KC_TRNS,    LSFT(KC_A),     LSFT(KC_B),     LSFT(KC_C),     LSFT(KC_D),     LSFT(KC_E),      LSFT(KC_F),
    KC_TRNS,    KC_ASTR,     KC_KP_7,        KC_KP_8,        KC_KP_9,        KC_ASTR,      UM_0x,
    KC_TRNS,    KC_KP_SLASH,    KC_KP_4,        KC_KP_5,        KC_KP_6,        KC_KP_SLASH,
    KC_TRNS,    KC_KP_MINUS,    KC_KP_1,        KC_KP_2,        KC_KP_3,        KC_KP_MINUS,     TO(1),
    KC_EQUAL,   KC_KP_PLUS,     KC_KP_0,        KC_COMMA,       KC_DOT,
                                                                                KC_TRNS,         KC_TRNS,
                                                                                                 KC_TRNS,
                                                                KC_TRNS,        KC_TRNS,           KC_TRNS,

    KC_TRNS,    KC_TRNS,        KC_TRNS,        KC_KP_SLASH,    KC_ASTR, KC_TRNS, KC_TRNS,
    KC_TRNS,    KC_VOLU,        KC_KP_7,        KC_KP_8,        KC_KP_9,        KC_KP_MINUS,    KC_TRNS,
                KC_VOLD,        KC_KP_4,        KC_KP_5,        KC_KP_6,        KC_KP_PLUS,     KC_TRNS,
    KC_TRNS,    KC_MUTE,        KC_KP_1,        KC_KP_2,        KC_KP_3,        KC_ENTER,       KC_TRNS,
                                KC_KP_0,        KC_KP_DOT,      KC_TRNS,        KC_TRNS,        KC_TRNS,
    KC_TRNS,    KC_TRNS,
    KC_TRNS,
    KC_TRNS,    KC_TRNS,        KC_TRNS
),

/* Keymap 4: Keywords
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |         |  !=  |      |      |      |  T5  |      |           |      |      |      |      |      |      |        |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |      |      |      | Retn | TODO |  :=  |           |      |      |      |      |      |      |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      |      |      |      | gitl |------|           |------|      |      |      |      |      |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      |      | const|      | break|      |           |      |      |      |      |      |      |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |       |      |      |      |      |                                       |      |      |      |      |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       | {}   |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |  ##  |       |  ##  |      |      |
 *                                 `--------------------'       `--------------------'
 */
[KEYW] = LAYOUT_ergodox(
        // left hand
        KC_NO,     UM_NEQ,     KC_NO,     KC_NO,  KC_NO,   TO(CLMK),   KC_NO,
        KC_NO,     KC_NO,      KC_NO,     KC_NO,   UM_RET,    M(MACRO_TODO),    UM_CEQ,
        KC_NO,     KC_NO,     UM_STR,    KC_NO,    KC_NO,     UM_GITLOG,
        KC_NO,     KC_NO,     KC_NO,   UM_CONT,    KC_NO,   UM_BREAK,   KC_NO,
        KC_NO,     KC_NO,     KC_NO,    KC_NO,     KC_NO,
                                                                   KC_NO,    KC_NO,
                                                                             KC_NO,
                                                          KC_NO,   KC_NO,    KC_TRNS,
        // right hand
             KC_NO,     KC_NO,  KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
             KC_NO,     KC_NO,   KC_NO,   KC_NO,    KC_NO,    KC_NO,    KC_NO,
                        KC_NO,     KC_NO,     KC_NO,     KC_NO,   KC_NO,     KC_NO,
             KC_NO,     KC_NO, KC_NO,  KC_NO,  KC_NO,     KC_NO,     KC_NO,
                                   KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
           UM_ECET,  KC_NO,
           KC_NO,
           KC_TRNS,  KC_NO,   KC_NO
    ),
};


const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
    switch(id) {
    case 0: // { }
        if (record->event.pressed) {
            return MACRO(T(ENT), D(LSFT), T(LBRC), U(LSFT), T(ENT),
                         D(LSFT), T(RBRC), U(LSFT), T(UP),
                         T(TAB), END);
        }
        break;
    case 1: // 0x
        if (record->event.pressed) {
            return MACRO(T(0), T(X), END);
        }
        break;
    case 2:
        if (record->event.pressed) {
            SEND_STRING(" := ");
        }
        break;
    case 3: // struct
        if (record->event.pressed) {
            return MACRO(T(T), T(Y), T(P), T(E), T(SPC),
                    T(S), T(O), T(M), T(E), D(LSFT), T(N), U(LSFT), T(A),
                    T(M), T(E), T(SPC), T(S), T(T), T(R), T(U), T(C), T(T),
                    T(SPC), D(LSFT), T(LBRC), U(LSFT), T(ENT), D(LSFT),
                    T(RBRC), U(LSFT), T(SCLN), T(ENT), T(UP), T(UP), T(UP),
                    T(UP), T(END), T(SPC), END);
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
    case MACRO_TODO:
        if (record->event.pressed) {
            SEND_STRING("//TODO: ");
        }
         break;
    // mouse diagonals
    case MUL: // mouse up left
        if (record->event.pressed) {
            mousekey_on(KC_MS_UP);
            mousekey_on(KC_MS_LEFT);
            mousekey_send();
        } else {
            mousekey_off(KC_MS_UP);
            mousekey_off(KC_MS_LEFT);
            mousekey_send();
        }
        break;
    case MUR: // mouse up right
        if (record->event.pressed) {
            mousekey_on(KC_MS_UP);
            mousekey_on(KC_MS_RIGHT);
            mousekey_send();
        } else {
            mousekey_off(KC_MS_UP);
            mousekey_off(KC_MS_RIGHT);
            mousekey_send();
        }
        break;
    case MDL: // mouse down left
        if (record->event.pressed) {
            mousekey_on(KC_MS_DOWN);
            mousekey_on(KC_MS_LEFT);
            mousekey_send();
        } else {
            mousekey_off(KC_MS_DOWN);
            mousekey_off(KC_MS_LEFT);
            mousekey_send();
        }
        break;
    case MDR: // mouse down right
        if (record->event.pressed) {
            mousekey_on(KC_MS_DOWN);
            mousekey_on(KC_MS_RIGHT);
            mousekey_send();
        } else {
            mousekey_off(KC_MS_DOWN);
            mousekey_off(KC_MS_RIGHT);
            mousekey_send();
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

    LEADER_DICTIONARY() {
        leading = false;
        leader_end();

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
        SEQ_TWO_KEYS(KC_T, KC_P) {
            SEND_STRING(":tabp ");
        }
        SEQ_TWO_KEYS(KC_T, KC_N) {
            SEND_STRING(":tabn ");
        }
        SEQ_TWO_KEYS(KC_T, KC_F) {
            SEND_STRING(":tabf ");
        }
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

