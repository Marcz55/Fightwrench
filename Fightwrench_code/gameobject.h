#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class gameobject
{
public:
    gameobject();
   virtual update() = 0;

private:
    double xpos;
    double ypos;
    double direction;
    double speed;



};

#endif // GAMEOBJECT_H
