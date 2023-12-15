// Copyright 2023 Manna Harbour
// https://github.com/manna-harbour/miryoku

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#pragma once

#define SENTENCE_CASE_TIMEOUT 1000
#define LEADER_NO_TIMEOUT
#define LEADER_PER_KEY_TIMING
#define LEADER_TIMEOUT 250
#define MAC_HOTKEYS

/* #undef COMBO_COUNT */
/* #define COMBO_COUNT 19 */

#define CAPS_LOCK_STATUS

#define RGBLIGHT_SLEEP

#define MIRYOKU_MAPPING( \
     K00, K01, K02, K03, K04,      K05, K06, K07, K08, K09, \
     K10, K11, K12, K13, K14,      K15, K16, K17, K18, K19, \
     K20, K21, K22, K23, K24,      K25, K26, K27, K28, K29, \
     N30, N31, K32, K33, K34,      K35, K36, K37, N38, N39 \
) \
LAYOUT_voyager( \
KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5,      KC_6, KC_7, KC_8, KC_9, KC_0, TD(QK_REBOOT), \
KC_TAB, K00, K01, K02, K03, K04,      K05, K06, K07, K08, K09, KC_BSPC, \
LSFT_T(KC_ESC), K10, K11, K12, K13, K14,      K15, K16, K17, K18, K19, RSFT_T(KC_ENT), \
KC_LEFT_GUI, K20, K21, K22, K23, K24,      K25, K26, K27, K28, K29, KC_RIGHT_CTRL, \
                    K33, K34,      K35, K36 \
)

#define MIRYOKU_LAYER_NUM \
KC_LBRC,           KC_7,              KC_8,              KC_9,              KC_RBRC,           U_NA,              TD(U_TD_U_BASE),   TD(U_TD_U_EXTRA),  TD(U_TD_U_TAP),    TD(U_TD_BOOT),     \
KC_ESC,            KC_4,              KC_5,              KC_6,              KC_EQL,            U_NA,              KC_LSFT,           KC_LGUI,           KC_LALT,           KC_LCTL,           \
KC_GRV,            KC_1,              KC_2,              KC_3,              KC_BSLS,           U_NA,              TD(U_TD_U_NUM),    TD(U_TD_U_NAV),    KC_ALGR,           U_NA,              \
U_NP,              U_NP,              KC_DOT,            KC_0,              KC_MINS,           U_NA,              U_NA,              U_NA,              U_NP,              U_NP

