#include "input_handler.h"

input_handler::update(class gamefield field)
{
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_a:
                        field.charachter_vector[1].left_key = 1;
                        break;
                    case SDLK_d:
                        field.charachter_vector[1].right_key = 1;
                        break;
                    case SDLK_w:
                        field.charachter_vector[1].up_key = 1;
                        break;
                    case SDLK_s:
                        field.charachter_vector[1].down_key = 1;
                        break;
                    case SDLK_y:
                        field.charachter_vector[1].turn_left_key = 1;
                        break;
                    case SDLK_u:
                        field.charachter_vector[1].turn_right_key = 1;
                        break;
                    case SDLK_i:
                        field.charachter_vector[1].shoot_key = true;
                        break;
                    case SDLK_o:
                        field.charachter_vector[1].ultimate;
                        break;
                }
        case SDL_KEYUP:
            switch(event.key.keysym.sym)
            {
                case SDLK_a:
                    field.charachter_vector[1].left_key = 0;
                    break;
                case SDLK_d:
                    field.charachter_vector[1].right_key = 0;
                    break;
                case SDLK_w:
                    field.charachter_vector[1].up_key = 0;
                    break;
                case SDLK_s:
                    field.charachter_vector[1].down_key = 0;
                    break;
                case SDLK_y:
                    field.charachter_vector[1].turn_left_key = 0;
                    break;
                case SDLK_u:
                    field.charachter_vector[1].turn_right_key = 0;
                    break;
                case SDLK_i:
                    field.charachter_vector[1].shoot_key = false;
                    break;
                /*case SDLK_o:
                    field.charachter_vector[1].stopultimate;
                    break;*/
            }


        }



    }


}
