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
    NEXTSEN,
    SELWORD,
    DOT_SLASH_UPDIR,

    BSPCIP,
    BSPCIW,
    BSPCEP,
    BSPCEW,

    BSPCEV_EVERY,
    BSPCU_YOU,
    BSPCA_AND,

    BSPCW_WITH,
    BSPCF_FOR,
    BSPCH_HERE,
    BSPCT_THE,
    BSPCM_MENT,
    BSPCG_ING,
    BSPCO_OUGH,
    BSPCOL_OULD,
    BSPCI_ION,
    BSPCIS_IONS,
    BSPCTA_THAT,
    BSPCQ_QUE,
    // I use the word "key" much more frequently than the common folk
    // and if you're reading this, you probably do too
    BSPCK_KEY,
    BSPCTS_THIS,
    BSPCDN_DONT,
    BSPCIT_IN_THE,
    HV_HAVE,
    QK_QMK,
    KB_KEYBOARD,
    WA_WHAT
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
        case BSPCEV_EVERY:
            if (spcdot_enabled && record->event.pressed) {
                send_string_with_mods("every");
            }
            break;
        case BSPCU_YOU:
            if (spcdot_enabled && record->event.pressed) {
                send_string_with_mods("you");
            }
            break;
        case BSPCA_AND:
            if (spcdot_enabled && record->event.pressed) {
                send_string_with_mods("and");
            }
            break;
        case BSPCW_WITH:
            if (spcdot_enabled && record->event.pressed) {
                send_string_with_mods("with");
            }
            break;
        case BSPCF_FOR:
            if (spcdot_enabled && record->event.pressed) {
                send_string_with_mods("for");
            }
            break;
        case BSPCH_HERE:
            if (spcdot_enabled && record->event.pressed) {
                send_string_with_mods("here");
            }
            break;
        case BSPCT_THE:
            if (spcdot_enabled && record->event.pressed) {
                send_string_with_mods("the");
            }
            break;
        case BSPCM_MENT:
            if (spcdot_enabled && record->event.pressed) {
                send_string_with_mods("ment");
            }
            break;
        case BSPCG_ING:
            if (spcdot_enabled && record->event.pressed) {
                send_string_with_mods("ing");
            }
            break;
        case BSPCO_OUGH:
            if (spcdot_enabled && record->event.pressed) {
                send_string_with_mods("ough");
            }
            break;
        case BSPCOL_OULD:
            if (spcdot_enabled && record->event.pressed) {
                send_string_with_mods("ould");
            }
            break;
        case BSPCI_ION:
            if (spcdot_enabled && record->event.pressed) {
                send_string_with_mods("ion");
            }
            break;
        case BSPCIS_IONS:
            if (spcdot_enabled && record->event.pressed) {
                send_string_with_mods("ions");
            }
            break;
        case BSPCTA_THAT:
            if (spcdot_enabled && record->event.pressed) {
                send_string_with_mods("that");
            }
            break;
        case BSPCQ_QUE:
            if (spcdot_enabled && record->event.pressed) {
                send_string_with_mods("que");
            }
            break;
        case BSPCK_KEY:
            if (spcdot_enabled && record->event.pressed) {
                send_string_with_mods("key");
            }
            break;
        case BSPCTS_THIS:
            if (spcdot_enabled && record->event.pressed) {
                send_string_with_mods("this");
            }
            break;
        case BSPCDN_DONT:
            if (spcdot_enabled && record->event.pressed) {
                send_string_with_mods("don't");
            }
            break;
        case BSPCIT_IN_THE:
            if (spcdot_enabled && record->event.pressed) {
                send_string_with_mods("in the");
            }
            break;
        case HV_HAVE:
            if (spcdot_enabled && record->event.pressed) {
                send_string_with_mods("have");
            }
            break;
        case QK_QMK:
            if (spcdot_enabled && record->event.pressed) {
                send_string_with_mods("qmk");
            }
            break;
        case KB_KEYBOARD:
            if (spcdot_enabled && record->event.pressed) {
                send_string_with_mods("keyboard");
            }
            break;
        case WA_WHAT:
            if (spcdot_enabled && record->event.pressed) {
                send_string_with_mods("what");
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

const uint16_t PROGMEM l_y_p[]         = {KC_L, KC_Y, KC_P, COMBO_END};
const uint16_t PROGMEM q_j[]           = {LT(U_BUTTON, KC_Q), ALGR_T(KC_J), COMBO_END};
const uint16_t PROGMEM q_j_v[]         = {LT(U_BUTTON, KC_Q), ALGR_T(KC_J), KC_V, COMBO_END};
const uint16_t PROGMEM j_v_d[]         = {ALGR_T(KC_J), KC_V, KC_D, COMBO_END};
const uint16_t PROGMEM j_v[]           = {ALGR_T(KC_J), KC_V, COMBO_END};
const uint16_t PROGMEM x_h[]           = {KC_X, KC_H, COMBO_END};
const uint16_t PROGMEM h_slsh[]        = {KC_H, KC_SLSH, COMBO_END};
const uint16_t PROGMEM h_comm[]        = {KC_H, ALGR_T(KC_COMM), COMBO_END};
const uint16_t PROGMEM h_dot[]         = {KC_H, LT(U_BUTTON, KC_DOT), COMBO_END};
const uint16_t PROGMEM slsh_comm[]     = {KC_SLSH, ALGR_T(KC_COMM), COMBO_END};
const uint16_t PROGMEM comm_dot[]      = {ALGR_T(KC_COMM), LT(U_BUTTON, KC_DOT), COMBO_END};
const uint16_t PROGMEM slsh_comm_dot[] = {KC_SLSH, ALGR_T(KC_COMM), LT(U_BUTTON, KC_DOT), COMBO_END};

// const uint16_t PROGMEM bspc_c[]  = {LT(U_NUM, KC_BSPC), LCTL_T(KC_C), COMBO_END};
const uint16_t PROGMEM bspc_ac[] = {LT(U_NUM, KC_BSPC), LALT_T(KC_I), LCTL_T(KC_C), COMBO_END};
const uint16_t PROGMEM bspc_ip[] = {LT(U_NAV, KC_SPC), LALT_T(KC_I), KC_P, COMBO_END};
const uint16_t PROGMEM bspc_iw[] = {LT(U_NAV, KC_SPC), LALT_T(KC_I), KC_W, COMBO_END};
const uint16_t PROGMEM bspc_ep[] = {LT(U_NAV, KC_SPC), LGUI_T(KC_E), KC_P, COMBO_END};
const uint16_t PROGMEM bspc_ew[] = {LT(U_NAV, KC_SPC), LGUI_T(KC_E), KC_W, COMBO_END};

const uint16_t PROGMEM bspc_every[]    = {LT(U_NUM, KC_BSPC), LGUI_T(KC_E), KC_V, COMBO_END};
const uint16_t PROGMEM bspc_you[]      = {LT(U_NUM, KC_BSPC), KC_U, COMBO_END};
const uint16_t PROGMEM bspc_and[]      = {LT(U_NAV, KC_SPC), KC_D, LCTL_T(KC_A), COMBO_END};
const uint16_t PROGMEM bspcw_with[]    = {LT(U_NUM, KC_BSPC), KC_H, KC_W, COMBO_END};
const uint16_t PROGMEM bspcf_for[]     = {LT(U_NUM, KC_BSPC), KC_F, COMBO_END};
const uint16_t PROGMEM bspch_here[]    = {LT(U_NUM, KC_BSPC), KC_H, COMBO_END};
const uint16_t PROGMEM bspct_the[]     = {LT(U_NUM, KC_BSPC), KC_H, LSFT_T(KC_T), COMBO_END};
const uint16_t PROGMEM bspcm_ment[]    = {LT(U_NUM, KC_BSPC), KC_M, COMBO_END};
const uint16_t PROGMEM bspcg_ing[]     = {LT(U_NUM, KC_BSPC), KC_H, KC_G, COMBO_END};
const uint16_t PROGMEM bspco_ough[]    = {LT(U_NUM, KC_BSPC), KC_O, COMBO_END};
const uint16_t PROGMEM bspcol_ould[]   = {LT(U_NUM, KC_BSPC), KC_O, KC_L, COMBO_END};
const uint16_t PROGMEM bspci_ion[]     = {LT(U_NAV, KC_SPC), KC_D, LALT_T(KC_I), COMBO_END};
const uint16_t PROGMEM bspcis_ions[]   = {LT(U_NAV, KC_SPC), KC_D, LALT_T(KC_I), LGUI_T(KC_S), COMBO_END};
const uint16_t PROGMEM bspcta_that[]   = {LT(U_NUM, KC_BSPC), LSFT_T(KC_T), LCTL_T(KC_A), COMBO_END};
const uint16_t PROGMEM bspcq_que[]     = {LT(U_NUM, KC_BSPC), LT(U_BUTTON, KC_Q), KC_H, COMBO_END};
const uint16_t PROGMEM bspci_key[]     = {LT(U_NUM, KC_BSPC), KC_H, KC_K, COMBO_END};
const uint16_t PROGMEM bspcts_this[]   = {LT(U_NUM, KC_BSPC), KC_H, LSFT_T(KC_T), LGUI_T(KC_S), COMBO_END};
const uint16_t PROGMEM bspcdn_dont[]   = {LT(U_NUM, KC_BSPC), KC_D, LSFT_T(KC_N), COMBO_END};
const uint16_t PROGMEM bspcit_in_the[] = {LT(U_NUM, KC_BSPC), LALT_T(KC_I), LSFT_T(KC_T), COMBO_END};
const uint16_t PROGMEM hv_have[]       = {KC_H, KC_V, COMBO_END};
const uint16_t PROGMEM qk_qmk[]        = {LT(U_BUTTON, KC_Q), KC_K, COMBO_END};
const uint16_t PROGMEM kb_keyboard[]   = {KC_K, KC_B, COMBO_END};
const uint16_t PROGMEM wa_what[]       = {KC_W, LSFT_T(KC_T), LCTL_T(KC_A), COMBO_END};

combo_t key_combos[] = {COMBO(l_y_p, SELWORD),
                        COMBO(q_j, QK_LEAD),
                        COMBO(q_j_v, AC_TOGG),
                        COMBO(j_v_d, ALT_TAB),
                        COMBO(j_v, KC_ESC),
                        COMBO(x_h, KC_GRV),
                        COMBO(h_slsh, KC_MINS),
                        COMBO(h_comm, KC_LT),
                        COMBO(h_dot, KC_GT),
                        COMBO(slsh_comm, KC_EQL),
                        COMBO(comm_dot, KC_SCLN),
                        COMBO(bspc_ac, KC_SCLN),
                        COMBO(slsh_comm_dot, DOT_SLASH_UPDIR),

                        COMBO(bspc_ip, BSPCIP),
                        COMBO(bspc_iw, BSPCIW),
                        COMBO(bspc_ep, BSPCEP),
                        COMBO(bspc_ew, BSPCEW),

                        COMBO(bspc_every, BSPCEV_EVERY),
                        COMBO(bspc_you, BSPCU_YOU),
                        COMBO(bspc_and, BSPCA_AND),
                        // COMBO(bspcw_with, BSPCW_WITH),
                        COMBO(bspcf_for, BSPCF_FOR),
                        COMBO(bspch_here, BSPCH_HERE),
                        COMBO(bspct_the, BSPCT_THE),
                        COMBO(bspcm_ment, BSPCM_MENT),
                        COMBO(bspcg_ing, BSPCG_ING),
                        COMBO(bspco_ough, BSPCO_OUGH),
                        COMBO(bspcol_ould, BSPCOL_OULD),
                        COMBO(bspci_ion, BSPCI_ION),
                        COMBO(bspcis_ions, BSPCIS_IONS),
                        COMBO(bspcta_that, BSPCTA_THAT),
                        COMBO(bspcq_que, BSPCQ_QUE),
                        COMBO(bspci_key, BSPCK_KEY),
                        COMBO(bspcts_this, BSPCTS_THIS),
                        COMBO(bspcdn_dont, BSPCDN_DONT),
                        COMBO(bspcit_in_the, BSPCIT_IN_THE),
                        COMBO(hv_have, HV_HAVE),
                        COMBO(qk_qmk, QK_QMK),
                        COMBO(kb_keyboard, KB_KEYBOARD),
                        COMBO(wa_what, WA_WHAT),

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
