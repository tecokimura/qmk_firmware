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
#define LT_MOUS  LT(LY_MOUSE,  KC_ESC) 
#define LT_NUMB  LT(LY_NUMBER, KC_TAB) 
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
    LT_MOUS,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    JP_CIRC,          JP_YEN,     KC_Y,    KC_U,   KC_I,     KC_O,     KC_P,     KC_MINS, \
    KC_LCTRL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    JP_LPRN,          JP_RPRN,    KC_H,    KC_J,   KC_K,     KC_L,     KC_SCLN,  JP_COLN, \
    KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    JP_LBRC,          JP_RBRC,    KC_N,    KC_M,   KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT, \
    LT_NUMB,  KC_LGUI, KC_LALT, KC_APP,  KC_BSPC, LT_CRSR, LT_FUNC,          LT_NUMB,    LT_CRSR, KC_ENT, _______,  JP_ZHTG,  _______,  LT_FUNC \
  ),

  /* LY_CURSOR
   * ,------------------------------------------------.   ,------------------------------------------------.
   * |      |      |      |      |      |      |      |   |      |      | PgDn | PgUp | Home | PsCr | Bspc |
   * |------+------+------+------+------+------+------|   |-------------+------+------+------+------+------|
   * | Ctrl | HOME | Space| Del  |      |      |      |   | Home | Left | Down |  Up  |Right | End  |  '   |
   * |------+------+------+------+------+------+------|   |------|------+------+------+------+------+------|
   * | Sft  |  F2  |  F3  |  F4  |  F5  |  F6  |  {   |   |  }   |  F7  |  F8  |  F9  | F10  | F11  |\/Sft |
   * |------+------+------+------+------+------+------|   |------+------+------+------+------+------+------|
   * | Ctrl | GUI  |  App |PrtSc |ESC/  |Space/|Tab/  |   |Back  |Enter/| Del  |Reset |=>GAME|=>SYMB|  \   |
   * |      |      |      |      |~SYMB |RCtrl |Shift |   |Space |~META |      |      |      |      |      |
   * `------------------------------------------------'   `------------------------------------------------'
   */
  [LY_CURSOR] = LAYOUT( \
    _______, _______, _______, KC_END,  _______, KC_TAB,  _______,    _______, _______, KC_PGDN, KC_PGUP,  KC_HOME, KC_PSCR, KC_BSPC, \
    KC_LCTL, KC_HOME, KC_SPC,  KC_DEL,  _______, _______, _______,    KC_HOME, KC_LEFT, KC_DOWN, KC_UP,    KC_RGHT, KC_END,  KC_QUOT, \
    KC_LSFT, _______, _______, _______, _______, KC_BSPC, _______,    _______, KC_ENT,  KC_ENT,  _______,  _______, KC_SLSH, KC_RO,   \
    _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______,  _______, _______, _______ \
),

  /* LaYer MOUSE
   * ,------------------------------------------------.   ,------------------------------------------------.
   * |   !  |   "  |   #  |   $  |   %  |   &  |  [   |   |  ]   |   '  |   (  |   )  |   ~  |   =  |  ~   |
   * |------+------+------+------+------+------+------|   |-------------+------+------+------+------+------|
   * | Alt  |      |      |      |      |      |  (   |   |  )   |      |      |      |      |   +  |  *   |
   * |------+------+------+------+------+------+------|   |------|------+------+------+------+------+------|
   * | Sft  |      |      |      |      |      |  {   |   |  }   |      |      |   <  |   >  |   ?  |  \   |
   * |------+------+------+------+------+------+------|   |------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |   |      |      |      |      |      |   .  |      |
   * `------------------------------------------------'   `------------------------------------------------'
   */
  [LY_MOUSE] = LAYOUT( \
    _______, KC_BTN1, KC_BTN2, _______, KC_TAB,  XXXXXXX, _______,    _______, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, _______, _______, \
    KC_LCTL, KC_VOLU, KC_MUTE, KC_VOLU, XXXXXXX, XXXXXXX, _______,    _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______, _______, \
    KC_LSFT, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,      _______, KC_BTN1, KC_BTN2, KC_BTN3, KC_BTN4, _______, _______, \
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,     _______, _______, _______, _______, _______, _______, _______ \
  ),

  /* LaYer NUMBER
   * ,------------------------------------------------.   ,------------------------------------------------.
   * | Tab  |      |      | Enter|      |      |      |   |      |      |   7  |   8  |   9  |   -  |  =   |
   * |------+------+------+------+------+------+------|   |-------------+------+------+------+------+------|
   * |      |      | Space|  Del |      |      |      |   |      | Bspc |   4  |   5  |   6  |   +  |  *   |
   * |------+------+------+------+------+------+------|   |------|------+------+------+------+------+------|
   * |      | UNDO |  Cut | Copy | Paste| Bspc |      |   |      |   0  |   1  |   2  |   3  |   /  |\/Sft |
   * |------+------+------+------+------+------+------|   |------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |   |      |Enter |      |      |      |   .  |      |
   * `------------------------------------------------'   `------------------------------------------------'
   */
  [LY_NUMBER] = LAYOUT( \
    _______, _______, _______, KC_ENT,  _______, KC_TAB,  _______,    _______,  _______, KC_7,    KC_8,    KC_9,    KC_MINS, KC_EQL,  \
    _______, _______, KC_SPC,  KC_DEL,  _______, _______, _______,    _______,  KC_BSPC, KC_4,    KC_5,    KC_6,    JP_PLUS, JP_ASTR, \
    _______, KC_UNDO, KC_CUT,  KC_COPY, KC_PASTE,KC_BSPC, _______,    _______,  KC_0,    KC_1,    KC_2,    KC_3,    KC_SLSH, _______,\
    _______, _______, _______, _______, _______, _______, _______,    _______,  _______, _______, _______, _______, KC_DOT,  _______  \
  ),

  /* LaYer FUNCtion
   * ,------------------------------------------------.   ,------------------------------------------------.
   * |  !   |   @  |   #  |   $  |   %  |   ^  |  &   |   |  *   |   Y  |   U  |   I  |   O  |   P  |  @   |
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
 /*
    JP_EXLM,  JP_AT,   JP_HASH, JP_DLR,  JP_PERC, JP_CIRC, JP_AMPR,   JP_ASTR,  JP_LPRN,   JP_RPRN,     JP_UNDS, JP_PLUS, JP_PIPE, JP_TILD, \
    JP_EXLM,  JP_DQT,  JP_HASH, JP_DLR,  JP_PERC, JP_AMPR, JP_QUOT,   JP_LPRN,  JP_RPRN,   _______,     JP_EQL,  JP_TILD, JP_PIPE, KC_BSPC, \
 */
    JP_EXLM,  JP_DQT,  JP_HASH, JP_DLR,  JP_PERC, JP_AMPR, JP_QUOT,   JP_LPRN,  JP_RPRN,   _______,     JP_EQL,  JP_CIRC, JP_YEN,  KC_BSPC, \
    _______,  _______, _______, _______, _______, _______, _______,   KC_GRV,   _______,SFT_T(KC_RO),   _______, JP_AT,   JP_LBRC, JP_RBRC, \
    _______,  _______, _______, _______, _______, _______, _______,   _______,  _______,   _______,     JP_UNDS, JP_PLUS, JP_BSLS, KC_RSFT, \
    RESET,    _______, _______, _______, _______, _______, _______,   _______,  _______,   _______,     _______, _______, _______, _______  \
  )

};

