#ifndef INPUT_EVENT_H
#define INPUT_EVENT_H

#include "input_type.h"

class InputEvent
{
public:

  InputEvent( InputType current, InputType previous );

  bool left_up() const;

  bool right_up() const;

  bool down_up() const;

  bool enter_up() const;

  bool romeo_up() const;

  bool escape() const;

private:  

  InputType current_frame_input;
  InputType previous_frame_input;

};

#endif
