//
// Created by ghisi on 17.10.22.
//

#ifndef AVR_DISPLAY_H
#define AVR_DISPLAY_H


#include "../system/EventHandler.h"

/*
 * #define LCD_D4	D, 4
 * #define LCD_D5	D, 5
 * #define LCD_D6	D, 6
 * #define LCD_D7	D, 7
 * #define LCD_RS	B, 4
 * #define LCD_RW   B, 3
 * #define LCD_EN	B, 0
 *
 *
 */

class Display: public EventHandler {
public:
    Display();
    EventType eventType() override;
    bool handle(std::unique_ptr<Event> event) override;

private:
    void stats(std::unique_ptr<Event> event);
    void text(std::unique_ptr<Event> event);
    void memory(std::unique_ptr<Event> event);
    void keypad(std::unique_ptr<Event> event);
    void sensor(std::unique_ptr<Event> event);
};


#endif //AVR_DISPLAY_H
