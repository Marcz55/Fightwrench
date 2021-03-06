#include "character.h"
#include "temporary_power_up.h"
#include <iostream>
using namespace std;

character::character(string character_name, string init_body, int x_pos, int y_pos, int speed, double angle,
                     string init_projectile,
                     int init_firing_cooldown, int init_max_health,
                     int init_max_ammo, int init_reload_time, double init_width, double init_height,
                     string port_name, class gamefield* init_gamefield, int init_damage): gameobject(character_name, x_pos,y_pos,speed,angle,init_gamefield)

{
    projectile_type = init_projectile;
    firing_cooldown = init_firing_cooldown;
    current_health = init_max_health;
    max_health = init_max_health;
    max_ammo = init_max_ammo;
    current_ammo = init_max_ammo;
    reload_time = init_reload_time;
    width = init_width;
    height = init_height;
    portrait_name=port_name;
    damage=init_damage;
    body_name = init_body;
}

void character::update()
{
    allowed_x_movement = 0;
    allowed_y_movement = 0;
    if (ultimate_timer > 0)
    {
        ultimate_timer -= 1;
    }
    if (ultimate_active_timer > 0)
    {
        ultimate_active_timer -= 1;
    }
    if (ultimate_active_timer == 0 && name == "Marsus")
    {
        firing_cooldown = firing_cooldown/0.75;
        ultimate_active_timer -= 1;
    }
    if (reload_timer > 0) {
        if (reload_timer == 1) {
            reload_timer = 0;
            current_ammo = max_ammo;
        } else {
            reload_timer -= 1;
        }
    }

    move(x_movement,y_movement,turn_right_key - turn_left_key);
    if (firing_timer > 0)
    {
        firing_timer -= 1;
    }
    if (shoot_key && firing_timer <= 0 && current_ammo > 0)
    {
        fire_weapon();
        current_ammo -= 1;
        if (current_ammo <= 0) {
            reload_timer = reload_time;
            main_gamefield->play_sound("Reload");

        }
    }

    for(auto it=active_power_ups.begin();it!=active_power_ups.end();it++)
    {
        it->update();
        cout << it->get_duration() << endl;
        if(it->get_duration()<=0)
        {
            cout << "Togs bort!!" << endl;
            max_health=max_health/it->get_delta_health();
            damage=damage/it->get_delta_damage();
            speed = speed/it->get_delta_move_speed();
            firing_cooldown = firing_cooldown/it->get_delta_fire_speed();
            reload_time = reload_time/it->get_delta_fire_speed();
            if(current_health>max_health)
            {
            current_health=max_health;
            }

            active_power_ups.erase(it--);
            cout << active_power_ups.size() << endl;
        }
    }



}

void character::update_move_vector()
{
    double temp_x = right_key - left_key;
    double temp_y = down_key - up_key;
    if (temp_x != 0 || temp_y != 0) {
        x_movement = temp_x / sqrt(temp_x * temp_x + temp_y * temp_y);
        y_movement = temp_y / sqrt(temp_x * temp_x + temp_y * temp_y);
    } else {
        y_movement = 0;
        x_movement = 0;
    };
    if (temp_x != 0 || temp_y != 0)
    {
        if (temp_x == 0)
        {
            if (temp_y == 1)
            {
                movement_direction = 180;
            }
            else
            {
                movement_direction = 0;
            }
        }
        else if (temp_y == 0)
        {
            if (temp_x == 1)
            {
                movement_direction = 90;
            } else {
                movement_direction = 270;
            }
        }
        else
        {
            if (temp_x > 0 && temp_y > 0)
            {
                movement_direction = 135;
            }
            if (temp_x < 0 && temp_y > 0)
            {
                movement_direction = 225;
            }
            if (temp_x < 0 && temp_y < 0)
            {
                movement_direction = 315;
            }
            if (temp_x > 0 && temp_y < 0)
            {
                movement_direction = 45;
            }
        }
    }

}
void character::input_set_up(const int up)
{
    up_key = up;
}

void character::input_set_down(const int down)
{
    down_key = down;
}

void character::input_set_left(const int left)
{
    left_key = left;
}

void character::input_set_right(const int right)
{
    right_key = right;
}

void character::input_set_turn_left(const int turn_left)
{
    turn_left_key = turn_left;
}

void character::input_set_turn_right(const int turn_right)
{
    turn_right_key = turn_right;
}

void character::input_set_shoot(const bool shoot)
{
    shoot_key = shoot;
}

void character::fire_weapon()
{
    main_gamefield->add_projectile(projectile_type,xpos + 30*cos(direction*0.0175),ypos + 30*sin(direction*0.0175),allowed_x_movement,allowed_y_movement,direction, damage,this);
    firing_timer = firing_cooldown;
}

void character::ultimate()
{
    if(ultimate_timer == 0)
    {

        ultimate_timer = ultimate_cooldown_time;
        ultimate_active_timer = ultimate_active_time;

        if(name == "Marsus")
        {
        firing_cooldown = firing_cooldown*0.75;
        //spela upp ljud här
        }
        if (name == "Nassehuvud")
        {
            main_gamefield->add_projectile("guided rocket",xpos + 30*cos(direction*0.0175),ypos + 30*sin(direction*0.0175),0,0,direction, damage,this);
            controlling = true;
        }
        if (name == "Axel")
        {
            double ultimate_jump_x = 10*cos((direction + 90)*0.0175);
            double ultimate_jump_y = 10*sin((direction + 90)*0.0175);
            double jump_xpos = xpos;
            double jump_ypos = ypos;
            for (int ulti_iterator = 1; ulti_iterator <= 50; ulti_iterator ++)
            {
                xpos = jump_xpos + ulti_iterator*ultimate_jump_x;
                ypos = jump_ypos + ulti_iterator*ultimate_jump_y;
                if(!main_gamefield->allowed_to_move_rectangle(get_corners(),this))
                {
                    xpos = jump_xpos + (ulti_iterator - 1)*ultimate_jump_x;
                    ypos = jump_ypos + (ulti_iterator - 1)*ultimate_jump_y;
                    return;
                }
            }
        }
    }
}

vector<double> character::get_corners()
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


   vector<double> ret; //Lägger de framtagna hörnpunkterna i vektorn som sedan kan skickas vidare till andra funktioner som behöver dem
   ret.push_back(vector_corner1[0]);
   ret.push_back(vector_corner1[1]);
   ret.push_back(vector_corner2[0]);
   ret.push_back(vector_corner2[1]);
   ret.push_back(vector_corner3[0]);
   ret.push_back(vector_corner3[1]);
   ret.push_back(vector_corner4[0]);
   ret.push_back(vector_corner4[1]);
   return ret;
}

void character::move(double x_length, double y_length,int turn_direction)
{
    //Börjar med att skala ner explosionshastigheterna
    explosion_movement_x = explosion_movement_x * 0.95;
    explosion_movement_y = explosion_movement_y * 0.95;

    //När explosionshastigheten är tillräckligt låg så tas den bort helt och hållet
    if(abs(explosion_movement_x) < 0.1)
        explosion_movement_x = 0;
    if(abs(explosion_movement_y) < 0.1)
        explosion_movement_y = 0;

    //konstanter som behövs för att sätta tillbaka positionen då en rörelse inte var tillåten
    double help_explosion_movement_x = explosion_movement_x;
    double help_explosion_movement_y = explosion_movement_y;
    double help_forced_x_movement = forced_x_movement;
    double help_forced_y_movement = forced_y_movement;

    if(x_length != 0 or y_length !=0 or turn_direction != 0 or forced_x_movement != 0 or forced_y_movement != 0 or explosion_movement_x != 0 or explosion_movement_y != 0)
    {
        if(controlling)
        {
            main_gamefield->send_command(turn_direction);
        }
        else
        {
            direction += turn_direction;
        }




        if(direction>360)
        {
            direction = direction - 360;
        }
        if(direction<0)
        {
            direction = direction + 360;
        }

        xpos += speed*x_length + forced_x_movement + explosion_movement_x;
        ypos += speed*y_length + forced_y_movement + explosion_movement_y;
        //kollar om koordinaten är okej att flytta sig till, om ja så är vi klara om nej så sätter vi tillbaka värdena till de gamla koordinaterna
        if(main_gamefield -> allowed_to_move_rectangle(get_corners(),this))
        {

            allowed_x_movement = speed*x_length + help_forced_x_movement + help_explosion_movement_x;
            allowed_y_movement = speed*y_length + help_forced_y_movement + help_explosion_movement_y;
            forced_x_movement = 0;
            forced_y_movement = 0;
            return;
        }

        if(!controlling)
        {
            direction -= turn_direction;
        }



        if(main_gamefield -> allowed_to_move_rectangle(get_corners(),this))
        {

            allowed_x_movement = speed*x_length + help_forced_x_movement + help_explosion_movement_x;
            allowed_y_movement = speed*y_length + help_forced_y_movement + help_explosion_movement_y;
            forced_x_movement = 0;
            forced_y_movement = 0;
            return;
        }
        xpos -= speed*x_length + help_forced_x_movement + help_explosion_movement_x;
        if(main_gamefield->allowed_to_move_rectangle(get_corners(),this))
        {

            allowed_x_movement = 0;
            allowed_y_movement = speed*y_length + help_forced_y_movement  + help_explosion_movement_y;
            forced_x_movement = 0;
            forced_y_movement = 0;
            return;
        }
        xpos += speed*x_length + help_forced_x_movement + help_explosion_movement_x;
        ypos -= speed*y_length + help_forced_y_movement + help_explosion_movement_y;
        if(main_gamefield -> allowed_to_move_rectangle(get_corners(),this))
        {

            allowed_x_movement = speed*x_length + help_forced_x_movement + explosion_movement_x;
            allowed_y_movement = 0;
            forced_x_movement = 0;
            forced_y_movement = 0;
            return;
        }
        xpos -= speed*x_length + help_forced_x_movement + help_explosion_movement_x;

     }
    forced_x_movement = 0;
    forced_y_movement = 0;
     return;
}
void character::pick_up_power_up(const power_up &po_up)
{

    if(po_up.get_type())
    {

        if(po_up.get_delta_health()+current_health > max_health)
        {
            current_health=max_health;
        }
        else
        {
           current_health=current_health+po_up.get_delta_health();
        }
    }
    else
    {
           current_health=current_health*po_up.get_delta_health();
           max_health=max_health*po_up.get_delta_health();
           damage=damage*po_up.get_delta_damage();
           speed = speed*po_up.get_delta_move_speed();
           firing_cooldown = firing_cooldown*po_up.get_delta_fire_speed();
           reload_time = reload_time*po_up.get_delta_fire_speed();
           active_power_ups.push_back(temporary_power_up(po_up.get_name(), po_up.get_xpos(), po_up.get_ypos(), po_up.get_direction(), 3, main_gamefield, po_up.get_delta_damage(), po_up.get_delta_health(), po_up.get_delta_fire_speed(), po_up.get_delta_move_speed(), po_up.get_duration()));
           std::cout<<"PLOCKAT UPP!";


    }
}



