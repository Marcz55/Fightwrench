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
    bool running = true;

public:
    input_handler() = default;
    ~input_handler() = default;
    input_handler(const input_handler&) = delete;
    input_handler(input_handler&&) = delete;
    input_handler& operator=(const input_handler&) = delete;
    input_handler& operator=(input_handler&&) = delete;
    void update(gamefield&); //Tar hand om allt som ligger i event_queue
    bool Get_running();
};

#endif // INPUT_HANDLER_H
