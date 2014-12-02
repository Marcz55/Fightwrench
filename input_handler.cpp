#include "input_handler.h"

void input_handler::update(class gamefield& field)
{
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_a:
                        field.character_vector[0].left_key = 1;
                        break;
                    case SDLK_d:
                        field.character_vector[0].right_key = 1;
                        break;
                    case SDLK_w:
                        field.character_vector[0].up_key = 1;
                        break;
                    case SDLK_s:
                        field.character_vector[0].down_key = 1;
                        break;
                    case SDLK_y:
                        field.character_vector[0].turn_left_key = 1;
                        break;
                    case SDLK_u:
                        field.character_vector[0].turn_right_key = 1;
                        break;
                    case SDLK_i:
                        field.character_vector[0].shoot_key = true;
                        break;
                    case SDLK_o:
                        field.character_vector[0].ultimate();
                        break;
                }
            case SDL_KEYUP:
                switch(event.key.keysym.sym)
            {
                case SDLK_a:
                    field.character_vector[0].left_key = 0;
                    break;
                case SDLK_d:
                    field.character_vector[0].right_key = 0;
                    break;
                case SDLK_w:
                    field.character_vector[0].up_key = 0;
                    break;
                case SDLK_s:
                    field.character_vector[0].down_key = 0;
                    break;
                case SDLK_y:
                    field.character_vector[0].turn_left_key = 0;
                    break;
                case SDLK_u:
                    field.character_vector[0].turn_right_key = 0;
                    break;
                case SDLK_i:
                    field.character_vector[0].shoot_key = false;
                    break;
                /*case SDLK_o:
                    field.character_vector[1].stopultimate;
                    break;
                    */
            }


        }



    }
return;
}
