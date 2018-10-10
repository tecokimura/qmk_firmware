#include "helix.h"
#include "bootloader.h"
#include "action_layer.h"
#include "eeconfig.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#include "LUFA/Drivers/Peripheral/TWI.h"
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

// * If you want to recognize that you pressed the Adjust key with the Lower / Raise key you can enable this comment out. However, the binary size may be over. *
// #define ADJUST_MACRO_ENABLE

// * If you want to use the Kana key you can enable this comment out. However, the binary size may be over. *
// #define KANA_ENABLE

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
  _BASE = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
  _RFN,
};

enum custom_keycodes {
  BASE = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  RFN,
  EISU,
  #ifdef KANA_ENABLE
  KANA,
  #endif
  RGBRST
};

// JIS key aliases
#define JP_CFTD KC_EQL   // ^ and ~ Circumflex (Hat) and Tilde
#define JP_ATBQ KC_LBRC  // @ and ` Atmark and Back-quote
#define JP_CLAS KC_QUOT  // : and * Colon and Asterisk
#define JP_BSVL KC_JYEN  // \ and | Back slash and and Vertical-line)
#define JP_LBRC KC_RBRC  // [ and { Left-bracket
#define JP_RBRC KC_BSLS  // ] and } Right-bracket
#define JP_BSUS KC_RO    // \ and _ Back slash and Under-score

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// tecokimura original
#define MAC_IMEOFF    LCTL(LSFT(KC_SCLN)) // OS X. IME OFF
#define MAC_IMEON     LCTL(LSFT(KC_J))    // OS X. IME ON
#define MAC_HEN_EISU  LCTL(KC_SCLN)       // OS X. IME Henkan Eisu

#define LT_SPC  LT(RAISE,  KC_SPC)
#define LT_TAB  LT(ADJUST, KC_TAB)
#define LT_LFN  LT(LOWER,  KC_ESC)


#if HELIX_ROWS == 5
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Qwerty JIS Normal
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | Esc  |  1!  |  2"  |  3#  |  4$  |  5%  |             |  6&  |  7'  |  8(  |  9)  |   0  |  -=  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  |  @`  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Ctrl |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |  ;+  |  :*  |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |Adjust| EISU |   N  |   M  |  ,<  |  .>  |  /?  |  \_  |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Lower| GUI  | Alt  | Ctrl | Bksp |Space |Enter |RAISE |Space |Enter | APP  | Left | Down |Shift |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_BASE] = LAYOUT( \
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, \
    LT_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    JP_ATBQ, \
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, JP_CLAS, \
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    ADJUST,  EISU,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, JP_BSUS, \
    LOWER,   KC_LALT, KC_LGUI, KC_LCTL, KC_BSPC, KC_SPC,  KC_ENT,  RAISE,   LT_SPC,  KC_ENT,  KC_APP,  RFN,     XXXXXXX, KC_RSFT  \
    ),

  /* Lower JIS Normal
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |  ESC |      |      |      |      | Bksp |             |      |      |      |  -=  |  ^~  |  \|  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |   (  |   )  |   /  |   7  |   8  |   9  |             |WheelL|WheelD|WheelU|WheelR|  @`  |  [{  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |   [  |   ]  |   *  |   4  |   5  |   6  |             |MouseL|MouseD|MouseU|MouseR|  :*  |  ]}  |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |   {  |   }  |   -  |   1  |   2  |   3  |  Tab |      |Click1|Click2|Click3|Click4|Click5|  \_  |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |   +  |   0  |   ,  |   .  | Enter|      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_LOWER] = LAYOUT( \
    KC_ESC,  _______, _______,   _______, _______, KC_BSPC,                 XXXXXXX, XXXXXXX, XXXXXXX, KC_MINS, JP_CFTD, JP_BSVL, \
    KC_LPRN, KC_RPRN, KC_SLSH,   KC_7,    KC_8,    KC_9,                    KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, JP_ATBQ, JP_LBRC, \
    JP_LBRC, JP_RBRC, KC_ASTR,   KC_4,    KC_5,    KC_6,                    KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, JP_CLAS, JP_RBRC, \
    KC_LCBR, KC_RCBR, KC_MINS,   KC_1,    KC_2,    KC_3,   KC_TAB, XXXXXXX, KC_BTN1, KC_BTN2, KC_BTN3, KC_BTN4, KC_BTN5, JP_BSUS, \
    _______, _______, KC_PLUS,   KC_0,    KC_COMM, KC_DOT, KC_ENT, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX  \
    ),

  /* Raise JIS Normal
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |             |  F7  |  F8  |  F9  |  F10 |  F11 | F12  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |  F7  |  F8  |  F9  |  F10 |  F11 | F12  |             | Home |PageDn|PageUp| End  |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |HOME  |Space | Del  |      |      |             | Left | Down |  Up  | Right|      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |MsBtn1|MsBtn2|      |      |      |      |      |      |IME ON|IMEOFF|      | MsUp |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |MsLeft|MsDown|MsRght|
   * `-------------------------------------------------------------------------------------------------'
   */
  [_RAISE] = LAYOUT( \
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     _______, XXXXXXX,      XXXXXXX,   XXXXXXX,    XXXXXXX, KC_DEL,  \
    KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,                    KC_HOME, KC_PGDN,      KC_PGUP,   KC_END,     _______, KC_BSPC, \
    KC_LCTL, KC_HOME, KC_SPC,  KC_DEL,  XXXXXXX, XXXXXXX,                   KC_LEFT, KC_DOWN,      KC_UP,     KC_RIGHT,   KC_END,  KC_ENT, \
    _______, KC_BTN1, KC_BTN2, XXXXXXX, XXXXXXX, KC_BSPC, XXXXXXX, XXXXXXX, KC_ENT,  MAC_HEN_EISU, MAC_IMEON, MAC_IMEOFF, KC_MS_U, XXXXXXX, \
    _______, _______, _______, _______, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX, XXXXXXX,      XXXXXXX,   KC_MS_L,    KC_MS_D, KC_MS_R  \
    ),

  /* Adjust (Lower + Raise) Common map for Normal and Exchange
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |  ESC |      |      |      |      | Bksp |             |      |      |      |  -=  |  ^~  |  \|  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |   (  |   )  |   /  |   7  |   8  |   9  |             |WheelL|WheelD|WheelU|WheelR|  @`  |  [{  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |   [  |   ]  |   *  |   4  |   5  |   6  |             |MouseL|MouseD|MouseU|MouseR|  :*  |  ]}  |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |   {  |   }  |   -  |   1  |   2  |   3  |  Tab |      |Click1|Click2|Click3|Click4|Click5|  \_  |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |   +  |   0  |   ,  |   .  | Enter|      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_ADJUST] =  LAYOUT( \
    RESET,   _______, _______,   _______, _______, KC_BSPC,                 XXXXXXX, XXXXXXX, XXXXXXX, KC_MINS, JP_CFTD, JP_BSVL, \
    KC_LPRN, KC_RPRN, KC_SLSH,   KC_7,    KC_8,    KC_9,                    KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, JP_ATBQ, JP_LBRC, \
    JP_LBRC, JP_RBRC, KC_ASTR,   KC_4,    KC_5,    KC_6,                    KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, JP_CLAS, JP_RBRC, \
    KC_LCBR, KC_RCBR, KC_MINS,   KC_1,    KC_2,    KC_3,   KC_TAB, XXXXXXX, KC_BTN1, KC_BTN2, KC_BTN3, KC_BTN4, KC_BTN5, JP_BSUS, \
    _______, _______, KC_PLUS,   KC_0,    KC_COMM, KC_DOT, KC_ENT, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX  \
    ),

  /* _RFN Common map for Normal and Exchange
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |Reset |      |RGBRST|Aud on|Audoff|      |             |      | Reset|RGBRST|Aud on|Audoff|      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |ModNrm|ModExc| Mac  | Win  |      |             |      |ModNrm|ModExc| Mac  | Win  |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------|------+
   * |      |RGB ON| HUE+ | SAT+ | VAL+ |      |             |      |RGB ON| HUE+ | SAT+ | VAL+ |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------|------+
   * |      | MODE | HUE- | SAT- | VAL- |      |      |      |      | MODE | HUE- | SAT- | VAL- |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_RFN] =  LAYOUT( \
    RESET,   XXXXXXX, RGBRST,  AU_ON,   AU_OFF,  XXXXXXX,                   XXXXXXX, RESET,   RGBRST,  AU_ON,   AU_OFF,  XXXXXXX, \
    XXXXXXX, BASE,    XXXXXXX, AG_NORM, AG_SWAP, XXXXXXX,                   XXXXXXX, BASE,    XXXXXXX,   AG_NORM, AG_SWAP, XXXXXXX, \
    XXXXXXX, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX,                   XXXXXXX, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, \
    XXXXXXX, RGB_SMOD,RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_SMOD,RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
    ),

};

#elif HELIX_ROWS == 4

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	// Do it yourself :)
};

#else
#error "undefined keymaps"
#endif


#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);
#endif

// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

#ifdef ADJUST_MACRO_ENABLE
// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    #ifdef RGBLIGHT_ENABLE
      rgblight_mode(RGB_current_mode);
    #endif
    layer_on(layer3);
   } else {
    layer_off(layer3);
  }
}
#endif

void toggle_lower_raise_layer(bool pressed, uint16_t dist_layer, uint16_t lower_layer, uint16_t raise_layer) {
  if (pressed) {
    //not sure how to have keyboard check mode and set it to a variable, so my work around
    //uses another variable that would be set to true after the first time a reactive key is pressed.
    if (!TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
      TOG_STATUS = !TOG_STATUS;
      #ifdef RGBLIGHT_ENABLE
        if (dist_layer == _LOWER ) {
          rgblight_mode(16);
        } else {
          rgblight_mode(15);
        }
      #endif
    }

    layer_on(dist_layer);
    #ifdef ADJUST_MACRO_ENABLE
      update_tri_layer_RGB(lower_layer, raise_layer, _ADJUST);
    #endif
  } else {
    #ifdef RGBLIGHT_ENABLE
      rgblight_mode(RGB_current_mode);   // revert RGB to initial mode prior to RGB mode change
    #endif
    TOG_STATUS = false;
    layer_off(dist_layer);
    #ifdef ADJUST_MACRO_ENABLE
      update_tri_layer_RGB(lower_layer, raise_layer, _ADJUST);
    #endif
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case BASE:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_BASE);
      }
      return false;
      break;
    case LOWER:
      toggle_lower_raise_layer(record->event.pressed, _LOWER, _LOWER, _RAISE);
      return false;
      break;
    case RAISE:
      toggle_lower_raise_layer(record->event.pressed, _RAISE, _LOWER, _RAISE);
      return false;
      break;
    case ADJUST:
        if (record->event.pressed) {
          #ifdef RGBLIGHT_ENABLE
            rgblight_mode(14);
          #endif
          layer_on(_ADJUST);
        } else {
          #ifdef RGBLIGHT_ENABLE
            rgblight_mode(RGB_current_mode);
          #endif
          layer_off(_ADJUST);
        }
        return false;
        break;
    //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case EISU:
      if (record->event.pressed) {
        if (keymap_config.swap_lalt_lgui==false) {
          register_code(KC_LANG2);
        } else {
          SEND_STRING(SS_LALT("`"));
        }
      } else {
        unregister_code(KC_LANG2);
      }
      return false;
      break;
    #ifdef KANA_ENABLE
    case KANA:
      if (record->event.pressed) {
        if(keymap_config.swap_lalt_lgui==false){
          register_code(KC_LANG1);
        }else{
          SEND_STRING(SS_LALT("`"));
        }
      } else {
        unregister_code(KC_LANG1);
      }
      return false;
      break;
    #endif
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
  }

  return true;
  // return process_layer_control(keycode, record, false) ? process_layer_control(keycode, record, true) : true;
}

void matrix_init_user(void) {
  #ifdef AUDIO_ENABLE
    startup_user();
  #endif
  #ifdef RGBLIGHT_ENABLE
    RGB_current_mode = rgblight_config.mode;
  #endif
  //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
  #ifdef SSD1306OLED
    TWI_Init(TWI_BIT_PRESCALE_1, TWI_BITLENGTH_FROM_FREQ(1, 800000));
    iota_gfx_init(!has_usb());   // turns on the display
  #endif
}


#ifdef AUDIO_ENABLE

void startup_user()
{
  _delay_ms(20); // gets rid of tick
}

void shutdown_user()
{
  _delay_ms(150);
  stop_all_notes();
}

void music_on_user(void)
{
  music_scale_user();
}

void music_scale_user(void)
{
  PLAY_SONG(music_scale);
}

#endif


//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

void matrix_scan_user(void) {
  iota_gfx_task();  // this is what updates the display continuously
}

void matrix_update(struct CharacterMatrix *dest,
                          const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

//assign the right code to your layers for OLED display
#define L_BASE _BASE
#define L_LOWER (1<<_LOWER)
#define L_RAISE (1<<_RAISE)
#define L_ADJUST (1<<_ADJUST)
#define L_ADJUST_TRI (L_ADJUST|L_RAISE|L_LOWER)

static void render_logo(struct CharacterMatrix *matrix) {

  static char logo[]={
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,
    0};
  matrix_write(matrix, logo);
  //matrix_write_P(&matrix, PSTR(" Split keyboard kit"));
}



void render_status(struct CharacterMatrix *matrix) {

  // Render to mode icon
  static char logo[][2][3]={{{0x95,0x96,0},{0xb5,0xb6,0}},{{0x97,0x98,0},{0xb7,0xb8,0}}};
  if(keymap_config.swap_lalt_lgui==false){
    matrix_write(matrix, logo[0][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write(matrix, logo[0][1]);
  } else {
    matrix_write(matrix, logo[1][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write(matrix, logo[1][1]);
  }

  // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below
  char buf[16];
  matrix_write_P(matrix, PSTR("\nLayer: "));
    switch (layer_state) {
      case L_BASE:
        matrix_write_P(matrix, PSTR("tecokimura"));
        break;
      case L_RAISE:
        matrix_write_P(matrix, PSTR("Raise"));
        break;
      case L_LOWER:
        matrix_write_P(matrix, PSTR("Lower"));
        break;
      case L_ADJUST:
      case L_ADJUST_TRI:
        matrix_write_P(matrix, PSTR("Adjust"));
        break;
      default:
        snprintf(buf, sizeof(buf), "Undef-%d", (short)layer_state);
        matrix_write(matrix, buf);
    }

  // Host Keyboard LED Status
  char led[32];
  snprintf(led, sizeof(led), "\n%s  %s  %s",
          (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) ? "NUMLOCK" : "       ",
          (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) ? "CAPS" : "    ",
          (host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK)) ? "SCLK" : "    ");
  matrix_write(matrix, led);
}


void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;

#if DEBUG_TO_SCREEN
  if (debug_enable) {
    return;
  }
#endif

  matrix_clear(&matrix);
  if (is_master) {
    render_status(&matrix);
  } else {
    render_logo(&matrix);
  }

  matrix_update(&display, &matrix);
}

#endif
