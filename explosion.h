#ifndef EXPLOSION_H
#define EXPLOSION_H

class explosion
{
public:
    explosion(double init_scale, double init_x, double init_y, class gamefield* init_gamefield);
    explosion(const explosion&) = default;
    explosion(explosion&&) = default;
    explosion& operator=(const explosion&) = default;
    explosion& operator=(explosion&&) = default;
    ~explosion() = default;
    int get_timer(){return explosion_timer;}
    double get_xpos(){return xpos;}
    double get_ypos(){return ypos;}
    double get_scale(){return scale;}
    void update();


private:
    class gamefield* main_gamefield;
    double scale;
    double xpos;
    double ypos;
    int explosion_timer = 10;
};

#endif // EXPLOSION_H
