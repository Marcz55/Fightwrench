#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H
#include <SDL2/SDL.h>
#include <vector>
#include <gamefield.h>
using namespace std;
class input_handler
{
private:
    SDL_Event event;
    vector<int> movement_vector_char1;
    vector<int> movement_vector_char2;

public:
    input_handler() = default;
    ~input_handler() = default;
    void update(class gamefield&); //Tar hand om allt som ligger i event_queue
};

#endif // INPUT_HANDLER_H
