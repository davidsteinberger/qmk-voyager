// Copyright 2019 Manna Harbour
// https://github.com/manna-harbour/miryoku

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#include QMK_KEYBOARD_H

#include "features/sentence_case.h"
#include "features/select_word.h"
#include "manna-harbour_miryoku.h"

bool     is_alt_tab_active = false; // ADD this near the beginning of keymap.c
uint16_t alt_tab_timer     = 0;     // we will be using them soon.
bool     spcdot_enabled    = false;

enum custom_keycodes { // Make sure have the awesome keycode ready
    ALT_TAB = SAFE_RANGE,
    SELWORD,
    DOT_SLASH_UPDIR,
    TRIPPLE_GRAVE,

    BSPCIP,
    BSPCIW,
    BSPCEP,
    BSPCEW,

    BSPCI,
};

void send_string_with_mods(char *str) {
    if (get_mods() & MOD_MASK_SHIFT) {
        clear_mods();
        SEND_STRING(str);
    } else {
        SEND_STRING(str);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_sentence_case(keycode, record)) {
        return false;
    }
    if (!process_select_word(keycode, record, SELWORD)) {
        return false;
    }

    if (spcdot_enabled && record->event.pressed) {
        static bool     add_shift  = false;
        static bool     spc_tapped = false;
        static uint16_t tap_timer  = 0;
        if (keycode == LT(U_NAV, KC_SPC)) {
            if (spc_tapped && !timer_expired(record->event.time, tap_timer)) {
                // The key was double tapped.
                clear_mods(); // If needed, clear the mods.
                register_code(KC_BSPC);
                register_code(KC_DOT);
                register_code(KC_SPC);
                add_shift = true;
                return false;
            }
            spc_tapped = true;
            tap_timer  = record->event.time + TAPPING_TERM;
        } else {
            if (add_shift) {
                spc_tapped = false;
                add_shift  = false;
                add_oneshot_mods(MOD_BIT(KC_LSFT));
            } else {
                // On an event with any other key, reset the double tap state.
                spc_tapped = false;
            }
        }
    }

    switch (keycode) { // This will do most of the grunt work with the keycodes.
        case ALT_TAB:
            if (record->event.pressed) {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(KC_LGUI);
                }
                alt_tab_timer = timer_read();
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            break;
        case DOT_SLASH_UPDIR:
            if (record->event.pressed) {
                SEND_STRING("../");
            }
            break;
        case BSPCIP:
            if (record->event.pressed) {
                send_string("David Steinberger");
            }
            break;
        case BSPCIW:
            if (record->event.pressed) {
                send_string("105042697");
            }
            break;
        case BSPCEP:
            if (record->event.pressed) {
                send_string("mail.steinberger@gmail.com");
            }
            break;
        case BSPCEW:
            if (record->event.pressed) {
                send_string("david.steinberger@innio.com");
            }
            break;
        case BSPCI:
            if (record->event.pressed) {
                SEND_STRING("I");
            }
            break;
        case TRIPPLE_GRAVE:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    clear_mods();
                    SEND_STRING("```");
                } else {
                    SEND_STRING("`");
                }
            }
            break;
    }
    return true;
}

void matrix_scan_user(void) { // The very important timer.
    sentence_case_task();
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 500) {
            unregister_code(KC_LGUI);
            is_alt_tab_active = false;
        }
    }
}

void leader_start_user(void) {
    // Do something when the leader key is pressed
}

void leader_end_user(void) {
    if (leader_sequence_two_keys(KC_D, KC_S)) {
        if (!spcdot_enabled) {
            spcdot_enabled = true;
        } else {
            spcdot_enabled = false;
        }
    }
}

// shift functions
const key_override_t   capsword_key_override = ko_make_basic(MOD_MASK_SHIFT, CW_TOGG, KC_CAPS);
const key_override_t   apos_under_override   = ko_make_with_layers(MOD_MASK_SHIFT, KC_QUOT, KC_UNDS, 1 << U_BASE);
const key_override_t   comma_qmark_override  = ko_make_with_layers(MOD_MASK_SHIFT, RSFT_T(KC_COMM), KC_QUES, 1 << U_BASE);
const key_override_t   dot_gt_override       = ko_make_with_layers(MOD_MASK_SHIFT, KC_DOT, KC_GT, 1 << U_BASE);
const key_override_t   minus_dqt_override    = ko_make_with_layers(MOD_MASK_SHIFT, ALGR_T(KC_MINS), KC_DQT, 1 << U_BASE);
const key_override_t   slash_lt_override     = ko_make_with_layers(MOD_MASK_SHIFT, LT(U_BUTTON, KC_SLSH), KC_LT, 1 << U_BASE);
const key_override_t **key_overrides         = (const key_override_t *[]){&capsword_key_override, &apos_under_override, &comma_qmark_override, &dot_gt_override, &minus_dqt_override, &slash_lt_override, NULL};

// thumb combos
#if defined(MIRYOKU_KLUDGE_THUMBCOMBOS)
const uint16_t PROGMEM thumbcombos_base_right[] = {LT(U_SYM, KC_ENT), LT(U_NUM, KC_BSPC), COMBO_END};
const uint16_t PROGMEM thumbcombos_base_left[]  = {LT(U_NAV, KC_SPC), LT(U_MOUSE, KC_TAB), COMBO_END};
const uint16_t PROGMEM thumbcombos_nav[]        = {KC_ENT, KC_BSPC, COMBO_END};
const uint16_t PROGMEM thumbcombos_mouse[]      = {KC_BTN2, KC_BTN1, COMBO_END};
const uint16_t PROGMEM thumbcombos_media[]      = {KC_MSTP, KC_MPLY, COMBO_END};
const uint16_t PROGMEM thumbcombos_num[]        = {KC_0, KC_MINS, COMBO_END};
#    if defined(MIRYOKU_LAYERS_FLIP)
const uint16_t PROGMEM thumbcombos_sym[] = {KC_UNDS, KC_LPRN, COMBO_END};
#    else
const uint16_t PROGMEM thumbcombos_sym[] = {KC_RPRN, KC_UNDS, COMBO_END};
#    endif
const uint16_t PROGMEM thumbcombos_fun[] = {KC_SPC, KC_TAB, COMBO_END};

const uint16_t PROGMEM l_d_w[]      = {KC_L, KC_D, KC_W, COMBO_END};
const uint16_t PROGMEM r_t_s[]      = {LALT_T(KC_R), LGUI_T(KC_T), LSFT_T(KC_S), COMBO_END};
const uint16_t PROGMEM q_x[]        = {LT(U_BUTTON, KC_Q), ALGR_T(KC_X), COMBO_END};
const uint16_t PROGMEM q_x_m[]      = {LT(U_BUTTON, KC_Q), ALGR_T(KC_X), KC_M, COMBO_END};
const uint16_t PROGMEM x_m_c[]      = {ALGR_T(KC_X), KC_M, KC_C, COMBO_END};
const uint16_t PROGMEM x_m[]        = {ALGR_T(KC_X), KC_M, COMBO_END};
const uint16_t PROGMEM k_p[]        = {KC_K, KC_P, COMBO_END};
const uint16_t PROGMEM p_dot[]      = {KC_P, KC_DOT, COMBO_END};
const uint16_t PROGMEM p_mins[]     = {KC_P, ALGR_T(KC_MINS), COMBO_END};
const uint16_t PROGMEM p_slsh[]     = {KC_P, LT(U_BUTTON, KC_SLSH), COMBO_END};
const uint16_t PROGMEM dot_mins[]   = {KC_DOT, ALGR_T(KC_MINS), COMBO_END};
const uint16_t PROGMEM p_dot_mins[] = {KC_P, KC_DOT, ALGR_T(KC_MINS), COMBO_END};

const uint16_t PROGMEM bspc_ip[] = {LT(U_NAV, KC_SPC), LCTL_T(KC_I), KC_D, COMBO_END};
const uint16_t PROGMEM bspc_iw[] = {LT(U_NAV, KC_SPC), LCTL_T(KC_I), KC_W, COMBO_END};
const uint16_t PROGMEM bspc_ep[] = {LT(U_NAV, KC_SPC), LALT_T(KC_E), KC_D, COMBO_END};
const uint16_t PROGMEM bspc_ew[] = {LT(U_NAV, KC_SPC), LALT_T(KC_E), KC_W, COMBO_END};

const uint16_t PROGMEM mc_comma[]   = {KC_M, KC_C, COMBO_END};
const uint16_t PROGMEM pdot_comma[] = {KC_P, KC_DOT, COMBO_END};
const uint16_t PROGMEM bspci[]      = {LT(U_NUM, KC_BSPC), LCTL_T(KC_I), COMBO_END};

combo_t key_combos[] = {COMBO(l_d_w, SELWORD),
                        COMBO(q_x, QK_LEAD),
                        COMBO(q_x_m, AC_TOGG),
                        COMBO(x_m_c, ALT_TAB),
                        COMBO(x_m, KC_ESC),
                        COMBO(r_t_s, KC_ENT),
                        COMBO(k_p, TRIPPLE_GRAVE),
                        COMBO(p_dot, KC_MINS),
                        COMBO(p_mins, KC_GT),
                        COMBO(p_slsh, KC_LT),
                        COMBO(dot_mins, KC_EQL),
                        COMBO(p_dot_mins, DOT_SLASH_UPDIR),
                        COMBO(bspc_ip, BSPCIP),
                        COMBO(bspc_iw, BSPCIW),
                        COMBO(bspc_ep, BSPCEP),
                        COMBO(bspc_ew, BSPCEW),
                        COMBO(mc_comma, RSFT_T(KC_COMM)),
                        COMBO(pdot_comma, RSFT_T(KC_COMM)),
                        COMBO(bspci, BSPCI),

                        COMBO(thumbcombos_base_right, LT(U_FUN, KC_DEL)),
                        COMBO(thumbcombos_base_left, LT(U_MEDIA, KC_ESC)),
                        COMBO(thumbcombos_nav, KC_DEL),
                        COMBO(thumbcombos_mouse, KC_BTN3),
                        COMBO(thumbcombos_media, KC_MUTE),
                        COMBO(thumbcombos_num, KC_DOT),
#    if defined(MIRYOKU_LAYERS_FLIP)
                        COMBO(thumbcombos_sym, KC_RPRN),
#    else
                        COMBO(thumbcombos_sym, KC_LPRN),
#    endif
                        COMBO(thumbcombos_fun, KC_APP)};
#endif
