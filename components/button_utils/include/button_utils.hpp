#pragma once

#include "button.h"

button_t* button_get_button(void);
void reinit_button();
void button_register_cb(button_event_cb_t cb);
void button_unregister_all(void);
