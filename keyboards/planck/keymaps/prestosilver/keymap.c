/* Copyright 2015-2017 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "muse.h"
#include "keymap_steno.h"

#ifdef AUDIO_ENABLE
  float on_song[][2] = SONG(AUDIO_ON_SOUND);
  float off_song[][2] = SONG(AUDIO_OFF_SOUND);
  float caps_on_song[][2] = SONG(CAPS_LOCK_ON_SOUND);
  float caps_off_song[][2] = SONG(CAPS_LOCK_OFF_SOUND);
  float plover_song[][2] = SONG(PLOVER_SOUND);
  float gaming_song[][2] = SONG(NUM_LOCK_ON_SOUND);
  float gaming_off_song[][2] = SONG(NUM_LOCK_OFF_SOUND);
  float plover_off_song[][2] = SONG(PLOVER_GOODBYE_SOUND);
#endif

enum planck_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _MACRO,
  _PLOVER,
  _ADJUST,
  _GAMING,
  //_GAME,
};

enum planck_keycodes {
  MAC_W = SAFE_RANGE,
  M_Q_VIM,
  M_CD,
  M_BAK,
  M_LIST,
  M_CLS,
  M_UNI,
  PLOVER,
  EXT_PLOVER,
  GAMING,
  GAMING_OFF
};

enum {
  TD_BSSC,
  TD_BSDEL,
  TD_PRN,
  TD_BRC,
  TD_DOTCOMMA
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_BSSC] = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_SCLN),
  [TD_BSDEL] = ACTION_TAP_DANCE_DOUBLE(KC_BSPC, KC_DEL),
  [TD_PRN] = ACTION_TAP_DANCE_DOUBLE(KC_LPRN, KC_RPRN),
  [TD_BRC] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC),
  [TD_DOTCOMMA] = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_COMM)
};

//joystick config
//joystick_config_t joystick_axes[JOYSTICK_AXES_COUNT] = {
//      [0] = JOYSTICK_AXIS_VIRTUAL
//};

#define HEART   0x2764  // ❤
#define SMILE   0x263b  // ☻
#define POOP    0x263b  // ☻
#define COMMI   0x262d  // ☭

#define LOWER   LT(_LOWER, KC_MINUS)
#define RAISE   LT(_RAISE, KC_SLSH)
#define FLOAT   SGUI(KC_SPACE)
#define FLOAT   SGUI(KC_SPACE)
#define A_TAB   LALT(KC_TAB)
#define CLOSE   LALT(KC_F4)
#define FIND    LCTL(KC_F)
#define BSSC    TD(TD_BSSC)
#define BSDEL   TD(TD_BSDEL)
#define BRACE   TD(TD_BRC)
#define PAREN   TD(TD_PRN)
#define DOTCOM  TD(TD_DOTCOMMA)

static uint8_t old_usb_led = 0;
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   .  |   <  |   >  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | GAME | CTRL | Alt  | GUIM |Lower |    Space    |Raise |  Up  | Left | Down |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
    KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    BRACE,   KC_DEL,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    DOTCOM,  KC_LABK, KC_RABK, KC_ENT,
    GAMING,  KC_LCTL, KC_LALT, MAC_W,   LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |   _  |   {  |   }  |   +  |   :  | VOL- | VOL+ | Home |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |  |   | End  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Prev | Prev | Play | Next |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,    KC_DEL,
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_UNDS, KC_LCBR, KC_RCBR, KC_PLUS, KC_COLN, KC_VOLD, KC_VOLU,    KC_HOME,
    _______, KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PIPE,    KC_END,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_MPLY, KC_MPLY,    KC_MNXT
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |   :  |   [  |   ]  |   =  |  ;   |   '  |   \  |Pg Up |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |INSERT|Pg Dn |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Prev | Prev | Play | Next |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_COLN, KC_LBRC, KC_RBRC, KC_EQL,  KC_SCLN, KC_QUOT, KC_BSLS, KC_PGUP,
    _______, KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS,  KC_PGDN,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_MPLY, KC_MPLY, KC_MNXT
),

/* Macro layer
 * ,-----------------------------------------------------------------------------------.
 * | home | Q_VIM|      |Close | Reset|  7   |  8   |  9   |  A   |  B   | BACK | Back |
 * |------+------+      +------+------+------+------+------+------+------+------+------|
 * |Switch|       ARROWS       | Sleep|  4   |  5   |  6   |  C   |  D   | FWD  | Enter|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |LClick|MClick|RClick| Clear|  1   |  2   |  3   |  E   |  F   | Find | List |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Back |      |      |      |      |    ENTER    |  0   |           MOUSE           |
 * `-----------------------------------------------------------------------------------'
 */
[_MACRO] = LAYOUT_planck_grid(
    M_CD,   M_Q_VIM,   KC_UP,      CLOSE,      RESET,           KC_P7,   KC_P8,   KC_P9,   KC_A,    KC_B,    KC_WBAK,   KC_BSPC,
    A_TAB,  KC_LEFT,   KC_DOWN,    KC_RIGHT,   KC_SYSTEM_SLEEP, KC_P4,   KC_P5,   KC_P6,   KC_C,    KC_D,    KC_WFWD,   KC_ENT,
    GAMING, KC_MS_BTN1,KC_MS_BTN3, KC_MS_BTN2, M_CLS,           KC_P1,   KC_P2,   KC_P3,   KC_E,    KC_F,    FIND,      M_LIST,
    _______,XXXXXXX,   XXXXXXX,    _______,    XXXXXXX,         KC_PENT, KC_PENT, KC_P0,   KC_MS_LEFT, KC_MS_UP, KC_MS_DOWN,KC_MS_RIGHT
),

/* Plover layer (http://opensteno.org)
 * ,-----------------------------------------------------------------------------------.
 * |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  FN  |   S  |   T  |   P  |   H  |   *  |   *  |   F  |   P  |   L  |   T  |   D  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Exit |   S  |   K  |   W  |   R  |   *  |   *  |   R  |   B  |   G  |   S  |   Z  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |   A  |   O  |             |   E  |   U  |  PWR | RES1 | RES2 |
 * `-----------------------------------------------------------------------------------'
 */

[_PLOVER] = LAYOUT_planck_grid(
  STN_N1,      STN_N2,  STN_N3,  STN_N4,  STN_N5,  STN_N6,  STN_N7,  STN_N8,  STN_N9,  STN_NA,  STN_NB,  STN_NC ,
  STN_FN,      STN_S1,  STN_TL,  STN_PL,  STN_HL,  STN_ST1, STN_ST3, STN_FR,  STN_PR,  STN_LR,  STN_TR,  STN_DR ,
  EXT_PLOVER,  STN_S2,  STN_KL,  STN_WL,  STN_RL,  STN_ST2, STN_ST4, STN_RR,  STN_BR,  STN_GR,  STN_SR,  STN_ZR ,
  XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, STN_A,   STN_O,   XXXXXXX, STN_E,   STN_U,   STN_PWR, STN_RE1, STN_RE2
),

/* Adjust (Lower + Raise)
 *                      v------------------------RGB CONTROL--------------------v
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|      | RGB  |RGBMOD| HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|  Del |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |MUSmod|Aud on|Audoff|AGnorm|AGswap|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|TermOn|TermOf|      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    _______, RESET,   _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,  RGB_VAI, RGB_VAD, KC_DEL ,
    _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, CK_TOGG, _______,  _______, _______, _______,
    _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______
),

/*
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Q  |   W  |   E  | Tab  |   T  |   Y  |   U  |   I  |   O  |Enter | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | CTRL |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  | Prev |  Up  | Next |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | GAME |   Z  |   X  |   C  |Lower |    Space    |Raise | Play | Left | Down |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_GAMING] = LAYOUT_planck_grid(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    KC_LSFT, KC_Q,    KC_W,    KC_E,    KC_TAB,  KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_ENT,  KC_DEL,
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_MPRV, KC_UP,   TO(_QWERTY),
    GAMING_OFF,  KC_Z,    KC_X,    KC_C,    KC_SPC,  KC_SPC,  KC_SPC,  KC_SPC,  KC_MPLY, KC_LEFT, KC_DOWN, KC_RGHT
),

/*
 * ,-----------------------------------------------------------------------------------.
 * | PAUSE|      |      |      |      |      |      |      |      | RB   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | LT   | X    |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | LB   | A    | B    | Y    |      |             |      |      |      | UP   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      | LEFT | DOWN | RIGHT|
 * `-----------------------------------------------------------------------------------'
 */
//[_GAME] = LAYOUT_planck_grid(
//    JS_BUTTON10,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
//    KC_LSFT, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_ENT,  KC_DEL,
//    KC_LCTRL,KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_MPRV, KC_UP,   KC_MNXT,
//    XXXXXXX, KC_Z,    KC_X,    KC_C,    KC_SPC,  KC_SPC,  KC_SPC,  KC_SPC,  KC_MPLY, KC_LEFT, KC_DOWN, KC_RGHT
//)

};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static uint16_t macro_hash_timer;
  static uint8_t layer;
  if (muse_mode) {
    return true;
  }
  switch (keycode) {
    case M_Q_VIM:
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(X_ESCAPE) SS_LSFT(SS_TAP(X_SCLN)) "wq!" SS_TAP(X_ENTER));
      }
      return false;
      break;
    case M_CD:
      if (record->event.pressed) {
        SEND_STRING("cd ~" SS_TAP(X_ENTER));
      }
      return false;
      break;
    case M_CLS:
      if (record->event.pressed) {
        SEND_STRING("clear" SS_TAP(X_ENTER));
      }
      return false;
      break;
    case M_BAK:
      if (record->event.pressed) {
        SEND_STRING("cd .." SS_TAP(X_ENTER));
      }
      return false;
      break;
    case M_LIST:
      if (record->event.pressed) {
        SEND_STRING("ls" SS_TAP(X_ENTER));
      }
      return false;
      break;
    case MAC_W:
      if (record->event.pressed) {
        layer = get_highest_layer(layer_state);
        macro_hash_timer = timer_read();
        register_code(KC_LGUI);
        layer_off(_MACRO);
      }else{
        unregister_code(KC_LGUI);
        layer_on(layer);
        if (timer_elapsed(macro_hash_timer) < TAPPING_TERM) {
          if (layer == _MACRO){
            layer_off(_MACRO);
            #ifdef AUDIO_ENABLE
              PLAY_SONG(off_song);
            #endif
          }
          else
          {
            layer_on(_MACRO);
            #ifdef AUDIO_ENABLE
              PLAY_SONG(on_song);
            #endif
          }
        }
      }
      return false;
      break;
    case GAMING:
      if (!record->event.pressed) {
        #ifdef AUDIO_ENABLE
          stop_all_notes();
          PLAY_SONG(gaming_song);
        #endif
        layer_on(_GAMING);
      }
      return false;
      break;
    case GAMING_OFF:
      if (!record->event.pressed) {
        #ifdef AUDIO_ENABLE
          stop_all_notes();
          PLAY_SONG(gaming_off_song);
        #endif
        layer_off(_GAMING);
      }
      return false;
      break;
    case PLOVER:
      if (!record->event.pressed) {
        #ifdef AUDIO_ENABLE
          stop_all_notes();
          PLAY_SONG(plover_song);
        #endif
        layer_on(_PLOVER);
      }
      return false;
      break;
    case EXT_PLOVER:
      if (!record->event.pressed) {
        #ifdef AUDIO_ENABLE
          stop_all_notes();
          PLAY_SONG(plover_off_song);
        #endif
        layer_off(_PLOVER);
      }
      return false;
      break;
  }
  return true;
}


void encoder_update(bool clockwise) {
  if (muse_mode) {
    if (clockwise) {
      muse_offset++;
    } else {
      muse_offset--;
    }
  } else {
    if (IS_LAYER_ON(_GAMING)) {
      if (clockwise) {
        tap_code(KC_VOLD);
      } else {
        tap_code(KC_VOLU);
      }
    } else {
      if (clockwise) {
        #ifdef MOUSEKEY_ENABLE
          tap_code(KC_MS_WH_DOWN);
        #else
          tap_code(KC_PGDOWN);
        #endif
      } else {
        #ifdef MOUSEKEY_ENABLE
          tap_code(KC_MS_WH_UP);
        #else
          tap_code(KC_PGUP);
        #endif
      }
    }
  }
}

bool dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0: {
            if (active) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            break;
        }
        case 1:
            if (active) {
                muse_mode = true;
            } else {
                muse_mode = false;
            }
    }
    return true;
}

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    } else {
        if (muse_counter) {
            stop_all_notes();
            muse_counter = 0;
        }
    }
#endif
}


bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
    case MAC_W:
      return false;
    default:
      return true;
  }
}

#ifdef AUDIO_ENABLE
void led_set_user(uint8_t usb_led)
{
  if (!is_playing_notes())
  {
    if ((usb_led & (1<<USB_LED_CAPS_LOCK)) && !(old_usb_led & (1<<USB_LED_CAPS_LOCK)))
    {
      PLAY_SONG(caps_on_song);
    }
    else if (!(usb_led & (1<<USB_LED_CAPS_LOCK)) && (old_usb_led & (1<<USB_LED_CAPS_LOCK)))
    {
      PLAY_SONG(caps_off_song);
    }
  }
  old_usb_led = usb_led;
}
#endif
