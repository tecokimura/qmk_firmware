#include QMK_KEYBOARD_H

#define _______ KC_TRNS

#define LY_HHKB 0
#define LY_SPC  1
#define LY_TAB  2
#define LY_LFN  3
#define LY_RFN  4

#define LT_SPC  LT(LY_SPC, KC_SPC)
#define LT_TAB  LT(LY_TAB, KC_TAB) 
#define LT_LFN  LT(LY_LFN, KC_TAB) 
#define LT_RFN  LT(LY_LFN, KC_TAB) 


/* Layer 0: HHKB JP
 * ,-----------------------------------------------------------.
 * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9| 10|  -|  =|Yen|Bsp|
 * |-----------------------------------------------------------|
 * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|     |
 * |------------------------------------------------------` Ent|
 * |Ctrl  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|  `|    |
 * |-----------------------------------------------------------|
 * |Shft   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|  \| Up|Sft|
 * |-----------------------------------------------------------|
 * |   ||Ctl|Alt|Cmd|   |   Spc   |Bsp|   |   |   ||Lft|Dwn|Rgh|
 * `-----------------------------------------------------------'
 */

/* Layer 4: HHKB mode (HHKB Fn)
 * ,-----------------------------------------------------------.
 * |Pwr| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Ins|Del|
 * |-----------------------------------------------------------|
 * |Caps |   |   |   |   |   |   |   |Psc|Slk|Pus|Up |   |     |
 * |------------------------------------------------------`    |
 * |      |VoD|VoU|Mut|   |   |  *|  /|Hom|PgU|Lef|Rig|   |    |
 * |-----------------------------------------------------------|
 * |       |   |   |   |   |   |  +|  -|End|PgD|Dow|   |   |   |
 * |-----------------------------------------------------------|
 * |   ||   |   |   |   |         |   |   |   |   ||   |   |   |
 * `-----------------------------------------------------------'
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LY_HHKB] = LAYOUT_JP(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   KC_6,    KC_7,    KC_8,    KC_9,   KC_0,    KC_MINS, KC_EQL,  KC_JYEN, KC_BSPC,
        LT_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,    KC_LBRC, KC_RBRC,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,   KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN, KC_QUOT, KC_BSLS,     KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_RO,   KC_UP,   KC_RSFT,
 LT_LFN, KC_ZKHK, KC_LGUI, KC_LALT, KC_BSPC,        LT_SPC,           KC_ENT,  KC_KANA, KC_RALT, LT_RFN, KC_LEFT, KC_DOWN, KC_RGHT),

    [LY_SPC] = LAYOUT_JP(
        KC_ESC,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MINS, KC_EQL,  KC_JYEN, KC_BSPC,
        _______, _______, _______, KC_END,  _______, _______, KC_HOME, KC_PGDN, KC_PGUP, _______, KC_PSCR, KC_LBRC, KC_RBRC,
        KC_LCTL, KC_HOME, KC_SPC,  KC_DEL,  _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_END,  KC_QUOT, KC_BSLS, KC_ENT,
        KC_LSFT, _______, _______, _______, _______, KC_BSPC, KC_ENT,  _______, KC_COMM, KC_DOT,  KC_SLSH, KC_RO,   KC_UP,   KC_RSFT,
        _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, KC_LEFT, KC_DOWN, KC_RGHT),

    [LY_TAB] = LAYOUT_JP(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL, KC_JYEN, KC_BSPC,
        _______, KC_BTN1, KC_BTN2, KC_E,    KC_R,    KC_TAB,  KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, KC_P,    KC_LBRC, KC_RBRC,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_SCLN, KC_QUOT, KC_BSLS, KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_BTN1, KC_BTN2, KC_BTN3, KC_BTN4, KC_BTN5, KC_RO, KC_UP, KC_RSFT,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT),

    [LY_LFN] = LAYOUT_JP(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        KC_TAB,  _______, _______, _______, _______, _______, _______, KC_7,    KC_8,    KC_9,    KC_PLUS, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, KC_4,    KC_5,    KC_6,    KC_MINS, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, KC_0,    KC_1,    KC_2,    KC_3,    _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),
        
    [LY_RFN] = LAYOUT_JP(
        KC_PWR,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS, KC_DEL,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_PSCR, KC_SLCK, KC_PAUS, KC_UP,   _______,
        _______, KC_VOLD, KC_VOLU, KC_MUTE, KC_PWR,  _______, KC_PAST, KC_PSLS, KC_HOME, KC_PGUP, KC_LEFT, KC_RGHT, _______, KC_PENT,
        _______, _______, _______, _______, _______, _______, KC_PPLS, KC_PMNS, KC_END,  KC_PGDN, KC_DOWN, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______)};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t macro_id, uint8_t opt)
{
    return MACRO_NONE;
}

const uint16_t PROGMEM fn_actions[] = {

};
