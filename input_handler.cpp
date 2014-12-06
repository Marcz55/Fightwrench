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
                //Fösta karaktären
                    case SDLK_a:
                        field.get_character_vector()->at(0).input_set_left(1);
                        break;
                    case SDLK_d:
                        field.get_character_vector()->at(0).input_set_right(1);
                        break;
                    case SDLK_w:
                        field.get_character_vector()->at(0).input_set_up(1);
                        break;
                    case SDLK_s:
                        field.get_character_vector()->at(0).input_set_down(1);
                        break;
                    case SDLK_y:
                        field.get_character_vector()->at(0).input_set_turn_left(1);
                        break;
                    case SDLK_u:
                        field.get_character_vector()->at(0).input_set_turn_right(1);
                        break;
                    case SDLK_i:
                        field.get_character_vector()->at(0).input_set_shoot(true);
                        break;
                    case SDLK_o:
                        field.get_character_vector()->at(0).ultimate();
                        break;
                        //Andra karaktären
                case SDLK_LEFT:
                    field.get_character_vector()->at(1).input_set_left(1);
                    break;
                case SDLK_RIGHT:
                    field.get_character_vector()->at(1).input_set_right(1);
                    break;
                case SDLK_UP:
                    field.get_character_vector()->at(1).input_set_up(1);
                    break;
                case SDLK_DOWN:
                    field.get_character_vector()->at(1).input_set_down(1);
                    break;
                case SDLK_KP_7:
                    field.get_character_vector()->at(1).input_set_turn_left(1);
                    break;
                case SDLK_KP_8:
                    field.get_character_vector()->at(1).input_set_turn_right(1);
                    break;
                case SDLK_KP_1:
                    field.get_character_vector()->at(1).input_set_shoot(true);
                    break;
                case SDLK_KP_9:
                    field.get_character_vector()->at(1).ultimate();
                    break;
                }
                break;
            case SDL_KEYUP:
                switch(event.key.keysym.sym)
            {
                //Första karaktären
                case SDLK_a:
                    field.get_character_vector()->at(0).input_set_left(0);
                    break;
                case SDLK_d:
                    field.get_character_vector()->at(0).input_set_right(0);
                    break;
                case SDLK_w:
                    field.get_character_vector()->at(0).input_set_up(0);
                    break;
                case SDLK_s:
                    field.get_character_vector()->at(0).input_set_down(0);
                    break;
                case SDLK_y:
                    field.get_character_vector()->at(0).input_set_turn_left(0);
                    break;
                case SDLK_u:
                    field.get_character_vector()->at(0).input_set_turn_right(0);
                    break;
                case SDLK_i:
                    field.get_character_vector()->at(0).input_set_shoot(false);
                    break;
                    //Andra karaktären
                case SDLK_LEFT:
                    field.get_character_vector()->at(1).input_set_left(0);
                    break;
                case SDLK_RIGHT:
                    field.get_character_vector()->at(1).input_set_right(0);
                    break;
                case SDLK_UP:
                    field.get_character_vector()->at(1).input_set_up(0);
                    break;
                case SDLK_DOWN:
                    field.get_character_vector()->at(1).input_set_down(0);
                    break;
                case SDLK_KP_7:
                    field.get_character_vector()->at(1).input_set_turn_left(0);
                    break;
                case SDLK_KP_8:
                    field.get_character_vector()->at(1).input_set_turn_right(0);
                    break;
                case SDLK_KP_1:
                    field.get_character_vector()->at(1).input_set_shoot(false);
                    break;
                    /*case SDLK_o:
                    field.get_character_vector()->at(1).stopultimate;
                    break;
                    */
             }
            break;
        }



    }
return;
}
