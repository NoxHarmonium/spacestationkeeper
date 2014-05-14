//
//  CinderEventBinders.h
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 8/05/2014.
//
//

#ifndef SpaceStationKeeper_CinderEventBinders_h
#define SpaceStationKeeper_CinderEventBinders_h

#include "ClassBinder.h"

using namespace ci::app;
using namespace luabind;

template <> struct ClassBinder<MouseEvent> {
  static void Bind(const char *name, lua_State *L) {
    luabind::module(L)[luabind::class_<MouseEvent>(name)
                           .def("getX", &MouseEvent::getX)
                           .def("getY", &MouseEvent::getY)
                           .def("getPos", &MouseEvent::getPos)
                           .def("isLeft", &MouseEvent::isLeft)
                           .def("isRight", &MouseEvent::isRight)
                           .def("isMiddle", &MouseEvent::isMiddle)
                           .def("isLeftDown", &MouseEvent::isLeftDown)
                           .def("isRightDown", &MouseEvent::isRightDown)
                           .def("isMiddleDown", &MouseEvent::isMiddleDown)
                           .def("isShiftDown", &MouseEvent::isShiftDown)
                           .def("isAltDown", &MouseEvent::isAltDown)
                           .def("isControlDown", &MouseEvent::isControlDown)
                           .def("isMetaDown", &MouseEvent::isMetaDown)
                           .def("isAccelDown", &MouseEvent::isAccelDown)];

    luabind::module(
        L)[luabind::class_<KeyEvent>(name)
               .def("getChar", &KeyEvent::getChar)
               .def("getCharUtf32", &KeyEvent::getCharUtf32)
               .def("getCode", &KeyEvent::getCode)
               .def("isShiftDown", &KeyEvent::isShiftDown)
               .def("isAltDown", &KeyEvent::isAltDown)
               .def("isControlDown", &KeyEvent::isControlDown)
               .def("isMetaDown", &KeyEvent::isMetaDown)
               .def("isAccelDown", &KeyEvent::isAccelDown)
               .enum_("constants")[
                 value("KEY_UNKNOWN", 0),
                 value("KEY_FIRST", 0),
                 value("KEY_BACKSPACE", 8),
                 value("KEY_TAB", 9),
                 value("KEY_CLEAR", 12),
                 value("KEY_RETURN", 13),
                 value("KEY_PAUSE", 19),
                 value("KEY_ESCAPE", 27),
                 value("KEY_SPACE", 32),
                 value("KEY_EXCLAIM", 33),
                 value("KEY_QUOTEDBL", 34),
                 value("KEY_HASH", 35),
                 value("KEY_DOLLAR", 36),
                 value("KEY_AMPERSAND", 38),
                 value("KEY_QUOTE", 39),
                 value("KEY_LEFTPAREN", 40),
                 value("KEY_RIGHTPAREN", 41),
                 value("KEY_ASTERISK", 42),
                 value("KEY_PLUS", 43),
                 value("KEY_COMMA", 44),
                 value("KEY_MINUS", 45),
                 value("KEY_PERIOD", 46),
                 value("KEY_SLASH", 47),
                 value("KEY_0", 48),
                 value("KEY_1", 49),
                 value("KEY_2", 50),
                 value("KEY_3", 51),
                 value("KEY_4", 52),
                 value("KEY_5", 53),
                 value("KEY_6", 54),
                 value("KEY_7", 55),
                 value("KEY_8", 56),
                 value("KEY_9", 57),
                 value("KEY_COLON", 58),
                 value("KEY_SEMICOLON", 59),
                 value("KEY_LESS", 60),
                 value("KEY_EQUALS", 61),
                 value("KEY_GREATER", 62),
                 value("KEY_QUESTION", 63),
                 value("KEY_AT", 64),
                 value("KEY_LEFTBRACKET", 91),
                 value("KEY_BACKSLASH", 92),
                 value("KEY_RIGHTBRACKET", 93),
                 value("KEY_CARET", 94),
                 value("KEY_UNDERSCORE", 95),
                 value("KEY_BACKQUOTE", 96),
                 value("KEY_a", 97),
                 value("KEY_b", 98),
                 value("KEY_c", 99),
                 value("KEY_d", 100),
                 value("KEY_e", 101),
                 value("KEY_f", 102),
                 value("KEY_g", 103),
                 value("KEY_h", 104),
                 value("KEY_i", 105),
                 value("KEY_j", 106),
                 value("KEY_k", 107),
                 value("KEY_l", 108),
                 value("KEY_m", 109),
                 value("KEY_n", 110),
                 value("KEY_o", 111),
                 value("KEY_p", 112),
                 value("KEY_q", 113),
                 value("KEY_r", 114),
                 value("KEY_s", 115),
                 value("KEY_t", 116),
                 value("KEY_u", 117),
                 value("KEY_v", 118),
                 value("KEY_w", 119),
                 value("KEY_x", 120),
                 value("KEY_y", 121),
                 value("KEY_z", 122),
                 value("KEY_DELETE", 127),
                 value("KEY_KP0", 256),
                 value("KEY_KP1", 257),
                 value("KEY_KP2", 258),
                 value("KEY_KP3", 259),
                 value("KEY_KP4", 260),
                 value("KEY_KP5", 261),
                 value("KEY_KP6", 262),
                 value("KEY_KP7", 263),
                 value("KEY_KP8", 264),
                 value("KEY_KP9", 265),
                 value("KEY_KP_PERIOD", 266),
                 value("KEY_KP_DIVIDE", 267),
                 value("KEY_KP_MULTIPLY", 268),
                 value("KEY_KP_MINUS", 269),
                 value("KEY_KP_PLUS", 270),
                 value("KEY_KP_ENTER", 271),
                 value("KEY_KP_EQUALS", 272),
                 value("KEY_UP", 273),
                 value("KEY_DOWN", 274),
                 value("KEY_RIGHT", 275),
                 value("KEY_LEFT", 276),
                 value("KEY_INSERT", 277),
                 value("KEY_HOME", 278),
                 value("KEY_END", 279),
                 value("KEY_PAGEUP", 280),
                 value("KEY_PAGEDOWN", 281),
                 value("KEY_F1", 282),
                 value("KEY_F2", 283),
                 value("KEY_F3", 284),
                 value("KEY_F4", 285),
                 value("KEY_F5", 286),
                 value("KEY_F6", 287),
                 value("KEY_F7", 288),
                 value("KEY_F8", 289),
                 value("KEY_F9", 290),
                 value("KEY_F10", 291),
                 value("KEY_F11", 292),
                 value("KEY_F12", 293),
                 value("KEY_F13", 294),
                 value("KEY_F14", 295),
                 value("KEY_F15", 296),
                 value("KEY_NUMLOCK", 300),
                 value("KEY_CAPSLOCK", 301),
                 value("KEY_SCROLLOCK", 302),
                 value("KEY_RSHIFT", 303),
                 value("KEY_LSHIFT", 304),
                 value("KEY_RCTRL", 305),
                 value("KEY_LCTRL", 306),
                 value("KEY_RALT", 307),
                 value("KEY_LALT", 308),
                 value("KEY_RMETA", 309),
                 value("KEY_LMETA", 310),
                 value("KEY_LSUPER", 311),  /* Left "Windows" key */
                 value("KEY_RSUPER", 312),  /* Right "Windows" key */
                 value("KEY_MODE", 313),    /* "Alt Gr" key */
                 value("KEY_COMPOSE", 314), /* Multi-key compose key */
                 value("KEY_HELP", 315),
                 value("KEY_PRINT", 316),
                 value("KEY_SYSREQ", 317),
                 value("KEY_BREAK", 318),
                 value("KEY_MENU", 319),
                 value("KEY_POWER", 320), /* Power Macintosh power key */
                 value("KEY_EURO", 321),  /* Some european keyboards */
                 value("KEY_UNDO", 322)   /* Atari keyboard has Undo */
               ]];
  }
};

#endif
