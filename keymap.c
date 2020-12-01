/* Copyright 2018 MechMerlin
 * Copyright 2018 Logan Huskins
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

enum custom_keycodes {
  CT_GRV = SAFE_RANGE, CT_2, CT_6, CT_7, CT_8, CT_9, CT_0, CT_MINS, CT_EQL,
  CT_LBRC, CT_RBRC, CT_BSLS,
  CT_SCLN, CT_QUOT
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Qwerty
   * ,-----------------------------------------------------------------------------------------.
   * | Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  | Backspace |
   * |-----------------------------------------------------------------------------------------+
   * |  Tab   |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |    \   |
   * |-----------------------------------------------------------------------------------------+
   * |  Caps   |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |    Enter    |
   * |-----------------------------------------------------------------------------------------+
   * |   Shift   |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  |      Shift      |
   * |-----------------------------------------------------------------------------------------+
   * | Ctrl  |  Alt  |  GUI  |              Space              |    ◀︎   |   ↑   |   ⬇︎   |  ▶︎  |
   * `-----------------------------------------------------------------------------------------'
   */
  [0] = LAYOUT_60_ansi(
    KC_ESC, KC_1, CT_2, KC_3, KC_4, KC_5, CT_6, CT_7, CT_8, CT_9, CT_0, CT_MINS, CT_EQL, KC_BSPC,
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, CT_LBRC, CT_RBRC, CT_BSLS,
    MO(1), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, CT_SCLN, CT_QUOT, KC_ENT,
    KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
    KC_LCTL, KC_LALT, KC_LGUI, KC_SPC, KC_LEFT, KC_UP, KC_DOWN, KC_RGHT
  ),

  /* Function
   * ,-----------------------------------------------------------------------------------------.
   * |  `  | F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 | F11 | F12 |    Del    |
   * |-----------------------------------------------------------------------------------------+
   * |        |     | Up  |     |     |     |     |     |     |     |PrtSc|ScrLk|Pause|        |
   * |-----------------------------------------------------------------------------------------+
   * |         |Left |Down |Right|     |     |     |     |     | Ins |Home |PgUp |             |
   * |-----------------------------------------------------------------------------------------+
   * |           |VolUp|VolDn|VolMu|     |     |     |     |     | End |PgDn |                 |
   * |-----------------------------------------------------------------------------------------+
   * |       |       |       |                                 |       |  L2   |       |       |
   * `-----------------------------------------------------------------------------------------'
   */
  [1] = LAYOUT_60_ansi(
    CT_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL,
    KC_TRNS, KC_TRNS, KC_UP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR, KC_SLCK, KC_PAUS, KC_TRNS,
    KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_INS, KC_HOME, KC_PGUP, KC_TRNS,
    KC_TRNS, KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_END, KC_PGDN, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  )
};

bool replace_us_to_jis(keyrecord_t *record, uint16_t replace, uint16_t original) {
  static bool lshift = false;
  if (record->event.pressed) {
    lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
    if (lshift) {
      unregister_code(KC_LSFT);
      register_code(replace);
      unregister_code(replace);
      register_code(KC_LSFT);
    } else {
      register_code(original);
      unregister_code(original);
    }
  }
  return false;
}

bool replace_us_to_jis_shifted(keyrecord_t *record, uint16_t replace, uint16_t original) {
  static bool lshift = false;
  if (record->event.pressed) {
    lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
    if (lshift) {
      if (lshift) unregister_code(KC_LSFT);
      register_code(KC_LSFT);
      register_code(replace);
      unregister_code(replace);
      unregister_code(KC_LSFT);
      if (lshift) register_code(KC_LSFT);
    } else {
      register_code(original);
      unregister_code(original);
    }
  }
  return false;
}

bool replace_us_to_jis_both_shifted(keyrecord_t *record, uint16_t replace, uint16_t original) {
  static bool lshift = false;
  if (record->event.pressed) {
    lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
    if (lshift) {
      if (lshift) unregister_code(KC_LSFT);
      register_code(KC_LSFT);
      register_code(replace);
      unregister_code(replace);
      unregister_code(KC_LSFT);
      if (lshift) register_code(KC_LSFT);
    } else {
      register_code(KC_LSFT);
      register_code(original);
      unregister_code(original);
      unregister_code(KC_LSFT);
    }
  }
  return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {
    case CT_GRV: return replace_us_to_jis_both_shifted(record, KC_EQL, KC_LBRC);
    case CT_2: return replace_us_to_jis(record, KC_LBRC, KC_2);
    case CT_6: return replace_us_to_jis(record, KC_EQL, KC_6);
    case CT_7: return replace_us_to_jis_shifted(record, KC_6, KC_7);
    case CT_8: return replace_us_to_jis_shifted(record, KC_QUOT, KC_8);
    case CT_9: return replace_us_to_jis_shifted(record, KC_8, KC_9);
    case CT_0: return replace_us_to_jis_shifted(record, KC_9, KC_0);
    case CT_MINS: return replace_us_to_jis_shifted(record, KC_INT1, KC_MINS);
    case CT_EQL: return replace_us_to_jis_both_shifted(record, KC_SCLN, KC_MINS);

    case CT_LBRC: return replace_us_to_jis_shifted(record, KC_RBRC, KC_RBRC);
    case CT_RBRC: return replace_us_to_jis_shifted(record, KC_BSLS, KC_BSLS);
    case CT_BSLS: return replace_us_to_jis_shifted(record, KC_JYEN, KC_JYEN);

    case CT_SCLN: return replace_us_to_jis(record, KC_QUOT, KC_SCLN);
    case CT_QUOT: return replace_us_to_jis_both_shifted(record, KC_2, KC_7);
  }
  return true;
}