#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"


#include "keymap_german.h"

#include "keymap_nordic.h"

#define QWRT 0 // default base
#define SYMB 1 // symbols
#define MEDI 2 // media keys
#define NUMB 3 // numbers and hex
#define KEYW 5 // keyword macros
#define EMAC 6 // emacs
#define CLMK 7 // Colmak


// my macros
#define UM_ECET   M(0)  // { }
#define UM_0x     M(1)
#define UM_PUB    M(2)
#define UM_PRO    M(3)
#define UM_PRV    M(4)
#define UM_CLS    M(5)
#define UM_STR    M(6)
#define UM_RET    M(7)
#define UM_INC    M(8)
#define UM_OBJ    M(9)
#define UM_GITLOG M(10)
#define UM_GOODM  M(11)
#define UM_NAMESP M(12)
#define UM_EMTR   M(14) // emacs toggle read-only
#define UM_EMWR   M(15) // emacs write buffer (save)
#define UM_EMUN   M(16) // emacs undo
#define UM_EMRE   M(17) // emacs redo
#define UM_EMPB   M(18) // emacs previous buffer
#define UM_EMNB   M(19) // emacs next buffer
#define UM_GOODN  M(20)
#define UM_ECETS  M(22)  // { };
#define UM_TMPL   M(23)
#define UM_TYPN   M(24)
#define UM_CONT   M(25)
#define UM_BREAK  M(26)
#define UM_CONST  M(27)
#define UM_SMILY  M(28)
#define UM_SADF   M(29)
#define UM_SCARF  M(30)
#define UM_DECAF  M(31)
#define UM_OPER   M(32)
#define UM_NULP   M(33)
#define UM_EXTR   M(34)
#define UM_VIRT   M(35)
#define UM_EMFB   M(36) // emacs font bigger
#define UM_EMFS   M(37) // emacs font smaller
#define UM_VOLAT  M(38)

#define MUL   20 // mouse up left
#define MUR   21 // mouse up right
#define MDL   22 // mouse down left
#define MDR   23 // mouse down right

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
 * | Tab    |    Q   |   W  |   E  |   R  |   T  |   :  |           | Alt  |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+--------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | BkSp   |    A   |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |;/SYMB| "/LGUI |
 * |--------+--------+------+------+------+------| Esc  |           |  ;   |------+------+------+------+------+--------|
 * | LSft/( | Z/Ctrl |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  | RSft/) |
 * `--------+--------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |L1/`| " |   [  | Left |Right |                                       |  Up  | Down |   ]  | Caps | M1  |
 *   `-----------------------------'                                       `----------------------------------'
 *                                        ,---------------.       ,---------------.
 *                                        |  L5  |  lead  |       |  lead  |  Ins |
 *                                 ,------|------|--------|       |--------+------+------.
 *                                 | Space| Del  |  Home  |       |  PgUp  | Enter|Space |
 *                                 |  /   |  /   |--------|       |--------|   /  |  /   |
 *                                 | Ctrl | Alt  |End/KEYW|       |PDn/KEYW|  Alt | Ctrl |
 *                                 `----------------------'       `----------------------'
 */
[QWRT] = KEYMAP(
    KC_EQUAL,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   TG(3),
    KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_COLN,
    KC_BSPACE,  KC_A,   KC_S,   KC_D,   KC_F,   KC_G,
    KC_LSPO,    CTL_T(KC_Z),    KC_X,   KC_C,   KC_V,   KC_B,   KC_ESCAPE,
    LT(1,KC_GRAVE), KC_QUOTE,   KC_LBRACKET,    KC_LEFT,    KC_RIGHT,
    TG(KEYW),  KC_LEAD,
    KC_HOME,
    CTRL_T(KC_SPACE),   ALT_T(KC_DELETE),  LT(5,KC_END),

    TG(1),  KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINUS,
    KC_LALT,    KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_BSLASH,
        KC_H,   KC_J,   KC_K,   KC_L,   LT(MEDI, KC_SCOLON),    GUI_T(KC_QUOTE),
    KC_SCOLON,  KC_N,   KC_M,   KC_COMMA,   KC_DOT, CTL_T(KC_SLASH),    KC_RSPC,
            KC_UP,  KC_DOWN,    KC_RBRACKET,    KC_CAPSLOCK,    MO(SYMB),
    KC_LEAD,    CTL_T(KC_ESCAPE),
    KC_PGUP,
    LT(KEYW,KC_PGDOWN),  ALT_T(KC_ENTER),   CTRL_T(KC_SPACE)
),

/* Keymap 0: Base layer
 *
 * ,----------------------------------------------------.           ,--------------------------------------------------.
 * |  =     |    1   |   2  |   3  |   4  |   5  |  L3  |           |  L1  |   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+--------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |    Q   |   W  |   F  |   P  |   B  |   :  |           | Alt  |   J  |   L  |   U  |   Y  |   ;  |   \    |
 * |--------+--------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | BkSp   |    A   |   R  |   S  |   T  |   G  |------|           |------|   K  |   N  |   E  |   I  |   O  |Enter/L2|
 * |--------+--------+------+------+------+------| Esc  |           |  ;   |------+------+------+------+------+--------|
 * | LSft/( | Z/Ctrl |   X  |   C  |   D  |   V  |      |           |      |   M  |   H  |   ,  |   .  |   /  | RSft/) |
 * `--------+--------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |L1/`| " |   [  | Left |Right |                                       |  Up  | Down |   ]  | Caps | M1  |
 *   `-----------------------------'                                       `----------------------------------'
 *                                        ,---------------.       ,---------------.
 *                                        |  L5  |  lead  |       |  lead  |  Ins |
 *                                 ,------|------|--------|       |--------+------+------.
 *                                 | Space| Del  |  Home  |       |  PgUp  | Enter|Space |
 *                                 |  /   |  /   |--------|       |--------|   /  |  /   |
 *                                 | Ctrl | Alt  |End/KEYW|       |PDn/KEYW|  Alt | Ctrl |
 *                                 `----------------------'       `----------------------'
 */
[CLMK] = KEYMAP( // layer 0 : default
	// left hand
	    KC_EQUAL,	    KC_1,		    KC_2,		    KC_3,		KC_4,		    KC_5,		            TG(3),
    	KC_TAB,         KC_Q,	    	KC_W,	    	KC_F,		KC_P,		    KC_B,		            KC_COLN,
	    KC_BSPACE,	    KC_A,		    KC_R,		    KC_S,		KC_T,		    KC_G,
	    KC_LSPO,	    CTL_T(KC_Z),	KC_X,	    	KC_C,		KC_D,		    KC_V,		            KC_ESCAPE,
    	LT(1,KC_GRAVE),	KC_QUOTE,	    KC_LBRACKET,	KC_LEFT,	KC_RIGHT,
				    						                                        TG(5),                  KC_LEAD,
                                                                                                            KC_HOME,
                                                                    CTRL_T(KC_SPACE),   ALT_T(KC_DELETE),   LT(KEYW,KC_END),

	// right hand
    	TG(SYMB),		    KC_6,	    	KC_7,	    	KC_8,		KC_9,	    	KC_0,		            KC_MINUS,
	    KC_LALT,    	KC_J,		    KC_L,	    	KC_U,		KC_Y,	    	KC_SCOLON,	            KC_BSLASH,
    			        KC_K,   		KC_N,	    	KC_E,		KC_I,	    	LT(MEDI,KC_O), 	        GUI_T(KC_QUOTE),
        KC_SCOLON,	    KC_M,	    	KC_H,	    	KC_COMMA,   KC_DOT,	    	CTL_T(KC_SLASH),        KC_RSPC,
	    			                	KC_UP,		    KC_DOWN,   	KC_RBRACKET,	KC_CAPSLOCK,    	    MO(SYMB),
    	KC_LEAD,        CTL_T(KC_ESCAPE),
        KC_PGUP,
        LT(KEYW,KC_PGDOWN),  ALT_T(KC_ENTER),   CTRL_T(KC_SPACE)
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
			        KC_DOWN,	    KC_4,		    KC_5,		    KC_6,		    KC_KP_ASTR,	    KC_TRNS,
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
    KC_TRNS,    KC_KP_ASTR,     KC_KP_7,        KC_KP_8,        KC_KP_9,        KC_KP_ASTR,      UM_0x,
    KC_TRNS,    KC_KP_SLASH,    KC_KP_4,        KC_KP_5,        KC_KP_6,        KC_KP_SLASH,
    KC_TRNS,    KC_KP_MINUS,    KC_KP_1,        KC_KP_2,        KC_KP_3,        KC_KP_MINUS,     TO(1),
    KC_EQUAL,   KC_KP_PLUS,     KC_KP_0,        KC_COMMA,       KC_DOT,
                                                                                KC_TRNS,         KC_TRNS,
                                                                                                 KC_TRNS,
                                                                KC_TRNS,        KC_TRNS,           KC_TRNS,

    KC_TRNS,    KC_TRNS,        KC_TRNS,        KC_KP_SLASH,    KC_KP_ASTR, KC_TRNS, KC_TRNS,
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
 * |         |      |      | scarf| sadf | smily|      |           |      | decaf|      |      |      |      |        |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         | const| volat| oper |  ret | tmpl |      |           |      | typen| cont |  prv |  pro | pub  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      |  str |  obj |      | gitl |------|           |------|      |      |      | nulp |      |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      | extr |  cls | virt | break|      |           |      |namesp| goodm| goodn|      |      |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |       |      |  inc |      |      |                                       |      |      |      |      |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       | ecet | ecets|
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |  ##  |       |  ##  |      |      |
 *                                 `--------------------'       `--------------------'
 */
[KEYW] = LAYOUT_ergodox(
        // left hand
        KC_NO,     KC_NO,     KC_NO,     UM_SCARF,  UM_SADF,   UM_SMILY,   KC_NO,
        KC_NO,     UM_CONST,  UM_VOLAT,  UM_OPER,   UM_RET,    UM_TMPL,    KC_NO,
        KC_NO,     KC_NO,     UM_STR,    UM_OBJ,    KC_NO,     UM_GITLOG,
        KC_NO,     KC_NO,     UM_EXTR,   UM_CLS,    UM_VIRT,   UM_BREAK,   KC_NO,
        KC_NO,     KC_NO,     UM_INC,    KC_NO,     KC_NO,
                                                                   KC_NO,    KC_NO,
                                                                             KC_NO,
                                                          KC_NO,   KC_NO,    KC_TRNS,
        // right hand
             KC_NO,     UM_DECAF,  KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
             KC_NO,     UM_TYPN,   UM_CONT,   UM_PRV,    UM_PRO,    UM_PUB,    KC_NO,
                        KC_NO,     KC_NO,     KC_NO,     UM_NULP,   KC_NO,     KC_NO,
             KC_NO,     UM_NAMESP, UM_GOODM,  UM_GOODN,  KC_NO,     KC_NO,     KC_NO,
                                   KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
           UM_ECET,  UM_ECETS,
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
    case 1:
        if (record->event.pressed) {
            return MACRO(T(0), T(X), END);
        }
        break;
    case 2:
        if (record->event.pressed) {
            SEND_STRING("public");
        }
        break;
    case 3:
        if (record->event.pressed) {
            SEND_STRING("protected");
        }
        break;
    case 4:
        if (record->event.pressed) {
            SEND_STRING("private");
        }
        break;
    case 5: // class
        if (record->event.pressed) {
            return MACRO(T(C), T(L), T(A), T(S), T(S), T(ENT),
                         D(LSFT), T(LBRC), U(LSFT), T(ENT),
                         T(P), T(U), T(B), T(L), T(I), T(C),
                         D(LSFT), T(SCLN), U(LSFT), T(ENT), T(ENT),
                         T(P), T(R), T(I), T(V), T(A), T(T), T(E),
                         D(LSFT), T(SCLN), U(LSFT), T(ENT),
                         D(LSFT), T(RBRC), U(LSFT), T(SCLN), T(ENT),
                         T(UP), T(UP), T(UP), T(UP), T(UP), T(UP), T(UP),
                         T(END), T(SPC), END);
        }
        break;
    case 6: // struct
        if (record->event.pressed) {
            return MACRO(T(S), T(T), T(R), T(U), T(C), T(T), T(ENT),
                         D(LSFT), T(LBRC), U(LSFT), T(ENT),
                         D(LSFT), T(RBRC), U(LSFT), T(SCLN), T(ENT),
                         T(UP), T(UP), T(UP), T(UP),
                         T(END), T(SPC), END);
        }
        break;
    case 7:
        if (record->event.pressed) {
            SEND_STRING("return");
        }
        break;
    case 8: // #include
        if (record->event.pressed) {
            return MACRO(T(NONUS_HASH), T(I), T(N), T(C), T(L), T(U), T(D), T(E), END);
        }
        break;
    case 9:
        if (record->event.pressed) {
            SEND_STRING("objdump -CT -x -d");
        }
        break;
    case 10:
        if (record->event.pressed) {
            SEND_STRING("git log --oneline --graph --decorate=short");
        }
        break;
    case 11:
        if (record->event.pressed) {
            SEND_STRING("good morning");
        }
        break;
    case 12:
        if (record->event.pressed) {
            SEND_STRING("namespace");
        }
        break;
    case 14: // emacs toggle read-only
        if (record->event.pressed) {
            return MACRO(D(LCTL), T(X), T(Q), U(LCTL), END);
        }
        break;
    case 15: // emacs write buffer
        if (record->event.pressed) {
            return MACRO(D(LCTL), T(X), T(S), U(LCTL), END);
        }
        break;
    case 16: // emacs undo
        if (record->event.pressed) {
            return MACRO(D(LCTL), D(LSFT), T(MINS), U(LSFT), U(LCTL), END);
        }
        break;
    case 17: // emacs redo
        if (record->event.pressed) {
            return MACRO(D(LALT), D(LSFT), T(MINS), U(LSFT), U(LALT), END);
        }
        break;
    case 18: // emacs previous buffer
        if (record->event.pressed) {
            return MACRO(D(LCTL), T(X), U(LCTL), T(LEFT), END);
        }
        break;
    case 19: // emacs next buffer
        if (record->event.pressed) {
            return MACRO(D(LCTL), T(X), U(LCTL), T(RGHT), END);
        }
        break;
    case 20:
        if (record->event.pressed) {
            SEND_STRING("good night");
        }
        break;
    case 22: // { };
        if (record->event.pressed) {
            return MACRO(T(ENT), D(LSFT), T(LBRC), U(LSFT), T(ENT),
                         D(LSFT), T(RBRC), U(LSFT), T(SCLN), T(UP),
                         T(TAB), END);
        }
        break;
    case 23:
        if (record->event.pressed) {
            SEND_STRING("template");
        }
        break;
    case 24:
        if (record->event.pressed) {
            SEND_STRING("typename");
        }
        break;
    case 25:
        if (record->event.pressed) {
            SEND_STRING("continue");
            return MACRO(T(SCLN), END);
        }
        break;
    case 26:
        if (record->event.pressed) {
            SEND_STRING("break");
            return MACRO(T(SCLN), END);
        }
        break;
    case 27:
        if (record->event.pressed) {
            SEND_STRING("const");
        }
        break;
    case 28:
        if (record->event.pressed) {
            SEND_STRING(":-)");
        }
        break;
    case 29:
        if (record->event.pressed) {
            SEND_STRING(":-(");
        }
        break;
    case 30: // dazed
        if (record->event.pressed) {
            send_keystrokes(NK_DOWN, KC_LSFT, KC_8, KC_MINS, KC_8, NK_UP, KC_LSFT, KC_NO);
        }
        break;
    case 31: // decaf
        if (record->event.pressed) {
            send_keystrokes(NK_DOWN, KC_LSFT, KC_C, KC_9, KC_MINS, KC_0, NK_UP, KC_LSFT, KC_NO);
        }
        break;
    case 32:
        if (record->event.pressed) {
            SEND_STRING("operator");
        }
        break;
    case 33:
        if (record->event.pressed) {
            SEND_STRING("nullptr");
        }
        break;
    case 34:
        if (record->event.pressed) {
            SEND_STRING("extern");
        }
        break;
    case 35:
        if (record->event.pressed) {
            SEND_STRING("virtual");
        }
        break;
    case 36: // emacs font smaller
        if (record->event.pressed) {
            return MACRO(D(LCTL), T(X), T(EQL), U(LCTL), END);
        }
        break;
    case 37:  // emacs font bigger
        if (record->event.pressed) {
            return MACRO(D(LCTL), T(X), T(MINS), U(LCTL), END);
        }
        break;
    case 38:
        if (record->event.pressed) {
            SEND_STRING("volatile");
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
            send_keystrokes(KC_LEFT, KC_NO);
        }
        SEQ_THREE_KEYS(KC_G, KC_C, KC_A) {
            SEND_STRING("git commit --amend");
        }

        SEQ_TWO_KEYS(KC_C, KC_C) {
            SEND_STRING("const_cast<>");
            send_keystrokes(KC_LEFT, KC_NO);
        }
        SEQ_TWO_KEYS(KC_C, KC_D) {
            SEND_STRING("dynamic_cast<>");
            send_keystrokes(KC_LEFT, KC_NO);
        }
        SEQ_TWO_KEYS(KC_C, KC_R) {
            SEND_STRING("reinterpret_cast<>");
            send_keystrokes(KC_LEFT, KC_NO);
        }
        SEQ_TWO_KEYS(KC_C, KC_S) {
            SEND_STRING("static_cast<>");
            send_keystrokes(KC_LEFT, KC_NO);
        }

        SEQ_ONE_KEY(KC_SLSH) {
            send_keystrokes(KC_SLSH, NK_DOWN, KC_LSFT, KC_8, KC_8, NK_UP, KC_LSFT, KC_ENT,
                            NK_DOWN, KC_LSFT, KC_8, NK_UP, KC_LSFT, KC_ENT,
                            NK_DOWN, KC_LSFT, KC_8, NK_UP, KC_LSFT, KC_SLSH, KC_UP, KC_END, KC_SPC,
                            KC_NO);
        }
    }
}
const uint16_t PROGMEM fn_actions[] = {
  [1] = ACTION_LAYER_TAP_TOGGLE(1)
};

// leaving this in place for compatibilty with old keymaps cloned and re-compiled.
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
        case 0:
        if (record->event.pressed) {
          SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        }
        break;
      }
    return MACRO_NONE;
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

