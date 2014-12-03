#include "input_handler.h"

void input_handler::update(gamefield& field)
{
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_a:
                        field.character_vector[0].input_set_left(1);
                        break;
                    case SDLK_d:
                        field.character_vector[0].input_set_right(1);
                        break;
                    case SDLK_w:
                        field.get_character_vector()->at(0).input_set_up(1);
                        break;
                    case SDLK_s:
                        field.character_vector[0].input_set_down(1);
                        break;
                    case SDLK_y:
                        field.character_vector[0].input_set_turn_left(1);
                        break;
                    case SDLK_u:
                        field.character_vector[0].input_set_turn_right(1);
                        break;
                    case SDLK_i:
                        field.character_vector[0].input_set_shoot(true);
                        break;
                    case SDLK_o:
                        field.character_vector[0].ultimate();
                        break;
                }
                break;
            case SDL_KEYUP:
                switch(event.key.keysym.sym)
            {
                case SDLK_a:
                    field.character_vector[0].input_set_left(0);
                    break;
                case SDLK_d:
                    field.character_vector[0].input_set_right(0);
                    break;
                case SDLK_w:
                    field.character_vector[0].input_set_up(0);
                    break;
                case SDLK_s:
                    field.character_vector[0].input_set_down(0);
                    break;
                case SDLK_y:
                    field.character_vector[0].input_set_turn_left(0);
                    break;
                case SDLK_u:
                    field.character_vector[0].input_set_turn_right(0);
                    break;
                case SDLK_i:
                    field.character_vector[0].input_set_shoot(false);
                    break;
                    /*case SDLK_o:
                    field.character_vector[1].stopultimate;
                    break;
                    */
             }
            break;
        }



    }
return;
}
