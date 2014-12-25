//grundläggande funktionalitet implementerad av Markus Petersson
//Avancerad funktionalitet implementerad av Axel Reizenstein och Joakim Mörhed
#include "cover.h"
#include <iostream>
#include "gamefield.h"
void cover::update()
{

    //Explosionshastigheten ska sänkas utefter tiden
    explosion_movement_x = explosion_movement_x * 0.95;
    explosion_movement_y = explosion_movement_y * 0.95;

    //Behöver ha dessa för att sätta tillbaka position då nästkommande position är otillåten, dessa parametrar ändras nämligen i kollisionshanteringen
    double help_explosion_movement_x = explosion_movement_x;
    double help_explosion_movement_y = explosion_movement_y;
    double help_forced_x_movement = forced_x_movement;
    double help_forced_y_movement = forced_y_movement;

    if(abs(explosion_movement_x) < 0.1)
        explosion_movement_x = 0;
    if(abs(explosion_movement_y) < 0.1)
        explosion_movement_y = 0;
    xpos = xpos + forced_x_movement + explosion_movement_x;
    ypos = ypos + forced_y_movement + explosion_movement_y;
    if(main_gamefield->allowed_to_move_rectangle(get_corners(),this))
    {
        forced_x_movement = 0;
        forced_y_movement = 0;
        return;
    }
    xpos = xpos - help_forced_x_movement - help_explosion_movement_x;
    ypos = ypos - help_forced_y_movement - help_explosion_movement_y;
    forced_x_movement = 0;
    forced_y_movement = 0;
    return;
}

cover::cover(std::string name1, int x, int y, double angle, int health_input, double height_input, double width_input,class gamefield *init_gamefield):gameobject(name1, x, y, 0,angle,init_gamefield)
{
    health=health_input;
    width=width_input;
    height=height_input;
}
void cover::set_health(int new_health)
{
    health=new_health;
}

void cover::set_height(int new_height)
{
    height=new_height;
}

void cover::set_width(int new_width)
{
    width=new_width;
}

 vector<double> cover::get_corners()
{
     double pi = 3.1415;
     //hörnen utan hänsyn till vinkeln med mitten av rektangeln som origo
     double vector_corner1[2] = {-width/2,-height/2};
     double vector_corner2[2] = {width/2,-height/2};
     double vector_corner3[2] = {width/2,height/2};
     double vector_corner4[2] = {-width/2,height/2};

     //Skapar rotationsmatrisen
    double rotation_matrix[2][2] = {cos(direction*pi/180), -sin(direction*pi/180), sin(direction*pi/180), cos(direction*pi/180)};

    //Roterar vektorerna så att de nu pekar från mittpunkten av rektangeln till där hörnen faktiskt är (d.v.s med hänsyn på vinkeln)
    double corner_to_be_rotated_1x = vector_corner1[0];//Behöver använda ursprungliga x_koordinaten före och efter den roteras
    vector_corner1[0] = rotation_matrix[0][0]*corner_to_be_rotated_1x + rotation_matrix[0][1]*vector_corner1[1];
    vector_corner1[1] = rotation_matrix[1][0]*corner_to_be_rotated_1x + rotation_matrix[1][1]*vector_corner1[1];

    double corner_to_be_rotated_2x = vector_corner2[0];//Behöver använda ursprungliga x_koordinaten före och efter den roteras
    vector_corner2[0] = rotation_matrix[0][0]*corner_to_be_rotated_2x + rotation_matrix[0][1]*vector_corner2[1];
    vector_corner2[1] = rotation_matrix[1][0]*corner_to_be_rotated_2x + rotation_matrix[1][1]*vector_corner2[1];

    double corner_to_be_rotated_3x = vector_corner3[0];//Behöver använda ursprungliga x_koordinaten före och efter den roteras
    vector_corner3[0] = rotation_matrix[0][0]*corner_to_be_rotated_3x + rotation_matrix[0][1]*vector_corner3[1];
    vector_corner3[1] = rotation_matrix[1][0]*corner_to_be_rotated_3x + rotation_matrix[1][1]*vector_corner3[1];

    double corner_to_be_rotated_4x = vector_corner4[0];//Behöver använda ursprungliga x_koordinaten före och efter den roteras
    vector_corner4[0] = rotation_matrix[0][0]*corner_to_be_rotated_4x + rotation_matrix[0][1]*vector_corner4[1];
    vector_corner4[1] = rotation_matrix[1][0]*corner_to_be_rotated_4x + rotation_matrix[1][1]*vector_corner4[1];


     //Sätter fast vektorerna på mittpunkten av rektangeln så att vektorerna nu pekar från origo till hörnen
     //istället för att peka från mittpunkten till hörnen

     vector_corner1[0] = xpos + vector_corner1[0];
     vector_corner1[1] = ypos + vector_corner1[1];

     vector_corner2[0] = xpos + vector_corner2[0];
     vector_corner2[1] = ypos + vector_corner2[1];

     vector_corner3[0] = xpos + vector_corner3[0];
     vector_corner3[1] = ypos + vector_corner3[1];

     vector_corner4[0] = xpos + vector_corner4[0];
     vector_corner4[1] = ypos + vector_corner4[1];


    vector<double> ret;
    ret.push_back(vector_corner1[0]);
    ret.push_back(vector_corner1[1]);
    ret.push_back(vector_corner2[0]);
    ret.push_back(vector_corner2[1]);
    ret.push_back(vector_corner3[0]);
    ret.push_back(vector_corner3[1]);
    ret.push_back(vector_corner4[0]);
    ret.push_back(vector_corner4[1]);
    return ret;//vector<double>{vector_corner1[0],vector_corner1[1],vector_corner2[0],vector_corner2[1],vector_corner3[0],vector_corner3[1],vector_corner4[0],vector_corner4[1]};
 }
