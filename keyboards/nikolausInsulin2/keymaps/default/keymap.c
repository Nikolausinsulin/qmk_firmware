/* Copyright 2020 foostan
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
#include "keymap_german.h"

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

// Tap dance enums
enum {
    tapdanceSpace, 
    tapdanceEndHome
};

td_state_t cur_dance(qk_tap_dance_state_t *state);

/*
// For the x tap dance. Put it here so it can be used in any keymap
void x_finished(qk_tap_dance_state_t *state, void *user_data);
void x_reset(qk_tap_dance_state_t *state, void *user_data);
*/


enum custom_keycodes {
    BACKTICK = SAFE_RANGE,
    CIRCUM
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case BACKTICK:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING(SS_DOWN(X_LSFT) SS_TAP(X_EQL) SS_TAP(X_EQL) SS_UP(X_LSFT) SS_TAP(X_BSPACE));
            //SEND_STRING(SS_TAP(X_EQL));
        } else {
            // when keycode QMKBEST is released
        }
        break;
    case CIRCUM:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING(SS_TAP(X_GRAVE) SS_TAP(X_GRAVE) SS_TAP(X_BSPACE));
            //SEND_STRING(SS_TAP(X_EQL));
        } else {
            // when keycode QMKBEST is released
        }
        break;
    /*
    case LAYERCHANGE:
        if (record->event.pressed) {
            layer_on(4);
        } else {
            // when keycode QMKBEST is released
        }
        break;
    */
    }
    return true;
};

// all leader key commands go here 
LEADER_EXTERNS();
void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    SEQ_ONE_KEY(KC_F) {
      // search via ctrl f
      SEND_STRING(SS_LCTL("f"));
    }
    
    SEQ_TWO_KEYS(KC_S, KC_S) {
      // make windows screenshot
      //SEND_STRING(SS_LWIN(X_PSCREEN)); 
      // TODO: make this work
      SEND_STRING("screenshot pls");
    }
    SEQ_TWO_KEYS(KC_SPACE, KC_SPACE) {
      // send shift enter
      SEND_STRING(SS_LSFT(SS_TAP(X_ENTER)));
    }
    // BROWSER COMMANDS
    SEQ_ONE_KEY(KC_U) {
      // search via ctrl f
      SEND_STRING(SS_LALT(SS_TAP(X_LEFT)));
    }
    SEQ_ONE_KEY(KC_E) {
      // search via ctrl f
      SEND_STRING(SS_LALT(SS_TAP(X_RIGHT)));
    }
    SEQ_TWO_KEYS(KC_T, KC_N) {
      // tab new
      SEND_STRING(SS_LCTL("t"));
    }
    SEQ_TWO_KEYS(KC_T, KC_C) {
      // tab close
      SEND_STRING(SS_LCTL("w"));
    }
    SEQ_TWO_KEYS(KC_T, KC_L) {
      // tab left
      SEND_STRING(SS_LCTL(SS_TAP(X_PGUP)));
    }
    SEQ_TWO_KEYS(KC_T, KC_R) {
      // tab right
      SEND_STRING(SS_LCTL(SS_TAP(X_PGDOWN)));
    }
    SEQ_FOUR_KEYS(KC_B, KC_O, KC_O, KC_K) {
      // bookmark 
      SEND_STRING(SS_LCTL("d"));
    }
    
    // LAYER SWITCHING
    SEQ_FOUR_KEYS(KC_A, KC_N, KC_K, KC_I) {
      // anki layer
      layer_on(4);
    }
    SEQ_THREE_KEYS(KC_N, KC_A, KC_V) {
      // nav layer
      layer_on(5);
    }
    SEQ_THREE_KEYS(KC_G, KC_T, KC_A) { //todo: change sequence
      // undefined layer
      layer_on(6);
    }


  }
} 


// when adding combos change combocount in config.h
/*
enum combos {
  //backspaceCombo,
  //deleteCombo, 
  // 
};

const uint16_t PROGMEM lc_combo[] = {KC_L, KC_C, COMBO_END};
const uint16_t PROGMEM cw_combo[] = {KC_C, KC_W, COMBO_END};
const uint16_t PROGMEM layer_combo[] = {KC_C, KC_W, COMBO_END};


combo_t key_combos[COMBO_COUNT] = {
  [backspaceCombo] = COMBO(lc_combo, KC_BSPACE),
  [deleteCombo] = COMBO(cw_combo, KC_DELETE)
};
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT(
      KC_ESC,           KC_X,               KC_V,       KC_L,           KC_C,    KC_W,                                      KC_K,           KC_H,   KC_G,       KC_F,       KC_Q,   RESET, 
      KC_TAB,           KC_U,               KC_I,       KC_A,           KC_E,    KC_O,                                      KC_S,           KC_N,   KC_R,       KC_T,       KC_D,   KC_RSHIFT, 
      KC_LCTRL,         KC_LWIN,            KC_LALT,    DE_Y,           KC_P,    DE_Z,                                      KC_B,           KC_M,   KC_COMMA,   KC_DOT,     KC_J,   _______, 
                                                                     OSL(2),    TD(tapdanceSpace),   KC_DOWN,          KC_LEAD, KC_BSPACE, OSL(1)
  ), 
// special signs layer
[1] = LAYOUT(
    _______,            DE_AT,              DE_UNDS,           DE_LBRC,            DE_RBRC,             CIRCUM,                                   DE_EXLM,        DE_LESS,      DE_MORE,     DE_EQL,   DE_AMPR,            _______,
    _______,            DE_BSLS,            DE_SLSH,           DE_LCBR,            DE_RCBR,             DE_ASTR,                                   DE_QST,         DE_LPRN,      DE_RPRN,     DE_MINS,  DE_COLN,            _______,
    _______,            DE_HASH,            DE_DLR,            DE_PIPE,            DE_TILD,             BACKTICK,                                   DE_PLUS,        DE_PERC,      DE_DQOT,     DE_QUOT,  DE_SCLN,            _______,
                                                                            _______,    _______,    _______,            _______,    _______,   _______
), 
// numpad and arrows layer
[2] = LAYOUT(
    _______,            _______,            _______,    _______,        _______, _______,                                   _______,        KC_7,     KC_8,   KC_9,  _______, _______,
    _______,            KC_LEFT,            KC_DOWN,    KC_UP,          KC_RIGHT, _______,                                   _______,        KC_4,     KC_5,   KC_6,  _______, _______,
    _______,            _______,            _______,    _______,        _______, _______,                                   _______,        KC_1,     KC_2,   KC_3,  _______, _______,
                                                                _______,    _______,    _______,         _______,    KC_0,   KC_DOT
), 
// umlaut layer currently not in use
[3] = LAYOUT(
    _______,            _______,            _______,    _______,        _______, _______,                                   _______,        _______, _______,   _______, _______, _______,
    _______,            DE_UE,              _______,    DE_AE,          _______, DE_OE,                                     DE_SS,          _______, _______,   _______, _______, _______,
    _______,            _______,            _______,    _______,        _______, _______,                                   _______,        _______, _______,   _______, _______, _______,
                                                                            _______,    _______,    _______,    _______,    _______,   _______
), 
// anki layer
[4] = LAYOUT(
    TO(0),              _______,            _______,    _______,        _______, _______,                                   _______,        _______, _______,   _______, _______, _______,
    _______,            KC_1,               KC_2,       KC_3,           KC_4,    KC_5,                                      _______,        _______, _______,   _______, _______, _______,
    _______,            _______,            _______,    _______,        _______, _______,                                   _______,        _______, _______,   _______, _______, _______,
                                                                            _______,    _______,    _______,    _______,    _______,   _______
), 
// nav layer 
[5] = LAYOUT(
    TO(0),              _______,            _______,    _______,        _______, _______,                                   _______,        _______, _______,   _______, _______, _______,
    _______,            _______,            _______,    _______,        _______, _______,                                   _______,        _______, _______,   _______, _______, _______,
    _______,            _______,            _______,    _______,        _______, _______,                                   _______,        _______, _______,   _______, _______, _______,
                                                                            _______,    _______,    _______,    _______,    _______,   _______
), 
// undefined layer 
[6] = LAYOUT(
    TO(0),              _______,            _______,    _______,        _______, _______,                                   _______,        _______, _______,   _______, _______, _______,
    _______,            _______,            _______,    _______,        _______, _______,                                   _______,        _______, _______,   _______, _______, _______,
    _______,            _______,            _______,    _______,        _______, _______,                                   _______,        _______, _______,   _______, _______, _______,
                                                                            _______,    _______,    _______,    _______,    _______,   _______
)
  };


/* 
[1] = LAYOUT(
  _______,    _______,    _______,    _______,    _______,    _______,    _______,                                    _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,                                    _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,                                    _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,                                    _______,    _______,    _______,    _______,    _______,    _______,    _______,
                                                              _______,    _______,    _______,            _______,    _______,    _______
)
*/



/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'TD_DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
// maybe better implementation at example 5 here: 
// https://docs.qmk.fm/#/feature_tap_dance?id=example-1-send-on-single-tap-on-double-tap
// find implementation that does not go up to 3 taps. 

td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    } else return TD_UNKNOWN;
}


static td_tap_t spacetap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

static td_tap_t endhometap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
 


void space_finished(qk_tap_dance_state_t *state, void *user_data) {
    spacetap_state.state = cur_dance(state);
    switch (spacetap_state.state) {
        case TD_SINGLE_TAP: tap_code(KC_SPACE); break;
        case TD_SINGLE_HOLD: tap_code(KC_ENTER); break;
        case TD_DOUBLE_TAP: tap_code(KC_SPACE); tap_code(KC_SPACE); break;
        case TD_DOUBLE_HOLD: register_code(KC_LSFT); tap_code(KC_ENTER); unregister_code(KC_LSFT); break;
        default: ;
    }
}

void space_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (spacetap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_SPACE); break;
        case TD_SINGLE_HOLD: unregister_code(KC_ENTER); break;
        case TD_DOUBLE_TAP: unregister_code(KC_SPACE); break;
        case TD_DOUBLE_HOLD: unregister_code(KC_SPACE); unregister_code(KC_ENTER);
        default: ;
    }
    spacetap_state.state = TD_NONE;
}


void endhome_finished(qk_tap_dance_state_t *state, void *user_data) {
    endhometap_state.state = cur_dance(state);
    switch (endhometap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_END); break;
        case TD_SINGLE_HOLD: register_code(KC_HOME); break;
        case TD_DOUBLE_TAP: register_code(KC_END); register_code(KC_END); break;
        case TD_DOUBLE_HOLD: register_code(KC_END); break;
        default: ;
    }
}

void endhome_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (endhometap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_END); break;
        case TD_SINGLE_HOLD: unregister_code(KC_HOME); break;
        case TD_DOUBLE_TAP: unregister_code(KC_END); unregister_code(KC_END); break;
        case TD_DOUBLE_HOLD: unregister_code(KC_END);
        default: ;
    }
    endhometap_state.state = TD_NONE;
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [tapdanceSpace] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, space_finished, space_reset),
    [tapdanceEndHome] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, endhome_finished, endhome_reset) //maybe here should be a , at the end
};

