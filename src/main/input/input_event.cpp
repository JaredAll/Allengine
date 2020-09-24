#include "input_event.h"

InputEvent::InputEvent( InputType current, InputType previous )
  : current_frame_input( current ), previous_frame_input( previous )
{}

bool InputEvent::left_up() const
{
  return previous_frame_input == InputType::left &&
    current_frame_input == InputType::none;
}

bool InputEvent::right_up() const
{
  return previous_frame_input == InputType::right &&
    current_frame_input == InputType::none;
}

bool InputEvent::down_up() const
{
  return previous_frame_input == InputType::down &&
    current_frame_input == InputType::none;
}

bool InputEvent::enter_up() const
{
  return previous_frame_input == InputType::enter &&
    current_frame_input == InputType::none;
}

bool InputEvent::romeo_up() const
{
  return previous_frame_input == InputType::romeo &&
    current_frame_input == InputType::none;
}

bool InputEvent::escape() const
{
  return current_frame_input == InputType::escape;
}
