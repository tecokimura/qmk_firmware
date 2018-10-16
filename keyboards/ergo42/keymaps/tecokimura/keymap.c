#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#include "keymap_jp.h"

#define BASE 0
#define META 1
#define SYMB 2
#define GAME 3

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// written by tecokimura
#define LY_NORMAL 0
#define LY_CURSOR 1
#define LY_MOUSE  2
#define LY_NUMBER 3
#define LY_FUNC   4

#define LT_CRSR  LT(LY_CURSOR, KC_SPC)
#define LT_MOUS  LT(LY_MOUSE,  KC_TAB) 
#define LT_NUMB  LT(LY_NUMBER, _______) 
#define LT_FUNC  LT(LY_FUNC,   _______) 

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* BASE
   * ,------------------------------------------------.   ,------------------------------------------------.
   * | :Tab |   Q  |   W  |   E  |   R  |   T  |  [   |   |  ]   |   Y  |   U  |   I  |   O  |   P  |  @   |
   * |------+------+------+------+------+------+------|   |-------------+------+------+------+------+------|
   * | Ctrl |   A  |   S  |   D  |   F  |   G  |  (   |   |  )   |   H  |   J  |   K  |   L  |   ;  |  :   |
   * |------+------+------+------+------+------+------|   |------|------+------+------+------+------+------|
   * | Shfit|   Z  |   X  |   C  |   V  |   B  |  {   |   |  }   |   N  |   M  |   ,  |   .  |   /  |\/Sft |
   * |------+------+------+------+------+------+------|   |------+------+------+------+------+------+------|
   * | :NUMB| GUI  |  App |PrtSc | Alt  | Bksp | :Spc |   | CRSR |Enter |      |PrtSc |=>GAME|=>SYMB| FUNC |
   * `------------------------------------------------'   `------------------------------------------------'
   */
  [LY_NORMAL] = LAYOUT( \
    LT_MOUS,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC,          KC_RBRC,    KC_Y,   KC_U,    KC_I,     KC_O,     KC_P,     KC_BSPC, \
    KC_LCTRL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    S(KC_8),          S(KC_9),    KC_H,   KC_J,    KC_K,     KC_L,     KC_SCLN,  KC_QUOT, \
    KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    S(KC_LBRC),       S(KC_RBRC), KC_N,   KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT, \
    LT_NUMB,  KC_APP,  KC_LGUI, KC_LALT, LT_FUNC, KC_BSPC, LT_CRSR,          LT_CRSR,    KC_ENT, _______, _______,  _______,  _______,  LT_FUNC \
  ),

  /* LY_CURSOR
   * ,------------------------------------------------.   ,------------------------------------------------.
   * |   1  |   2  |   3  |   4  |   5  |   6  |  [   |   |  ]   |   7  |   8  |   9  |   0  |   -  |  ^   |
   * |------+------+------+------+------+------+------|   |-------------+------+------+------+------+------|
   * | Alt  |  F1  |      |Muhen | Henk |      |  (   |   |  )   | Left | Down |  Up  |Right |      |      |
   * |------+------+------+------+------+------+------|   |------|------+------+------+------+------+------|
   * | Sft  |  F2  |  F3  |  F4  |  F5  |  F6  |  {   |   |  }   |  F7  |  F8  |  F9  | F10  | F11  |\/Sft |
   * |------+------+------+------+------+------+------|   |------+------+------+------+------+------+------|
   * | Ctrl | GUI  |  App |PrtSc |ESC/  |Space/|Tab/  |   |Back  |Enter/| Del  |Reset |=>GAME|=>SYMB|  \   |
   * |      |      |      |      |~SYMB |RCtrl |Shift |   |Space |~META |      |      |      |      |      |
   * `------------------------------------------------'   `------------------------------------------------'
   */
  [LY_CURSOR] = LAYOUT( \
/*
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    _______, _______, KC_7,    KC_8,    KC_9,  KC_0,    KC_MINS, KC_EQL, \
    _______, KC_F1,   XXXXXXX, KC_MHEN, KC_HENK, XXXXXXX, _______, _______, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, XXXXXXX, XXXXXXX, \
    _______, KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   _______, _______, KC_F7,   KC_F8,   KC_F9, KC_F10,  KC_F11,  SFT_T(KC_RO), \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET, _______, _______, _______ \
*/
    KC_ESC,  _______, _______, KC_END,  _______, KC_TAB,  _______,    _______, KC_HOME, KC_PGDN, KC_PGUP,  _______,    KC_PSCR,   KC_LBRC, \
    KC_LCTL, KC_HOME, KC_SPC,  KC_DEL,  _______, _______, _______,    KC_HOME, KC_LEFT, KC_DOWN, KC_UP,    KC_RGHT,    KC_END,    KC_QUOT, \
    KC_LSFT, _______, _______, _______, _______, KC_BSPC, _______,    _______, KC_ENT,  _______, KC_COMM,  KC_DOT,     KC_SLSH,   KC_RO,   \
    _______, S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5), _______,    _______, S(KC_8), S(KC_9), S(KC_0),  S(KC_MINS), S(KC_EQL), KC_MINS \
),

  /* LaYer MOUSE
   * ,------------------------------------------------.   ,------------------------------------------------.
   * |   !  |   "  |   #  |   $  |   %  |   &  |  [   |   |  ]   |   '  |   (  |   )  |   ~  |   =  |  ~   |
   * |------+------+------+------+------+------+------|   |-------------+------+------+------+------+------|
   * | Alt  |      |      |      |      |      |  (   |   |  )   |      |      |      |      |   +  |  *   |
   * |------+------+------+------+------+------+------|   |------|------+------+------+------+------+------|
   * | Sft  |      |      |      |      |      |  {   |   |  }   |      |      |   <  |   >  |   ?  |  \   |
   * |------+------+------+------+------+------+------|   |------+------+------+------+------+------+------|
   * | Ctrl | GUI  |  App |PrtSc |ESC/  |Space/|Tab/  |   |Back  |Enter/| Del  |PrtSc |=>GAME|=>SYMB|  \   |
   * |      |      |      |      |~SYMB |RCtrl |Shift |   |Space |~META |      |      |      |      |      |
   * `------------------------------------------------'   `------------------------------------------------'
   */
  [LY_MOUSE] = LAYOUT( \
    _______, KC_BTN1, KC_BTN2, XXXXXXX, KC_TAB,  XXXXXXX, _______, _______, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, _______, _______, \
    KC_LCTL, KC_VOLU, KC_MUTE, KC_VOLU, XXXXXXX, XXXXXXX, _______, _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______, _______, \
    KC_LSFT, S(KC_2), S(KC_3), S(KC_4), XXXXXXX, S(KC_6), _______, _______, KC_BTN1, KC_BTN2, KC_BTN3, KC_BTN4, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
  ),

  /* LaYer NUMBER
   * ,------------------------------------------------.   ,------------------------------------------------.
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |  [   |   |  ]   |   Y  |   U  |   I  |   O  |   P  |  @   |
   * |------+------+------+------+------+------+------|   |-------------+------+------+------+------+------|
   * | Alt  |   A  |   S  |   D  |   F  |   G  |  (   |   |  )   |   H  |   J  |   K  |   L  |   ;  |  :   |
   * |------+------+------+------+------+------+------|   |------|------+------+------+------+------+------|
   * | Sft  |   Z  |   X  |   C  |   V  |   B  |  {   |   |  }   |   N  |   M  |   ,  |   .  |   /  |\/Sft |
   * |------+------+------+------+------+------+------|   |------+------+------+------+------+------+------|
   * | Ctrl | GUI  |  App |PrtSc | ESC  |Space |Tab   |   |Back  |Enter | Del  |PrtSc |=>GAME|=>SYMB|  \   |
   * |      |      |      |      |      |      |      |   |Space |      |      |      |      |      |      |
   * `------------------------------------------------'   `------------------------------------------------'
   */
  [LY_NUMBER] = LAYOUT( \
    KC_TAB,  _______, _______, KC_ENT,  _______, _______, _______,    _______,  _______, KC_7,    KC_8,    KC_9,    KC_MINS, KC_EQL,  \
    _______, _______, KC_SPC,  KC_DEL,  _______, _______, _______,    _______,  KC_BSPC, KC_4,    KC_5,    KC_6,    JP_PLUS, JP_ASTR, \
    _______, KC_UNDO, KC_CUT,  KC_COPY, KC_PASTE,KC_BSPC, _______,    _______,  KC_0,    KC_1,    KC_2,    KC_3,    KC_DOT,  KC_SLSH, \
    _______, _______, _______, _______, _______, _______, _______,    _______,  KC_ENT,  _______, _______, _______, _______, _______  \
  ),

  /* LaYer FUNCtion
   * ,------------------------------------------------.   ,------------------------------------------------.
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |  [   |   |  ]   |   Y  |   U  |   I  |   O  |   P  |  @   |
   * |------+------+------+------+------+------+------|   |-------------+------+------+------+------+------|
   * | Alt  |   A  |   S  |   D  |   F  |   G  |  (   |   |  )   |   H  |   J  |   K  |   L  |   ;  |  :   |
   * |------+------+------+------+------+------+------|   |------|------+------+------+------+------+------|
   * | Sft  |   Z  |   X  |   C  |   V  |   B  |  {   |   |  }   |   N  |   M  |   ,  |   .  |   /  |\/Sft |
   * |------+------+------+------+------+------+------|   |------+------+------+------+------+------+------|
   * | Ctrl | GUI  |  App |PrtSc | ESC  |Space |Tab   |   |Back  |Enter | Del  |PrtSc |=>GAME|=>SYMB|  \   |
   * |      |      |      |      |      |      |      |   |Space |      |      |      |      |      |      |
   * `------------------------------------------------'   `------------------------------------------------'
   */
  [LY_FUNC] = LAYOUT( \
    S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5), S(KC_6),  S(KC_7),    S(KC_8),    S(KC_9), S(KC_0), S(KC_MINS), S(KC_EQL),  S(KC_NUBS), S(KC_GRV), \
    KC_LCTRL, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,      KC_F7,      KC_F8,   KC_F9,   KC_F10,     KC_F11,     KC_F12,     KC_LBRC, \
    KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    S(KC_RBRC), S(KC_BSLS), KC_N,    KC_M,    KC_COMM,    KC_DOT,     KC_SLSH,    SFT_T(KC_RO), \
    RESET,    KC_LGUI, KC_APP,  KC_PSCR, KC_ESC,  KC_SPC,  KC_TAB,     KC_BSPC,    KC_ENT,  KC_DELT, KC_PSCR,    _______,    _______,    _______ \
  )

};

