//Joakim Mörhed har skrivit Collision_handler.
//Collision_handler tar hand om kollisioner samt deras effekter.
#include "collision_handler.h"
#include <iostream>


collision_handler::collision_handler(gamefield* gamefield_object_pointer)
{
    gamefield_pointer = gamefield_object_pointer;
    window_height = gamefield_object_pointer->get_window_height();
    window_width = gamefield_object_pointer->get_window_width();
    return;
}
/*Allowed_to_move_rectangle(vector<double>,character*)
 * Beräknar huruvida en rektangels nya position är okej att flytta till.
 * Om rektangeln inte fick flytta sig till den nya position så påverkas det objekt som var ivägen på olika sätt,
 * t.ex. så överförs två krafter, en forced_movement och en explosion_movement som påverkar objektets rörelse på olika sätt
 *
 */
bool collision_handler::allowed_to_move_rectangle(vector<double> corner_vector_to_check,character* character_pointer)/*(double x1,double y1,double x2,double y2,double x3,double y3,double x4,double y4)*/
{//corner_vector_to_check innehåller koordinaterna för rektangelns hörn som skall kollas i ordningen, x1,y1,x2,y2,x3,....
    //Kollar först så att rektangeln inte försöker smita utanför banan
    if(corner_vector_to_check.at(0) < 0 or corner_vector_to_check.at(1)  < 0 or corner_vector_to_check.at(2) < 0 or corner_vector_to_check.at(3) < 0 or corner_vector_to_check.at(4) < 0 or corner_vector_to_check.at(5) < 0 or corner_vector_to_check.at(6) < 0 or corner_vector_to_check.at(7) < 0 or
            corner_vector_to_check.at(0) > window_width or corner_vector_to_check.at(1) > window_height or corner_vector_to_check.at(2) > window_width or corner_vector_to_check.at(3) > window_height or
            corner_vector_to_check.at(4) > window_width or corner_vector_to_check.at(5) > window_height or corner_vector_to_check.at(6) > window_width or corner_vector_to_check.at(7) > window_height)
        return false;


    vector<cover>* cover_vector = gamefield_pointer->get_cover_vector();
    //Skapar den nya basen för rektangeln, (x2-x1,y2-y1) och (x3-x2,y3-y2)
    double base_vector_u[2] = {corner_vector_to_check.at(2) - corner_vector_to_check.at(0), corner_vector_to_check.at(3) - corner_vector_to_check.at(1)}; //u uttryckt i basen x,y
    double base_vector_v[2] = {corner_vector_to_check.at(4) - corner_vector_to_check.at(2), corner_vector_to_check.at(5) - corner_vector_to_check.at(3)}; //v uttryckt i basen x,y
    //Vi vill normera basvektorerna
    double normalize_u = sqrt(pow(base_vector_u[0],2) + pow(base_vector_u[1],2));
    double normalize_v = sqrt(pow(base_vector_v[0],2) + pow(base_vector_v[1],2));

    base_vector_u[0] = base_vector_u[0] / normalize_u;
    base_vector_u[1] = base_vector_u[1] / normalize_u;
    base_vector_v[0] = base_vector_v[0] / normalize_v;
    base_vector_v[1] = base_vector_v[1] / normalize_v;
    //Skapar en "basbytarmatris" för att lätt kunna byta bas från x,y till u,v.
    //Notera att eftersom baserna är normerade så är Ae->f = (Af->e)^-1 = (Af->e)^t
    double base_change_matrix[2][2] = {base_vector_u[0],base_vector_u[1],base_vector_v[0],base_vector_v[1]};

    //Tar ut koordinaterna för rektangelns hörn i den nya koordinaten, notera att jag bara behöver
    //ta ut två hörn, de "motsatta" eftersom vi gör det i en nya bas där rektangeln nu är vinkelrät
    //relativt koordinataxlarna.
    double corner_1[2];
    corner_1[0] = base_change_matrix[0][0]*corner_vector_to_check.at(0) + base_change_matrix[0][1]*corner_vector_to_check.at(1);
    corner_1[1] = base_change_matrix[1][0]*corner_vector_to_check.at(0) + base_change_matrix[1][1]*corner_vector_to_check.at(1);

    double corner_3[2];
    corner_3[0] = base_change_matrix[0][0]*corner_vector_to_check.at(4) + base_change_matrix[0][1]*corner_vector_to_check.at(5);
    corner_3[1] = base_change_matrix[1][0]*corner_vector_to_check.at(4) + base_change_matrix[1][1]*corner_vector_to_check.at(5);

    //Den faktor som explosionsrörelsen för karaktären skalas med varje gång denne kolliderar
    double explosion_contact_movement_loss = 2;
    double explosion_transfer_loss = 1.5; //Den faktor som explosionsrörelsen förlorar när den överför till ett nytt objekt
    //Nu har vi initierat klart och behöver alltså kolla igenom om den nya koordinaten är okej att flytta till.
    //Vi börjar med att gå igenom cover listan (som just nu antas bara bestå av rektangelobjekt.
    for(std::vector<cover>::iterator it = cover_vector->begin(); it != cover_vector->end(); ++it)
    {
        vector<double>corner_vector = it->get_corners(); //Tänker att get_corner returnerar
        //x1,y1,x2,y2.. för de olika hörnen i en vektor i den ordningen.
        //Skriver rektangelns hörn i de nya koordinaterna u,v.

        //Tänker att jag behöver utföra någon kontroll om kontroll av kollision är överhuvudtaget nödvändig:
        //Detta görs genom att jämföra avstånden mellan de båda rektanglarnas mittpunkter mot längden av dess diagonaler summerade.

        //Dessa två vektorer går genom diagonalen på bägge rektanglarna
        double help_vector_rec_1[2] = {corner_vector_to_check[2] - corner_vector_to_check[6], corner_vector_to_check[3] - corner_vector_to_check[7]};
        double help_vector_rec_2[2] = {corner_vector[2] - corner_vector[6], corner_vector[3] - corner_vector[7]};

        //Längden av diagonalen i varje rektangel
        double length_dia_1 = sqrt(pow(help_vector_rec_1[0],2) + pow(help_vector_rec_1[1],2));
        double length_dia_2 = sqrt(pow(help_vector_rec_2[0],2) + pow(help_vector_rec_2[1],2));

        //Längden mellan rektanglarnas mittpunkter
        double length_between_midpoints = sqrt(pow(corner_vector_to_check[6]+help_vector_rec_1[0]/2 - (corner_vector[6] + help_vector_rec_2[0]/2),2) + pow(corner_vector_to_check[7]+help_vector_rec_1[1]/2 - (corner_vector[7] + help_vector_rec_2[1]/2),2));
        //Om längden mellan rektanglarnas mittpunkter är mindre än summan av dess diagonaler så kan det vara bra att utföra kollisionskontroll.
        if(length_dia_1/2 + length_dia_2/2 + 1 >= length_between_midpoints)
        {
            double corner_to_check1[2];
            double corner_to_check2[2];
            double corner_to_check3[2];
            double corner_to_check4[2];
            corner_to_check1[0] = base_change_matrix[0][0]*corner_vector[0] + base_change_matrix[0][1]*corner_vector[1];
            corner_to_check1[1] = base_change_matrix[1][0]*corner_vector[0] + base_change_matrix[1][1]*corner_vector[1];

            corner_to_check2[0] = base_change_matrix[0][0]*corner_vector[2] + base_change_matrix[0][1]*corner_vector[3];
            corner_to_check2[1] = base_change_matrix[1][0]*corner_vector[2] + base_change_matrix[1][1]*corner_vector[3];

            corner_to_check3[0] = base_change_matrix[0][0]*corner_vector[4] + base_change_matrix[0][1]*corner_vector[5];
            corner_to_check3[1] = base_change_matrix[1][0]*corner_vector[4] + base_change_matrix[1][1]*corner_vector[5];

            corner_to_check4[0] = base_change_matrix[0][0]*corner_vector[6] + base_change_matrix[0][1]*corner_vector[7];
            corner_to_check4[1] = base_change_matrix[1][0]*corner_vector[6] + base_change_matrix[1][1]*corner_vector[7];

            //Kollar om någon av rektangelns hörn ligger inuti rektangeln som vi kollar kollision för.
            //Eftersom vi har gjort ett basbyte till rektangelns, som vi kollar kollision för, sidor så
            //befinner sig varje hörn på enbart en axel, således mäter vi avståndet ifrån 2 hörn på en axel till rektangelns
            //koordinat på denna axel och jämför detta avstånd med avståndet mellan de båda hörnen.
            if(abs(corner_to_check1[0]-corner_1[0]) + abs(corner_to_check1[0]-corner_3[0]) <= abs(corner_1[0]-corner_3[0]) and
                    abs(corner_to_check1[1]-corner_1[1]) + abs(corner_to_check1[1]-corner_3[1]) <= abs(corner_1[1]-corner_3[1]))
            {
                //Om det inte var tillåtet att röra sig så ska objektet som stöttes i få rörelsen istället samt överförs hela explosions hastigheten till nästa objekt
                it->set_forced_x_movement(it->get_forced_x_movement() + character_pointer->get_x_movement() + character_pointer->get_forced_x_movement());
                it->set_forced_y_movement(it->get_forced_y_movement() + character_pointer->get_y_movement() + character_pointer->get_forced_y_movement());
                it->set_explosion_movement_x(it->get_explosion_movement_x() + character_pointer->get_explosion_movement_x() / explosion_transfer_loss);
                it->set_explosion_movement_y(it->get_explosion_movement_y() + character_pointer->get_explosion_movement_y() / explosion_transfer_loss);
                character_pointer->set_explosion_movement_x(character_pointer->get_explosion_movement_x() / explosion_contact_movement_loss);
                character_pointer->set_explosion_movement_y(character_pointer->get_explosion_movement_y() / explosion_contact_movement_loss);
                return false;
            }
            {
                if(abs(corner_to_check2[0]-corner_1[0]) + abs(corner_to_check2[0]-corner_3[0]) <= abs(corner_1[0]-corner_3[0]) and
                        abs(corner_to_check2[1]-corner_1[1]) + abs(corner_to_check2[1]-corner_3[1]) <= abs(corner_1[1]-corner_3[1]))
                {
                    //Om det inte var tillåtet att röra sig så ska objektet som stöttes i få rörelsen istället
                    it->set_forced_x_movement(it->get_forced_x_movement() + character_pointer->get_x_movement() + character_pointer->get_forced_x_movement());
                    it->set_forced_y_movement(it->get_forced_y_movement() + character_pointer->get_y_movement() + character_pointer->get_forced_y_movement());
                    it->set_explosion_movement_x(it->get_explosion_movement_x() + character_pointer->get_explosion_movement_x() / explosion_transfer_loss);
                    it->set_explosion_movement_y(it->get_explosion_movement_y() + character_pointer->get_explosion_movement_y() / explosion_transfer_loss);
                    character_pointer->set_explosion_movement_x(character_pointer->get_explosion_movement_x() / explosion_contact_movement_loss);
                    character_pointer->set_explosion_movement_y(character_pointer->get_explosion_movement_y() / explosion_contact_movement_loss);
                    return false;
                }
                {
                    if(abs(corner_to_check3[0]-corner_1[0]) + abs(corner_to_check3[0]-corner_3[0]) <= abs(corner_1[0]-corner_3[0]) and
                            abs(corner_to_check3[1]-corner_1[1]) + abs(corner_to_check3[1]-corner_3[1]) <= abs(corner_1[1]-corner_3[1]))
                    {
                        //Om det inte var tillåtet att röra sig så ska objektet som stöttes i få rörelsen istället
                        it->set_forced_x_movement(it->get_forced_x_movement() + character_pointer->get_x_movement() + character_pointer->get_forced_x_movement());
                        it->set_forced_y_movement(it->get_forced_y_movement() + character_pointer->get_y_movement() + character_pointer->get_forced_y_movement());
                        it->set_explosion_movement_x(it->get_explosion_movement_x() + character_pointer->get_explosion_movement_x() / explosion_transfer_loss);
                        it->set_explosion_movement_y(it->get_explosion_movement_y() + character_pointer->get_explosion_movement_y() / explosion_transfer_loss);
                        character_pointer->set_explosion_movement_x(character_pointer->get_explosion_movement_x() / explosion_contact_movement_loss);
                        character_pointer->set_explosion_movement_y(character_pointer->get_explosion_movement_y() / explosion_contact_movement_loss);
                        return false;
                    }
                    {
                        if(abs(corner_to_check4[0]-corner_1[0]) + abs(corner_to_check4[0]-corner_3[0]) <= abs(corner_1[0]-corner_3[0]) and
                                abs(corner_to_check4[1]-corner_1[1]) + abs(corner_to_check4[1]-corner_3[1]) <= abs(corner_1[1]-corner_3[1]))
                        {
                            //Om det inte var tillåtet att röra sig så ska objektet som stöttes i få rörelsen istället
                            it->set_forced_x_movement(it->get_forced_x_movement() + character_pointer->get_x_movement() + character_pointer->get_forced_x_movement());
                            it->set_forced_y_movement(it->get_forced_y_movement() + character_pointer->get_y_movement() + character_pointer->get_forced_y_movement());
                            it->set_explosion_movement_x(it->get_explosion_movement_x() + character_pointer->get_explosion_movement_x() / explosion_transfer_loss);
                            it->set_explosion_movement_y(it->get_explosion_movement_y() + character_pointer->get_explosion_movement_y() / explosion_transfer_loss);
                            character_pointer->set_explosion_movement_x(character_pointer->get_explosion_movement_x() / explosion_contact_movement_loss);
                            character_pointer->set_explosion_movement_y(character_pointer->get_explosion_movement_y() / explosion_contact_movement_loss);
                            return false;
                        }
                    }
                }
            }

            //Har vi tagit oss hit har vi inte fått någon kollission, vad som krävs nu är att vi gör ytterliggare ett basbyte, men nu till rektangeln i cover listan
            double base_vector_u2[2] = {corner_vector[2] - corner_vector[0], corner_vector[3] - corner_vector[1]}; //u2 uttryckt i basen x,y
            double base_vector_v2[2] = {corner_vector[4] - corner_vector[2], corner_vector[5] - corner_vector[3]}; //v2 uttryckt i basen x,y
            //Vi vill normera basvektorerna
            double normalize_u2 = sqrt(pow(base_vector_u2[0],2) + pow(base_vector_u2[1],2));
            double normalize_v2 = sqrt(pow(base_vector_v2[0],2) + pow(base_vector_v2[1],2));

            base_vector_u2[0] = base_vector_u2[0] / normalize_u2;
            base_vector_u2[1] = base_vector_u2[1] / normalize_u2;
            base_vector_v2[0] = base_vector_v2[0] / normalize_v2;
            base_vector_v2[1] = base_vector_v2[1] / normalize_v2;
            //Skapar en "basbytarmatris" för att lätt kunna byta bas från x,y till u2,v2.
            //Notera att eftersom baserna är normerade så är Ae->f = (Af->e)^-1 = (Af->e)^t
            double base_change_matrix2[2][2] = {base_vector_u2[0],base_vector_u2[1],base_vector_v2[0],base_vector_v2[1]};

            //Tar ut koordinaterna för rektangelns hörn i den nya koordinaten, notera att jag bara behöver
            //ta ut två hörn, de "motsatta" eftersom vi gör det i en nya bas där rektangeln nu är vinkelrät
            //relativt koordinataxlarna.
            double corner2_1[2];
            corner2_1[0] = base_change_matrix2[0][0]*corner_vector[0] + base_change_matrix2[0][1]*corner_vector[1];
            corner2_1[1] = base_change_matrix2[1][0]*corner_vector[0] + base_change_matrix2[1][1]*corner_vector[1];

            double corner2_3[2];
            corner2_3[0] = base_change_matrix2[0][0]*corner_vector[4] + base_change_matrix2[0][1]*corner_vector[5];
            corner2_3[1] = base_change_matrix2[1][0]*corner_vector[4] + base_change_matrix2[1][1]*corner_vector[5];

            //Nu behöver vi kolla om rektangeln i cover "skär" in i den rektangeln vi kollar kollission för

            //skapar ny arrays för att hålla hörnen i den nya basen
            double corner1_in_new_base[2];
            double corner2_in_new_base[2];
            double corner3_in_new_base[2];
            double corner4_in_new_base[2];
            corner1_in_new_base[0] = base_change_matrix2[0][0]*corner_vector_to_check.at(0) + base_change_matrix2[0][1]*corner_vector_to_check.at(1);
            corner1_in_new_base[1] = base_change_matrix2[1][0]*corner_vector_to_check.at(0) + base_change_matrix2[1][1]*corner_vector_to_check.at(1);

            corner2_in_new_base[0] = base_change_matrix2[0][0]*corner_vector_to_check.at(2) + base_change_matrix2[0][1]*corner_vector_to_check.at(3);
            corner2_in_new_base[1] = base_change_matrix2[1][0]*corner_vector_to_check.at(2) + base_change_matrix2[1][1]*corner_vector_to_check.at(3);

            corner3_in_new_base[0] = base_change_matrix2[0][0]*corner_vector_to_check.at(4) + base_change_matrix2[0][1]*corner_vector_to_check.at(5);
            corner3_in_new_base[1] = base_change_matrix2[1][0]*corner_vector_to_check.at(4) + base_change_matrix2[1][1]*corner_vector_to_check.at(5);

            corner4_in_new_base[0] = base_change_matrix2[0][0]*corner_vector_to_check.at(6) + base_change_matrix2[0][1]*corner_vector_to_check.at(7);
            corner4_in_new_base[1] = base_change_matrix2[1][0]*corner_vector_to_check.at(6) + base_change_matrix2[1][1]*corner_vector_to_check.at(7);



            //Kollar om någon av rektangelns (vars kollission vi undersöker) hörn ligger inuti rektangeln från cover-listan
            if(abs(corner1_in_new_base[0]-corner2_1[0]) + abs(corner1_in_new_base[0]-corner2_3[0]) <= abs(corner2_1[0]-corner2_3[0]) and
                    abs(corner1_in_new_base[1]-corner2_1[1]) + abs(corner1_in_new_base[1]-corner2_3[1]) <= abs(corner2_1[1]-corner2_3[1]))
            {
                //Om det inte var tillåtet att röra sig så ska objektet som stöttes i få rörelsen istället
                it->set_forced_x_movement(it->get_forced_x_movement() + character_pointer->get_x_movement() + character_pointer->get_forced_x_movement());
                it->set_forced_y_movement(it->get_forced_y_movement() + character_pointer->get_y_movement() + character_pointer->get_forced_y_movement());
                it->set_explosion_movement_x(it->get_explosion_movement_x() + character_pointer->get_explosion_movement_x() / explosion_transfer_loss);
                it->set_explosion_movement_y(it->get_explosion_movement_y() + character_pointer->get_explosion_movement_y() / explosion_transfer_loss);
                character_pointer->set_explosion_movement_x(character_pointer->get_explosion_movement_x() / explosion_contact_movement_loss);
                character_pointer->set_explosion_movement_y(character_pointer->get_explosion_movement_y() / explosion_contact_movement_loss);
                return false;
            }
            {
                if(abs(corner2_in_new_base[0]-corner2_1[0]) + abs(corner2_in_new_base[0]-corner2_3[0]) <= abs(corner2_1[0]-corner2_3[0]) and
                        abs(corner2_in_new_base[1]-corner2_1[1]) + abs(corner2_in_new_base[1]-corner2_3[1]) <= abs(corner2_1[1]-corner2_3[1]))
                {
                    //Om det inte var tillåtet att röra sig så ska objektet som stöttes i få rörelsen istället
                    it->set_forced_x_movement(it->get_forced_x_movement() + character_pointer->get_x_movement() + character_pointer->get_forced_x_movement());
                    it->set_forced_y_movement(it->get_forced_y_movement() + character_pointer->get_y_movement() + character_pointer->get_forced_y_movement());
                    it->set_explosion_movement_x(it->get_explosion_movement_x() + character_pointer->get_explosion_movement_x() / explosion_transfer_loss);
                    it->set_explosion_movement_y(it->get_explosion_movement_y() + character_pointer->get_explosion_movement_y() / explosion_transfer_loss);
                    character_pointer->set_explosion_movement_x(character_pointer->get_explosion_movement_x() / explosion_contact_movement_loss);
                    character_pointer->set_explosion_movement_y(character_pointer->get_explosion_movement_y() / explosion_contact_movement_loss);
                    return false;
                }
                {
                    if(abs(corner3_in_new_base[0]-corner2_1[0]) + abs(corner3_in_new_base[0]-corner2_3[0]) <= abs(corner2_1[0]-corner2_3[0]) and
                            abs(corner3_in_new_base[1]-corner2_1[1]) + abs(corner3_in_new_base[1]-corner2_3[1]) <= abs(corner2_1[1]-corner2_3[1]))
                    {
                        //Om det inte var tillåtet att röra sig så ska objektet som stöttes i få rörelsen istället
                        it->set_forced_x_movement(it->get_forced_x_movement() + character_pointer->get_x_movement() + character_pointer->get_forced_x_movement());
                        it->set_forced_y_movement(it->get_forced_y_movement() + character_pointer->get_y_movement() + character_pointer->get_forced_y_movement());
                        it->set_explosion_movement_x(it->get_explosion_movement_x() + character_pointer->get_explosion_movement_x() / explosion_transfer_loss);
                        it->set_explosion_movement_y(it->get_explosion_movement_y() + character_pointer->get_explosion_movement_y() / explosion_transfer_loss);
                        character_pointer->set_explosion_movement_x(character_pointer->get_explosion_movement_x() / explosion_contact_movement_loss);
                        character_pointer->set_explosion_movement_y(character_pointer->get_explosion_movement_y() / explosion_contact_movement_loss);
                        return false;
                    }
                    {
                        if(abs(corner4_in_new_base[0]-corner2_1[0]) + abs(corner4_in_new_base[0]-corner2_3[0]) <= abs(corner2_1[0]-corner2_3[0]) and
                                abs(corner4_in_new_base[1]-corner2_1[1]) + abs(corner4_in_new_base[1]-corner2_3[1]) <= abs(corner2_1[1]-corner2_3[1]))
                        {
                            //Om det inte var tillåtet att röra sig så ska objektet som stöttes i få rörelsen istället
                            it->set_forced_x_movement(it->get_forced_x_movement() + character_pointer->get_x_movement() + character_pointer->get_forced_x_movement());
                            it->set_forced_y_movement(it->get_forced_y_movement() + character_pointer->get_y_movement() + character_pointer->get_forced_y_movement());
                            it->set_explosion_movement_x(it->get_explosion_movement_x() + character_pointer->get_explosion_movement_x() / explosion_transfer_loss);
                            it->set_explosion_movement_y(it->get_explosion_movement_y() + character_pointer->get_explosion_movement_y() / explosion_transfer_loss);
                            character_pointer->set_explosion_movement_x(character_pointer->get_explosion_movement_x() / explosion_contact_movement_loss);
                            character_pointer->set_explosion_movement_y(character_pointer->get_explosion_movement_y() / explosion_contact_movement_loss);
                            return false;
                        }
                    }
                }
            }


        }
    }
    //HAR VI TAGIT OSS HIT SÅ HAR REKTANGELN KOLLAT KOLLISION MOT ALLA REKTANGLAR I COVER-LISTAN I GAMEFIELD
    //om vi vill att rektanglar ska kunna kollidera med annat än just rektanglar så får vi alltså lägga till det.

    //Det är nu dags att låta rektangeln kolla kollision mot alla karaktärer, utan sig själv förstås!
    vector<character>* character_vector = gamefield_pointer->get_character_vector();
    for(std::vector<character>::iterator it = character_vector->begin(); it != character_vector->end(); ++it)
    {   if(it->get_pointer_to_yourself() != character_pointer)
        {

            vector<double>corner_vector = it->get_corners(); //Tänker att get_corner returnerar
            //x1,y1,x2,y2.. för de olika hörnen i en vektor i den ordningen.
            //Skriver rektangelns hörn i de nya koordinaterna u,v.

            //Tänker att jag behöver utföra någon kontroll om kontroll av kollision är överhuvudtaget nödvändig:
            //Detta görs genom att jämföra avstånden mellan de båda rektanglarnas mittpunkter mot längden av dess diagonaler summerade.

            //Dessa två vektorer går genom diagonalen på bägge rektanglarna
            double help_vector_rec_1[2] = {corner_vector_to_check[2] - corner_vector_to_check[6], corner_vector_to_check[3] - corner_vector_to_check[7]};
            double help_vector_rec_2[2] = {corner_vector[2] - corner_vector[6], corner_vector[3] - corner_vector[7]};

            //Längden av diagonalen i varje rektangel
            double length_dia_1 = sqrt(pow(help_vector_rec_1[0],2) + pow(help_vector_rec_1[1],2));
            double length_dia_2 = sqrt(pow(help_vector_rec_2[0],2) + pow(help_vector_rec_2[1],2));

            //Längden mellan rektanglarnas mittpunkter
            double length_between_midpoints = sqrt(pow(corner_vector_to_check[6]+help_vector_rec_1[0]/2 - (corner_vector[6] + help_vector_rec_2[0]/2),2) + pow(corner_vector_to_check[7]+help_vector_rec_1[1]/2 - (corner_vector[7] + help_vector_rec_2[1]/2),2));
            //Om längden mellan rektanglarnas mittpunkter är mindre än summan av dess diagonaler så kan det vara bra att utföra kollisionskontroll.
            if(length_dia_1/2 + length_dia_2/2 + 1 >= length_between_midpoints)
            {
                double corner_to_check1[2];
                double corner_to_check2[2];
                double corner_to_check3[2];
                double corner_to_check4[2];
                corner_to_check1[0] = base_change_matrix[0][0]*corner_vector[0] + base_change_matrix[0][1]*corner_vector[1];
                corner_to_check1[1] = base_change_matrix[1][0]*corner_vector[0] + base_change_matrix[1][1]*corner_vector[1];

                corner_to_check2[0] = base_change_matrix[0][0]*corner_vector[2] + base_change_matrix[0][1]*corner_vector[3];
                corner_to_check2[1] = base_change_matrix[1][0]*corner_vector[2] + base_change_matrix[1][1]*corner_vector[3];

                corner_to_check3[0] = base_change_matrix[0][0]*corner_vector[4] + base_change_matrix[0][1]*corner_vector[5];
                corner_to_check3[1] = base_change_matrix[1][0]*corner_vector[4] + base_change_matrix[1][1]*corner_vector[5];

                corner_to_check4[0] = base_change_matrix[0][0]*corner_vector[6] + base_change_matrix[0][1]*corner_vector[7];
                corner_to_check4[1] = base_change_matrix[1][0]*corner_vector[6] + base_change_matrix[1][1]*corner_vector[7];

                //Kollar om någon av rektangelns hörn ligger inuti rektangeln som vi kollar kollision för.
                //Eftersom vi har gjort ett basbyte till rektangelns, som vi kollar kollision för, sidor så
                //befinner sig varje hörn på enbart en axel, således mäter vi avståndet ifrån 2 hörn på en axel till rektangelns
                //koordinat på denna axel och jämför detta avstånd med avståndet mellan de båda hörnen.
                if(abs(corner_to_check1[0]-corner_1[0]) + abs(corner_to_check1[0]-corner_3[0]) <= abs(corner_1[0]-corner_3[0]) and
                        abs(corner_to_check1[1]-corner_1[1]) + abs(corner_to_check1[1]-corner_3[1]) <= abs(corner_1[1]-corner_3[1]))
                {
                    //Om det inte var tillåtet att röra sig så ska objektet som stöttes i få rörelsen istället
                    it->set_forced_x_movement(it->get_forced_x_movement() + character_pointer->get_x_movement() + character_pointer->get_forced_x_movement());
                    it->set_forced_y_movement(it->get_forced_y_movement() + character_pointer->get_y_movement() + character_pointer->get_forced_y_movement());
                    it->set_explosion_movement_x(it->get_explosion_movement_x() + character_pointer->get_explosion_movement_x() / explosion_transfer_loss);
                    it->set_explosion_movement_y(it->get_explosion_movement_y() + character_pointer->get_explosion_movement_y() / explosion_transfer_loss);
                    character_pointer->set_explosion_movement_x(character_pointer->get_explosion_movement_x() / explosion_contact_movement_loss);
                    character_pointer->set_explosion_movement_y(character_pointer->get_explosion_movement_y() / explosion_contact_movement_loss);
                    return false;
                }
                {
                    if(abs(corner_to_check2[0]-corner_1[0]) + abs(corner_to_check2[0]-corner_3[0]) <= abs(corner_1[0]-corner_3[0]) and
                            abs(corner_to_check2[1]-corner_1[1]) + abs(corner_to_check2[1]-corner_3[1]) <= abs(corner_1[1]-corner_3[1]))
                    {
                        //Om det inte var tillåtet att röra sig så ska objektet som stöttes i få rörelsen istället
                        it->set_forced_x_movement(it->get_forced_x_movement() + character_pointer->get_x_movement() + character_pointer->get_forced_x_movement());
                        it->set_forced_y_movement(it->get_forced_y_movement() + character_pointer->get_y_movement() + character_pointer->get_forced_y_movement());
                        it->set_explosion_movement_x(it->get_explosion_movement_x() + character_pointer->get_explosion_movement_x() / explosion_transfer_loss);
                        it->set_explosion_movement_y(it->get_explosion_movement_y() + character_pointer->get_explosion_movement_y() / explosion_transfer_loss);
                        character_pointer->set_explosion_movement_x(character_pointer->get_explosion_movement_x() / explosion_contact_movement_loss);
                        character_pointer->set_explosion_movement_y(character_pointer->get_explosion_movement_y() / explosion_contact_movement_loss);
                        return false;
                    }
                    {
                        if(abs(corner_to_check3[0]-corner_1[0]) + abs(corner_to_check3[0]-corner_3[0]) <= abs(corner_1[0]-corner_3[0]) and
                                abs(corner_to_check3[1]-corner_1[1]) + abs(corner_to_check3[1]-corner_3[1]) <= abs(corner_1[1]-corner_3[1]))
                        {
                            //Om det inte var tillåtet att röra sig så ska objektet som stöttes i få rörelsen istället
                            it->set_forced_x_movement(it->get_forced_x_movement() + character_pointer->get_x_movement() + character_pointer->get_forced_x_movement());
                            it->set_forced_y_movement(it->get_forced_y_movement() + character_pointer->get_y_movement() + character_pointer->get_forced_y_movement());
                            it->set_explosion_movement_x(it->get_explosion_movement_x() + character_pointer->get_explosion_movement_x() / explosion_transfer_loss);
                            it->set_explosion_movement_y(it->get_explosion_movement_y() + character_pointer->get_explosion_movement_y() / explosion_transfer_loss);
                            character_pointer->set_explosion_movement_x(character_pointer->get_explosion_movement_x() / explosion_contact_movement_loss);
                            character_pointer->set_explosion_movement_y(character_pointer->get_explosion_movement_y() / explosion_contact_movement_loss);
                            return false;
                        }
                        {
                            if(abs(corner_to_check4[0]-corner_1[0]) + abs(corner_to_check4[0]-corner_3[0]) <= abs(corner_1[0]-corner_3[0]) and
                                    abs(corner_to_check4[1]-corner_1[1]) + abs(corner_to_check4[1]-corner_3[1]) <= abs(corner_1[1]-corner_3[1]))
                            {
                                //Om det inte var tillåtet att röra sig så ska objektet som stöttes i få rörelsen istället
                                it->set_forced_x_movement(it->get_forced_x_movement() + character_pointer->get_x_movement() + character_pointer->get_forced_x_movement());
                                it->set_forced_y_movement(it->get_forced_y_movement() + character_pointer->get_y_movement() + character_pointer->get_forced_y_movement());
                                it->set_explosion_movement_x(it->get_explosion_movement_x() + character_pointer->get_explosion_movement_x() / explosion_transfer_loss);
                                it->set_explosion_movement_y(it->get_explosion_movement_y() + character_pointer->get_explosion_movement_y() / explosion_transfer_loss);
                                character_pointer->set_explosion_movement_x(character_pointer->get_explosion_movement_x() / explosion_contact_movement_loss);
                                character_pointer->set_explosion_movement_y(character_pointer->get_explosion_movement_y() / explosion_contact_movement_loss);
                                return false;
                            }
                        }
                    }
                }

                //Har vi tagit oss hit har vi inte fått någon kollission, vad som krävs nu är att vi gör ytterliggare ett basbyte, men nu till rektangeln i cover listan
                double base_vector_u2[2] = {corner_vector[2] - corner_vector[0], corner_vector[3] - corner_vector[1]}; //u2 uttryckt i basen x,y
                double base_vector_v2[2] = {corner_vector[4] - corner_vector[2], corner_vector[5] - corner_vector[3]}; //v2 uttryckt i basen x,y
                //Vi vill normera basvektorerna
                double normalize_u2 = sqrt(pow(base_vector_u2[0],2) + pow(base_vector_u2[1],2));
                double normalize_v2 = sqrt(pow(base_vector_v2[0],2) + pow(base_vector_v2[1],2));

                base_vector_u2[0] = base_vector_u2[0] / normalize_u2;
                base_vector_u2[1] = base_vector_u2[1] / normalize_u2;
                base_vector_v2[0] = base_vector_v2[0] / normalize_v2;
                base_vector_v2[1] = base_vector_v2[1] / normalize_v2;
                //Skapar en "basbytarmatris" för att lätt kunna byta bas från x,y till u2,v2.
                //Notera att eftersom baserna är normerade så är Ae->f = (Af->e)^-1 = (Af->e)^t
                double base_change_matrix2[2][2] = {base_vector_u2[0],base_vector_u2[1],base_vector_v2[0],base_vector_v2[1]};

                //Tar ut koordinaterna för rektangelns hörn i den nya koordinaten, notera att jag bara behöver
                //ta ut två hörn, de "motsatta" eftersom vi gör det i en nya bas där rektangeln nu är vinkelrät
                //relativt koordinataxlarna.
                double corner2_1[2];
                corner2_1[0] = base_change_matrix2[0][0]*corner_vector[0] + base_change_matrix2[0][1]*corner_vector[1];
                corner2_1[1] = base_change_matrix2[1][0]*corner_vector[0] + base_change_matrix2[1][1]*corner_vector[1];

                double corner2_3[2];
                corner2_3[0] = base_change_matrix2[0][0]*corner_vector[4] + base_change_matrix2[0][1]*corner_vector[5];
                corner2_3[1] = base_change_matrix2[1][0]*corner_vector[4] + base_change_matrix2[1][1]*corner_vector[5];

                //Nu behöver vi kolla om rektangeln i cover "skär" in i den rektangeln vi kollar kollission för

                //skapar ny arrays för att hålla hörnen i den nya basen
                double corner1_in_new_base[2];
                double corner2_in_new_base[2];
                double corner3_in_new_base[2];
                double corner4_in_new_base[2];
                corner1_in_new_base[0] = base_change_matrix2[0][0]*corner_vector_to_check.at(0) + base_change_matrix2[0][1]*corner_vector_to_check.at(1);
                corner1_in_new_base[1] = base_change_matrix2[1][0]*corner_vector_to_check.at(0) + base_change_matrix2[1][1]*corner_vector_to_check.at(1);

                corner2_in_new_base[0] = base_change_matrix2[0][0]*corner_vector_to_check.at(2) + base_change_matrix2[0][1]*corner_vector_to_check.at(3);
                corner2_in_new_base[1] = base_change_matrix2[1][0]*corner_vector_to_check.at(2) + base_change_matrix2[1][1]*corner_vector_to_check.at(3);

                corner3_in_new_base[0] = base_change_matrix2[0][0]*corner_vector_to_check.at(4) + base_change_matrix2[0][1]*corner_vector_to_check.at(5);
                corner3_in_new_base[1] = base_change_matrix2[1][0]*corner_vector_to_check.at(4) + base_change_matrix2[1][1]*corner_vector_to_check.at(5);

                corner4_in_new_base[0] = base_change_matrix2[0][0]*corner_vector_to_check.at(6) + base_change_matrix2[0][1]*corner_vector_to_check.at(7);
                corner4_in_new_base[1] = base_change_matrix2[1][0]*corner_vector_to_check.at(6) + base_change_matrix2[1][1]*corner_vector_to_check.at(7);



                //Kollar om någon av rektangelns (vars kollission vi undersöker) hörn ligger inuti rektangeln från cover-listan
                if(abs(corner1_in_new_base[0]-corner2_1[0]) + abs(corner1_in_new_base[0]-corner2_3[0]) <= abs(corner2_1[0]-corner2_3[0]) and
                        abs(corner1_in_new_base[1]-corner2_1[1]) + abs(corner1_in_new_base[1]-corner2_3[1]) <= abs(corner2_1[1]-corner2_3[1]))
                {
                    //Om det inte var tillåtet att röra sig så ska objektet som stöttes i få rörelsen istället
                    it->set_forced_x_movement(it->get_forced_x_movement() + character_pointer->get_x_movement() + character_pointer->get_forced_x_movement());
                    it->set_forced_y_movement(it->get_forced_y_movement() + character_pointer->get_y_movement() + character_pointer->get_forced_y_movement());
                    it->set_explosion_movement_x(it->get_explosion_movement_x() + character_pointer->get_explosion_movement_x() / explosion_transfer_loss);
                    it->set_explosion_movement_y(it->get_explosion_movement_y() + character_pointer->get_explosion_movement_y() / explosion_transfer_loss);
                    character_pointer->set_explosion_movement_x(character_pointer->get_explosion_movement_x() / explosion_contact_movement_loss);
                    character_pointer->set_explosion_movement_y(character_pointer->get_explosion_movement_y() / explosion_contact_movement_loss);
                    return false;
                }
                {
                    if(abs(corner2_in_new_base[0]-corner2_1[0]) + abs(corner2_in_new_base[0]-corner2_3[0]) <= abs(corner2_1[0]-corner2_3[0]) and
                            abs(corner2_in_new_base[1]-corner2_1[1]) + abs(corner2_in_new_base[1]-corner2_3[1]) <= abs(corner2_1[1]-corner2_3[1]))
                    {
                        //Om det inte var tillåtet att röra sig så ska objektet som stöttes i få rörelsen istället
                        it->set_forced_x_movement(it->get_forced_x_movement() + character_pointer->get_x_movement() + character_pointer->get_forced_x_movement());
                        it->set_forced_y_movement(it->get_forced_y_movement() + character_pointer->get_y_movement() + character_pointer->get_forced_y_movement());
                        it->set_explosion_movement_x(it->get_explosion_movement_x() + character_pointer->get_explosion_movement_x() / explosion_transfer_loss);
                        it->set_explosion_movement_y(it->get_explosion_movement_y() + character_pointer->get_explosion_movement_y() / explosion_transfer_loss);
                        character_pointer->set_explosion_movement_x(character_pointer->get_explosion_movement_x() / explosion_contact_movement_loss);
                        character_pointer->set_explosion_movement_y(character_pointer->get_explosion_movement_y() / explosion_contact_movement_loss);
                        return false;
                    }
                    {
                        if(abs(corner3_in_new_base[0]-corner2_1[0]) + abs(corner3_in_new_base[0]-corner2_3[0]) <= abs(corner2_1[0]-corner2_3[0]) and
                                abs(corner3_in_new_base[1]-corner2_1[1]) + abs(corner3_in_new_base[1]-corner2_3[1]) <= abs(corner2_1[1]-corner2_3[1]))
                        {
                            //Om det inte var tillåtet att röra sig så ska objektet som stöttes i få rörelsen istället
                            it->set_forced_x_movement(it->get_forced_x_movement() + character_pointer->get_x_movement() + character_pointer->get_forced_x_movement());
                            it->set_forced_y_movement(it->get_forced_y_movement() + character_pointer->get_y_movement() + character_pointer->get_forced_y_movement());
                            it->set_explosion_movement_x(it->get_explosion_movement_x() + character_pointer->get_explosion_movement_x() / explosion_transfer_loss);
                            it->set_explosion_movement_y(it->get_explosion_movement_y() + character_pointer->get_explosion_movement_y() / explosion_transfer_loss);
                            character_pointer->set_explosion_movement_x(character_pointer->get_explosion_movement_x() / explosion_contact_movement_loss);
                            character_pointer->set_explosion_movement_y(character_pointer->get_explosion_movement_y() / explosion_contact_movement_loss);
                            return false;
                        }
                        {
                            if(abs(corner4_in_new_base[0]-corner2_1[0]) + abs(corner4_in_new_base[0]-corner2_3[0]) <= abs(corner2_1[0]-corner2_3[0]) and
                                    abs(corner4_in_new_base[1]-corner2_1[1]) + abs(corner4_in_new_base[1]-corner2_3[1]) <= abs(corner2_1[1]-corner2_3[1]))
                            {
                                //Om det inte var tillåtet att röra sig så ska objektet som stöttes i få rörelsen istället
                                it->set_forced_x_movement(it->get_forced_x_movement() + character_pointer->get_x_movement() + character_pointer->get_forced_x_movement());
                                it->set_forced_y_movement(it->get_forced_y_movement() + character_pointer->get_y_movement() + character_pointer->get_forced_y_movement());
                                it->set_explosion_movement_x(it->get_explosion_movement_x() + character_pointer->get_explosion_movement_x() / explosion_transfer_loss);
                                it->set_explosion_movement_y(it->get_explosion_movement_y() + character_pointer->get_explosion_movement_y() / explosion_transfer_loss);
                                character_pointer->set_explosion_movement_x(character_pointer->get_explosion_movement_x() / explosion_contact_movement_loss);
                                character_pointer->set_explosion_movement_y(character_pointer->get_explosion_movement_y() / explosion_contact_movement_loss);
                                return false;
                            }
                        }
                    }
                }

            }
        }
    }


    return true;
}





/*Allowed_to_move_rectangle(vector<double>,cover*)
 * Beräknar huruvida en rektangels nya position är okej att flytta till.
 * Om rektangeln inte fick flytta sig till den nya position så påverkas det objekt som var ivägen på olika sätt,
 * t.ex. så överförs två krafter, en forced_movement och en explosion_movement som påverkar objektets rörelse på olika sätt
 *
 */
bool collision_handler::allowed_to_move_rectangle(vector<double> corner_vector_to_check,cover* cover_pointer)/*(double x1,double y1,double x2,double y2,double x3,double y3,double x4,double y4)*/
{//corner_vector_to_check innehåller koordinaterna för rektangelns hörn som skall kollas i ordningen, x1,y1,x2,y2,x3,....
    //Kollar först så att rektangeln inte försöker smita utanför banan

    if(corner_vector_to_check.at(0) < 0 or corner_vector_to_check.at(2) < 0 or corner_vector_to_check.at(4) < 0 or corner_vector_to_check.at(6) < 0
            or corner_vector_to_check.at(0) > window_width or corner_vector_to_check.at(2) > window_width or corner_vector_to_check.at(4) > window_width or corner_vector_to_check.at(6) > window_width)
    {
        cover_pointer->set_explosion_movement_x(-cover_pointer->get_explosion_movement_x());
        return false;
    }
    if(corner_vector_to_check.at(1) < 0 or corner_vector_to_check.at(3) < 0 or corner_vector_to_check.at(5) < 0 or corner_vector_to_check.at(7) < 0
            or corner_vector_to_check.at(1) > window_height or corner_vector_to_check.at(3) > window_height or corner_vector_to_check.at(5) > window_height or corner_vector_to_check.at(7) > window_height)
    {
        cover_pointer->set_explosion_movement_y(-cover_pointer->get_explosion_movement_y());
        return false;
    }
    vector<cover>* cover_vector = gamefield_pointer->get_cover_vector();
    //Skapar den nya basen för rektangeln, (x2-x1,y2-y1) och (x3-x2,y3-y2)
    double base_vector_u[2] = {corner_vector_to_check.at(2) - corner_vector_to_check.at(0), corner_vector_to_check.at(3) - corner_vector_to_check.at(1)}; //u uttryckt i basen x,y
    double base_vector_v[2] = {corner_vector_to_check.at(4) - corner_vector_to_check.at(2), corner_vector_to_check.at(5) - corner_vector_to_check.at(3)}; //v uttryckt i basen x,y
    //Vi vill normera basvektorerna
    double normalize_u = sqrt(pow(base_vector_u[0],2) + pow(base_vector_u[1],2));
    double normalize_v = sqrt(pow(base_vector_v[0],2) + pow(base_vector_v[1],2));

    base_vector_u[0] = base_vector_u[0] / normalize_u;
    base_vector_u[1] = base_vector_u[1] / normalize_u;
    base_vector_v[0] = base_vector_v[0] / normalize_v;
    base_vector_v[1] = base_vector_v[1] / normalize_v;
    //Skapar en "basbytarmatris" för att lätt kunna byta bas från x,y till u,v.
    //Notera att eftersom baserna är normerade så är Ae->f = (Af->e)^-1 = (Af->e)^t
    double base_change_matrix[2][2] = {base_vector_u[0],base_vector_u[1],base_vector_v[0],base_vector_v[1]};

    //Tar ut koordinaterna för rektangelns hörn i den nya koordinaten, notera att jag bara behöver
    //ta ut två hörn, de "motsatta" eftersom vi gör det i en nya bas där rektangeln nu är vinkelrät
    //relativt koordinataxlarna.
    double corner_1[2];
    corner_1[0] = base_change_matrix[0][0]*corner_vector_to_check.at(0) + base_change_matrix[0][1]*corner_vector_to_check.at(1);
    corner_1[1] = base_change_matrix[1][0]*corner_vector_to_check.at(0) + base_change_matrix[1][1]*corner_vector_to_check.at(1);

    double corner_3[2];
    corner_3[0] = base_change_matrix[0][0]*corner_vector_to_check.at(4) + base_change_matrix[0][1]*corner_vector_to_check.at(5);
    corner_3[1] = base_change_matrix[1][0]*corner_vector_to_check.at(4) + base_change_matrix[1][1]*corner_vector_to_check.at(5);

    double explosion_contact_movement_loss = 2; //Det faktor som explosionshastigheten delas med vid varje kollision
    double explosion_transfer_loss = 1.5; //Den faktor som explosionshastigheten skalas ner med då den överförs till ett nytt objekt
    //Nu har vi initierat klart och behöver alltså kolla igenom om den nya koordinaten är okej att flytta till.
    //Vi börjar med att gå igenom cover listan (som just nu antas bara bestå av rektangelobjekt.
    for(std::vector<cover>::iterator it = cover_vector->begin(); it != cover_vector->end(); ++it)
    {
        if(it->get_pointer_to_yourself() != cover_pointer)
        {
            vector<double>corner_vector = it->get_corners(); //Tänker att get_corner returnerar
            //x1,y1,x2,y2.. för de olika hörnen i en vektor i den ordningen.
            //Skriver rektangelns hörn i de nya koordinaterna u,v.

            //Tänker att jag behöver utföra någon kontroll om kontroll av kollision är överhuvudtaget nödvändig:
            //Detta görs genom att jämföra avstånden mellan de båda rektanglarnas mittpunkter mot längden av dess diagonaler summerade.

            //Dessa två vektorer går genom diagonalen på bägge rektanglarna
            double help_vector_rec_1[2] = {corner_vector_to_check[2] - corner_vector_to_check[6], corner_vector_to_check[3] - corner_vector_to_check[7]};
            double help_vector_rec_2[2] = {corner_vector[2] - corner_vector[6], corner_vector[3] - corner_vector[7]};

            //Längden av diagonalen i varje rektangel
            double length_dia_1 = sqrt(pow(help_vector_rec_1[0],2) + pow(help_vector_rec_1[1],2));
            double length_dia_2 = sqrt(pow(help_vector_rec_2[0],2) + pow(help_vector_rec_2[1],2));

            //Längden mellan rektanglarnas mittpunkter
            double length_between_midpoints = sqrt(pow(corner_vector_to_check[6]+help_vector_rec_1[0]/2 - (corner_vector[6] + help_vector_rec_2[0]/2),2) + pow(corner_vector_to_check[7]+help_vector_rec_1[1]/2 - (corner_vector[7] + help_vector_rec_2[1]/2),2));
            //Om längden mellan rektanglarnas mittpunkter är mindre än summan av dess diagonaler så kan det vara bra att utföra kollisionskontroll.
            if(length_dia_1/2 + length_dia_2/2 + 1 >= length_between_midpoints)
            {
                double corner_to_check1[2];
                double corner_to_check2[2];
                double corner_to_check3[2];
                double corner_to_check4[2];
                corner_to_check1[0] = base_change_matrix[0][0]*corner_vector[0] + base_change_matrix[0][1]*corner_vector[1];
                corner_to_check1[1] = base_change_matrix[1][0]*corner_vector[0] + base_change_matrix[1][1]*corner_vector[1];

                corner_to_check2[0] = base_change_matrix[0][0]*corner_vector[2] + base_change_matrix[0][1]*corner_vector[3];
                corner_to_check2[1] = base_change_matrix[1][0]*corner_vector[2] + base_change_matrix[1][1]*corner_vector[3];

                corner_to_check3[0] = base_change_matrix[0][0]*corner_vector[4] + base_change_matrix[0][1]*corner_vector[5];
                corner_to_check3[1] = base_change_matrix[1][0]*corner_vector[4] + base_change_matrix[1][1]*corner_vector[5];

                corner_to_check4[0] = base_change_matrix[0][0]*corner_vector[6] + base_change_matrix[0][1]*corner_vector[7];
                corner_to_check4[1] = base_change_matrix[1][0]*corner_vector[6] + base_change_matrix[1][1]*corner_vector[7];

                //Kollar om någon av rektangelns hörn ligger inuti rektangeln som vi kollar kollision för.
                //Eftersom vi har gjort ett basbyte till rektangelns, som vi kollar kollision för, sidor så
                //befinner sig varje hörn på enbart en axel, således mäter vi avståndet ifrån 2 hörn på en axel till rektangelns
                //koordinat på denna axel och jämför detta avstånd med avståndet mellan de båda hörnen.
                if(abs(corner_to_check1[0]-corner_1[0]) + abs(corner_to_check1[0]-corner_3[0]) <= abs(corner_1[0]-corner_3[0]) and
                        abs(corner_to_check1[1]-corner_1[1]) + abs(corner_to_check1[1]-corner_3[1]) <= abs(corner_1[1]-corner_3[1]))
                {
                    //Om det inte var tillåtet att röra sig så ska objektet som stöttes i få rörelsen istället
                    it->set_forced_x_movement(it->get_forced_x_movement() + cover_pointer->get_forced_x_movement());
                    it->set_forced_y_movement(it->get_forced_y_movement() + cover_pointer->get_forced_y_movement());
                    it->set_explosion_movement_x(it->get_explosion_movement_x() + cover_pointer->get_explosion_movement_x() / explosion_transfer_loss);
                    it->set_explosion_movement_y(it->get_explosion_movement_y() + cover_pointer->get_explosion_movement_y() / explosion_transfer_loss);
                    cover_pointer->set_explosion_movement_x(cover_pointer->get_explosion_movement_x() / explosion_contact_movement_loss);
                    cover_pointer->set_explosion_movement_y(cover_pointer->get_explosion_movement_y() / explosion_contact_movement_loss);
                    return false;
                }
                {
                    if(abs(corner_to_check2[0]-corner_1[0]) + abs(corner_to_check2[0]-corner_3[0]) <= abs(corner_1[0]-corner_3[0]) and
                            abs(corner_to_check2[1]-corner_1[1]) + abs(corner_to_check2[1]-corner_3[1]) <= abs(corner_1[1]-corner_3[1]))
                    {
                        //Om det inte var tillåtet att röra sig så ska objektet som stöttes i få rörelsen istället
                        it->set_forced_x_movement(it->get_forced_x_movement() + cover_pointer->get_forced_x_movement());
                        it->set_forced_y_movement(it->get_forced_y_movement() + cover_pointer->get_forced_y_movement());
                        it->set_explosion_movement_x(it->get_explosion_movement_x() + cover_pointer->get_explosion_movement_x() / explosion_transfer_loss);
                        it->set_explosion_movement_y(it->get_explosion_movement_y() + cover_pointer->get_explosion_movement_y() / explosion_transfer_loss);
                        cover_pointer->set_explosion_movement_x(cover_pointer->get_explosion_movement_x() / explosion_contact_movement_loss);
                        cover_pointer->set_explosion_movement_y(cover_pointer->get_explosion_movement_y() / explosion_contact_movement_loss);
                        return false;
                    }
                    {
                        if(abs(corner_to_check3[0]-corner_1[0]) + abs(corner_to_check3[0]-corner_3[0]) <= abs(corner_1[0]-corner_3[0]) and
                                abs(corner_to_check3[1]-corner_1[1]) + abs(corner_to_check3[1]-corner_3[1]) <= abs(corner_1[1]-corner_3[1]))
                        {
                            //Om det inte var tillåtet att röra sig så ska objektet som stöttes i få rörelsen istället
                            it->set_forced_x_movement(it->get_forced_x_movement() + cover_pointer->get_forced_x_movement());
                            it->set_forced_y_movement(it->get_forced_y_movement() + cover_pointer->get_forced_y_movement());
                            it->set_explosion_movement_x(it->get_explosion_movement_x() + cover_pointer->get_explosion_movement_x() / explosion_transfer_loss);
                            it->set_explosion_movement_y(it->get_explosion_movement_y() + cover_pointer->get_explosion_movement_y() / explosion_transfer_loss);
                            cover_pointer->set_explosion_movement_x(cover_pointer->get_explosion_movement_x() / explosion_contact_movement_loss);
                            cover_pointer->set_explosion_movement_y(cover_pointer->get_explosion_movement_y() / explosion_contact_movement_loss);
                            return false;
                        }
                        {
                            if(abs(corner_to_check4[0]-corner_1[0]) + abs(corner_to_check4[0]-corner_3[0]) <= abs(corner_1[0]-corner_3[0]) and
                                    abs(corner_to_check4[1]-corner_1[1]) + abs(corner_to_check4[1]-corner_3[1]) <= abs(corner_1[1]-corner_3[1]))
                            {
                                //Om det inte var tillåtet att röra sig så ska objektet som stöttes i få rörelsen istället
                                it->set_forced_x_movement(it->get_forced_x_movement() + cover_pointer->get_forced_x_movement());
                                it->set_forced_y_movement(it->get_forced_y_movement() + cover_pointer->get_forced_y_movement());
                                it->set_explosion_movement_x(it->get_explosion_movement_x() + cover_pointer->get_explosion_movement_x() / explosion_transfer_loss);
                                it->set_explosion_movement_y(it->get_explosion_movement_y() + cover_pointer->get_explosion_movement_y() / explosion_transfer_loss);
                                cover_pointer->set_explosion_movement_x(cover_pointer->get_explosion_movement_x() / explosion_contact_movement_loss);
                                cover_pointer->set_explosion_movement_y(cover_pointer->get_explosion_movement_y() / explosion_contact_movement_loss);
                                return false;
                            }
                        }
                    }
                }

                //Har vi tagit oss hit har vi inte fått någon kollission, vad som krävs nu är att vi gör ytterliggare ett basbyte, men nu till rektangeln i cover listan
                double base_vector_u2[2] = {corner_vector[2] - corner_vector[0], corner_vector[3] - corner_vector[1]}; //u2 uttryckt i basen x,y
                double base_vector_v2[2] = {corner_vector[4] - corner_vector[2], corner_vector[5] - corner_vector[3]}; //v2 uttryckt i basen x,y
                //Vi vill normera basvektorerna
                double normalize_u2 = sqrt(pow(base_vector_u2[0],2) + pow(base_vector_u2[1],2));
                double normalize_v2 = sqrt(pow(base_vector_v2[0],2) + pow(base_vector_v2[1],2));

                base_vector_u2[0] = base_vector_u2[0] / normalize_u2;
                base_vector_u2[1] = base_vector_u2[1] / normalize_u2;
                base_vector_v2[0] = base_vector_v2[0] / normalize_v2;
                base_vector_v2[1] = base_vector_v2[1] / normalize_v2;
                //Skapar en "basbytarmatris" för att lätt kunna byta bas från x,y till u2,v2.
                //Notera att eftersom baserna är normerade så är Ae->f = (Af->e)^-1 = (Af->e)^t
                double base_change_matrix2[2][2] = {base_vector_u2[0],base_vector_u2[1],base_vector_v2[0],base_vector_v2[1]};

                //Tar ut koordinaterna för rektangelns hörn i den nya koordinaten, notera att jag bara behöver
                //ta ut två hörn, de "motsatta" eftersom vi gör det i en nya bas där rektangeln nu är vinkelrät
                //relativt koordinataxlarna.
                double corner2_1[2];
                corner2_1[0] = base_change_matrix2[0][0]*corner_vector[0] + base_change_matrix2[0][1]*corner_vector[1];
                corner2_1[1] = base_change_matrix2[1][0]*corner_vector[0] + base_change_matrix2[1][1]*corner_vector[1];

                double corner2_3[2];
                corner2_3[0] = base_change_matrix2[0][0]*corner_vector[4] + base_change_matrix2[0][1]*corner_vector[5];
                corner2_3[1] = base_change_matrix2[1][0]*corner_vector[4] + base_change_matrix2[1][1]*corner_vector[5];

                //Nu behöver vi kolla om rektangeln i cover "skär" in i den rektangeln vi kollar kollission för

                //skapar ny arrays för att hålla hörnen i den nya basen
                double corner1_in_new_base[2];
                double corner2_in_new_base[2];
                double corner3_in_new_base[2];
                double corner4_in_new_base[2];
                corner1_in_new_base[0] = base_change_matrix2[0][0]*corner_vector_to_check.at(0) + base_change_matrix2[0][1]*corner_vector_to_check.at(1);
                corner1_in_new_base[1] = base_change_matrix2[1][0]*corner_vector_to_check.at(0) + base_change_matrix2[1][1]*corner_vector_to_check.at(1);

                corner2_in_new_base[0] = base_change_matrix2[0][0]*corner_vector_to_check.at(2) + base_change_matrix2[0][1]*corner_vector_to_check.at(3);
                corner2_in_new_base[1] = base_change_matrix2[1][0]*corner_vector_to_check.at(2) + base_change_matrix2[1][1]*corner_vector_to_check.at(3);

                corner3_in_new_base[0] = base_change_matrix2[0][0]*corner_vector_to_check.at(4) + base_change_matrix2[0][1]*corner_vector_to_check.at(5);
                corner3_in_new_base[1] = base_change_matrix2[1][0]*corner_vector_to_check.at(4) + base_change_matrix2[1][1]*corner_vector_to_check.at(5);

                corner4_in_new_base[0] = base_change_matrix2[0][0]*corner_vector_to_check.at(6) + base_change_matrix2[0][1]*corner_vector_to_check.at(7);
                corner4_in_new_base[1] = base_change_matrix2[1][0]*corner_vector_to_check.at(6) + base_change_matrix2[1][1]*corner_vector_to_check.at(7);



                //Kollar om någon av rektangelns (vars kollission vi undersöker) hörn ligger inuti rektangeln från cover-listan
                if(abs(corner1_in_new_base[0]-corner2_1[0]) + abs(corner1_in_new_base[0]-corner2_3[0]) <= abs(corner2_1[0]-corner2_3[0]) and
                        abs(corner1_in_new_base[1]-corner2_1[1]) + abs(corner1_in_new_base[1]-corner2_3[1]) <= abs(corner2_1[1]-corner2_3[1]))
                {
                    //Om det inte var tillåtet att röra sig så ska objektet som stöttes i få rörelsen istället
                    it->set_forced_x_movement(it->get_forced_x_movement() + cover_pointer->get_forced_x_movement());
                    it->set_forced_y_movement(it->get_forced_y_movement() + cover_pointer->get_forced_y_movement());
                    it->set_explosion_movement_x(it->get_explosion_movement_x() + cover_pointer->get_explosion_movement_x() / explosion_transfer_loss);
                    it->set_explosion_movement_y(it->get_explosion_movement_y() + cover_pointer->get_explosion_movement_y() / explosion_transfer_loss);
                    cover_pointer->set_explosion_movement_x(cover_pointer->get_explosion_movement_x() / explosion_contact_movement_loss);
                    cover_pointer->set_explosion_movement_y(cover_pointer->get_explosion_movement_y() / explosion_contact_movement_loss);
                    return false;
                }
                {
                    if(abs(corner2_in_new_base[0]-corner2_1[0]) + abs(corner2_in_new_base[0]-corner2_3[0]) <= abs(corner2_1[0]-corner2_3[0]) and
                            abs(corner2_in_new_base[1]-corner2_1[1]) + abs(corner2_in_new_base[1]-corner2_3[1]) <= abs(corner2_1[1]-corner2_3[1]))
                    {
                        //Om det inte var tillåtet att röra sig så ska objektet som stöttes i få rörelsen istället
                        it->set_forced_x_movement(it->get_forced_x_movement() + cover_pointer->get_forced_x_movement());
                        it->set_forced_y_movement(it->get_forced_y_movement() + cover_pointer->get_forced_y_movement());
                        it->set_explosion_movement_x(it->get_explosion_movement_x() + cover_pointer->get_explosion_movement_x() / explosion_transfer_loss);
                        it->set_explosion_movement_y(it->get_explosion_movement_y() + cover_pointer->get_explosion_movement_y() / explosion_transfer_loss);
                        cover_pointer->set_explosion_movement_x(cover_pointer->get_explosion_movement_x() / explosion_contact_movement_loss);
                        cover_pointer->set_explosion_movement_y(cover_pointer->get_explosion_movement_y() / explosion_contact_movement_loss);
                        return false;
                    }
                    {
                        if(abs(corner3_in_new_base[0]-corner2_1[0]) + abs(corner3_in_new_base[0]-corner2_3[0]) <= abs(corner2_1[0]-corner2_3[0]) and
                                abs(corner3_in_new_base[1]-corner2_1[1]) + abs(corner3_in_new_base[1]-corner2_3[1]) <= abs(corner2_1[1]-corner2_3[1]))
                        {
                            //Om det inte var tillåtet att röra sig så ska objektet som stöttes i få rörelsen istället
                            it->set_forced_x_movement(it->get_forced_x_movement() + cover_pointer->get_forced_x_movement());
                            it->set_forced_y_movement(it->get_forced_y_movement() + cover_pointer->get_forced_y_movement());
                            it->set_explosion_movement_x(it->get_explosion_movement_x() + cover_pointer->get_explosion_movement_x() / explosion_transfer_loss);
                            it->set_explosion_movement_y(it->get_explosion_movement_y() + cover_pointer->get_explosion_movement_y() / explosion_transfer_loss);
                            cover_pointer->set_explosion_movement_x(cover_pointer->get_explosion_movement_x() / explosion_contact_movement_loss);
                            cover_pointer->set_explosion_movement_y(cover_pointer->get_explosion_movement_y() / explosion_contact_movement_loss);
                            return false;
                        }
                        {
                            if(abs(corner4_in_new_base[0]-corner2_1[0]) + abs(corner4_in_new_base[0]-corner2_3[0]) <= abs(corner2_1[0]-corner2_3[0]) and
                                    abs(corner4_in_new_base[1]-corner2_1[1]) + abs(corner4_in_new_base[1]-corner2_3[1]) <= abs(corner2_1[1]-corner2_3[1]))
                            {
                                //Om det inte var tillåtet att röra sig så ska objektet som stöttes i få rörelsen istället
                                it->set_forced_x_movement(it->get_forced_x_movement() + cover_pointer->get_forced_x_movement());
                                it->set_forced_y_movement(it->get_forced_y_movement() + cover_pointer->get_forced_y_movement());
                                it->set_explosion_movement_x(it->get_explosion_movement_x() + cover_pointer->get_explosion_movement_x() / explosion_transfer_loss);
                                it->set_explosion_movement_y(it->get_explosion_movement_y() + cover_pointer->get_explosion_movement_y() / explosion_transfer_loss);
                                cover_pointer->set_explosion_movement_x(cover_pointer->get_explosion_movement_x() / explosion_contact_movement_loss);
                                cover_pointer->set_explosion_movement_y(cover_pointer->get_explosion_movement_y() / explosion_contact_movement_loss);
                                return false;
                            }
                        }
                    }
                }

            }
        }
    }
    //HAR VI TAGIT OSS HIT SÅ HAR REKTANGELN KOLLAT KOLLISION MOT ALLA REKTANGLAR I COVER-LISTAN I GAMEFIELD
    //om vi vill att rektanglar ska kunna kollidera med annat än just rektanglar så får vi alltså lägga till det.

    //Det är nu dags att låta rektangeln kolla kollision mot alla karaktärer, utan sig själv förstås!
    vector<character>* character_vector = gamefield_pointer->get_character_vector();
    for(std::vector<character>::iterator it = character_vector->begin(); it != character_vector->end(); ++it)
    {
        vector<double>corner_vector = it->get_corners(); //Tänker att get_corner returnerar
        //x1,y1,x2,y2.. för de olika hörnen i en vektor i den ordningen.
        //Skriver rektangelns hörn i de nya koordinaterna u,v.

        //Tänker att jag behöver utföra någon kontroll om kontroll av kollision är överhuvudtaget nödvändig:
        //Detta görs genom att jämföra avstånden mellan de båda rektanglarnas mittpunkter mot längden av dess diagonaler summerade.

        //Dessa två vektorer går genom diagonalen på bägge rektanglarna
        double help_vector_rec_1[2] = {corner_vector_to_check[2] - corner_vector_to_check[6], corner_vector_to_check[3] - corner_vector_to_check[7]};
        double help_vector_rec_2[2] = {corner_vector[2] - corner_vector[6], corner_vector[3] - corner_vector[7]};

        //Längden av diagonalen i varje rektangel
        double length_dia_1 = sqrt(pow(help_vector_rec_1[0],2) + pow(help_vector_rec_1[1],2));
        double length_dia_2 = sqrt(pow(help_vector_rec_2[0],2) + pow(help_vector_rec_2[1],2));

        //Längden mellan rektanglarnas mittpunkter
        double length_between_midpoints = sqrt(pow(corner_vector_to_check[6]+help_vector_rec_1[0]/2 - (corner_vector[6] + help_vector_rec_2[0]/2),2) + pow(corner_vector_to_check[7]+help_vector_rec_1[1]/2 - (corner_vector[7] + help_vector_rec_2[1]/2),2));
        //Om längden mellan rektanglarnas mittpunkter är mindre än summan av dess diagonaler så kan det vara bra att utföra kollisionskontroll.
        if(length_dia_1/2 + length_dia_2/2 + 1 >= length_between_midpoints)
        {
            double corner_to_check1[2];
            double corner_to_check2[2];
            double corner_to_check3[2];
            double corner_to_check4[2];
            corner_to_check1[0] = base_change_matrix[0][0]*corner_vector[0] + base_change_matrix[0][1]*corner_vector[1];
            corner_to_check1[1] = base_change_matrix[1][0]*corner_vector[0] + base_change_matrix[1][1]*corner_vector[1];

            corner_to_check2[0] = base_change_matrix[0][0]*corner_vector[2] + base_change_matrix[0][1]*corner_vector[3];
            corner_to_check2[1] = base_change_matrix[1][0]*corner_vector[2] + base_change_matrix[1][1]*corner_vector[3];

            corner_to_check3[0] = base_change_matrix[0][0]*corner_vector[4] + base_change_matrix[0][1]*corner_vector[5];
            corner_to_check3[1] = base_change_matrix[1][0]*corner_vector[4] + base_change_matrix[1][1]*corner_vector[5];

            corner_to_check4[0] = base_change_matrix[0][0]*corner_vector[6] + base_change_matrix[0][1]*corner_vector[7];
            corner_to_check4[1] = base_change_matrix[1][0]*corner_vector[6] + base_change_matrix[1][1]*corner_vector[7];

            //Kollar om någon av rektangelns hörn ligger inuti rektangeln som vi kollar kollision för.
            //Eftersom vi har gjort ett basbyte till rektangelns, som vi kollar kollision för, sidor så
            //befinner sig varje hörn på enbart en axel, således mäter vi avståndet ifrån 2 hörn på en axel till rektangelns
            //koordinat på denna axel och jämför detta avstånd med avståndet mellan de båda hörnen.
            if(abs(corner_to_check1[0]-corner_1[0]) + abs(corner_to_check1[0]-corner_3[0]) <= abs(corner_1[0]-corner_3[0]) and
                    abs(corner_to_check1[1]-corner_1[1]) + abs(corner_to_check1[1]-corner_3[1]) <= abs(corner_1[1]-corner_3[1]))
            {
                //Om det inte var tillåtet att röra sig så ska objektet som stöttes i få rörelsen istället
                it->set_forced_x_movement(it->get_forced_x_movement() + cover_pointer->get_forced_x_movement());
                it->set_forced_y_movement(it->get_forced_y_movement() + cover_pointer->get_forced_y_movement());
                it->set_explosion_movement_x(it->get_explosion_movement_x() + cover_pointer->get_explosion_movement_x() / explosion_transfer_loss);
                it->set_explosion_movement_y(it->get_explosion_movement_y() + cover_pointer->get_explosion_movement_y() / explosion_transfer_loss);
                cover_pointer->set_explosion_movement_x(cover_pointer->get_explosion_movement_x() / explosion_contact_movement_loss);
                cover_pointer->set_explosion_movement_y(cover_pointer->get_explosion_movement_y() / explosion_contact_movement_loss);
                return false;
            }
            {
                if(abs(corner_to_check2[0]-corner_1[0]) + abs(corner_to_check2[0]-corner_3[0]) <= abs(corner_1[0]-corner_3[0]) and
                        abs(corner_to_check2[1]-corner_1[1]) + abs(corner_to_check2[1]-corner_3[1]) <= abs(corner_1[1]-corner_3[1]))
                {
                    //Om det inte var tillåtet att röra sig så ska objektet som stöttes i få rörelsen istället
                    it->set_forced_x_movement(it->get_forced_x_movement() + cover_pointer->get_forced_x_movement());
                    it->set_forced_y_movement(it->get_forced_y_movement() + cover_pointer->get_forced_y_movement());
                    it->set_explosion_movement_x(it->get_explosion_movement_x() + cover_pointer->get_explosion_movement_x() / explosion_transfer_loss);
                    it->set_explosion_movement_y(it->get_explosion_movement_y() + cover_pointer->get_explosion_movement_y() / explosion_transfer_loss);
                    cover_pointer->set_explosion_movement_x(cover_pointer->get_explosion_movement_x() / explosion_contact_movement_loss);
                    cover_pointer->set_explosion_movement_y(cover_pointer->get_explosion_movement_y() / explosion_contact_movement_loss);
                    return false;
                }
                {
                    if(abs(corner_to_check3[0]-corner_1[0]) + abs(corner_to_check3[0]-corner_3[0]) <= abs(corner_1[0]-corner_3[0]) and
                            abs(corner_to_check3[1]-corner_1[1]) + abs(corner_to_check3[1]-corner_3[1]) <= abs(corner_1[1]-corner_3[1]))
                    {
                        //Om det inte var tillåtet att röra sig så ska objektet som stöttes i få rörelsen istället
                        it->set_forced_x_movement(it->get_forced_x_movement() + cover_pointer->get_forced_x_movement());
                        it->set_forced_y_movement(it->get_forced_y_movement() + cover_pointer->get_forced_y_movement());
                        it->set_explosion_movement_x(it->get_explosion_movement_x() + cover_pointer->get_explosion_movement_x() / explosion_transfer_loss);
                        it->set_explosion_movement_y(it->get_explosion_movement_y() + cover_pointer->get_explosion_movement_y() / explosion_transfer_loss);
                        cover_pointer->set_explosion_movement_x(cover_pointer->get_explosion_movement_x() / explosion_contact_movement_loss);
                        cover_pointer->set_explosion_movement_y(cover_pointer->get_explosion_movement_y() / explosion_contact_movement_loss);
                        return false;
                    }
                    {
                        if(abs(corner_to_check4[0]-corner_1[0]) + abs(corner_to_check4[0]-corner_3[0]) <= abs(corner_1[0]-corner_3[0]) and
                                abs(corner_to_check4[1]-corner_1[1]) + abs(corner_to_check4[1]-corner_3[1]) <= abs(corner_1[1]-corner_3[1]))
                        {
                            //Om det inte var tillåtet att röra sig så ska objektet som stöttes i få rörelsen istället
                            it->set_forced_x_movement(it->get_forced_x_movement() + cover_pointer->get_forced_x_movement());
                            it->set_forced_y_movement(it->get_forced_y_movement() + cover_pointer->get_forced_y_movement());
                            it->set_explosion_movement_x(it->get_explosion_movement_x() + cover_pointer->get_explosion_movement_x() / explosion_transfer_loss);
                            it->set_explosion_movement_y(it->get_explosion_movement_y() + cover_pointer->get_explosion_movement_y() / explosion_transfer_loss);
                            cover_pointer->set_explosion_movement_x(cover_pointer->get_explosion_movement_x() / explosion_contact_movement_loss);
                            cover_pointer->set_explosion_movement_y(cover_pointer->get_explosion_movement_y() / explosion_contact_movement_loss);
                            return false;
                        }
                    }
                }
            }

            //Har vi tagit oss hit har vi inte fått någon kollission, vad som krävs nu är att vi gör ytterliggare ett basbyte, men nu till rektangeln i cover listan
            double base_vector_u2[2] = {corner_vector[2] - corner_vector[0], corner_vector[3] - corner_vector[1]}; //u2 uttryckt i basen x,y
            double base_vector_v2[2] = {corner_vector[4] - corner_vector[2], corner_vector[5] - corner_vector[3]}; //v2 uttryckt i basen x,y
            //Vi vill normera basvektorerna
            double normalize_u2 = sqrt(pow(base_vector_u2[0],2) + pow(base_vector_u2[1],2));
            double normalize_v2 = sqrt(pow(base_vector_v2[0],2) + pow(base_vector_v2[1],2));

            base_vector_u2[0] = base_vector_u2[0] / normalize_u2;
            base_vector_u2[1] = base_vector_u2[1] / normalize_u2;
            base_vector_v2[0] = base_vector_v2[0] / normalize_v2;
            base_vector_v2[1] = base_vector_v2[1] / normalize_v2;
            //Skapar en "basbytarmatris" för att lätt kunna byta bas från x,y till u2,v2.
            //Notera att eftersom baserna är normerade så är Ae->f = (Af->e)^-1 = (Af->e)^t
            double base_change_matrix2[2][2] = {base_vector_u2[0],base_vector_u2[1],base_vector_v2[0],base_vector_v2[1]};

            //Tar ut koordinaterna för rektangelns hörn i den nya koordinaten, notera att jag bara behöver
            //ta ut två hörn, de "motsatta" eftersom vi gör det i en nya bas där rektangeln nu är vinkelrät
            //relativt koordinataxlarna.
            double corner2_1[2];
            corner2_1[0] = base_change_matrix2[0][0]*corner_vector[0] + base_change_matrix2[0][1]*corner_vector[1];
            corner2_1[1] = base_change_matrix2[1][0]*corner_vector[0] + base_change_matrix2[1][1]*corner_vector[1];

            double corner2_3[2];
            corner2_3[0] = base_change_matrix2[0][0]*corner_vector[4] + base_change_matrix2[0][1]*corner_vector[5];
            corner2_3[1] = base_change_matrix2[1][0]*corner_vector[4] + base_change_matrix2[1][1]*corner_vector[5];

            //Nu behöver vi kolla om rektangeln i cover "skär" in i den rektangeln vi kollar kollission för

            //skapar ny arrays för att hålla hörnen i den nya basen
            double corner1_in_new_base[2];
            double corner2_in_new_base[2];
            double corner3_in_new_base[2];
            double corner4_in_new_base[2];
            corner1_in_new_base[0] = base_change_matrix2[0][0]*corner_vector_to_check.at(0) + base_change_matrix2[0][1]*corner_vector_to_check.at(1);
            corner1_in_new_base[1] = base_change_matrix2[1][0]*corner_vector_to_check.at(0) + base_change_matrix2[1][1]*corner_vector_to_check.at(1);

            corner2_in_new_base[0] = base_change_matrix2[0][0]*corner_vector_to_check.at(2) + base_change_matrix2[0][1]*corner_vector_to_check.at(3);
            corner2_in_new_base[1] = base_change_matrix2[1][0]*corner_vector_to_check.at(2) + base_change_matrix2[1][1]*corner_vector_to_check.at(3);

            corner3_in_new_base[0] = base_change_matrix2[0][0]*corner_vector_to_check.at(4) + base_change_matrix2[0][1]*corner_vector_to_check.at(5);
            corner3_in_new_base[1] = base_change_matrix2[1][0]*corner_vector_to_check.at(4) + base_change_matrix2[1][1]*corner_vector_to_check.at(5);

            corner4_in_new_base[0] = base_change_matrix2[0][0]*corner_vector_to_check.at(6) + base_change_matrix2[0][1]*corner_vector_to_check.at(7);
            corner4_in_new_base[1] = base_change_matrix2[1][0]*corner_vector_to_check.at(6) + base_change_matrix2[1][1]*corner_vector_to_check.at(7);



            //Kollar om någon av rektangelns (vars kollission vi undersöker) hörn ligger inuti rektangeln från cover-listan
            if(abs(corner1_in_new_base[0]-corner2_1[0]) + abs(corner1_in_new_base[0]-corner2_3[0]) <= abs(corner2_1[0]-corner2_3[0]) and
                    abs(corner1_in_new_base[1]-corner2_1[1]) + abs(corner1_in_new_base[1]-corner2_3[1]) <= abs(corner2_1[1]-corner2_3[1]))
            {
                //Om det inte var tillåtet att röra sig så ska objektet som stöttes i få rörelsen istället
                it->set_forced_x_movement(it->get_forced_x_movement() + cover_pointer->get_forced_x_movement());
                it->set_forced_y_movement(it->get_forced_y_movement() + cover_pointer->get_forced_y_movement());
                it->set_explosion_movement_x(it->get_explosion_movement_x() + cover_pointer->get_explosion_movement_x() / explosion_transfer_loss);
                it->set_explosion_movement_y(it->get_explosion_movement_y() + cover_pointer->get_explosion_movement_y() / explosion_transfer_loss);
                cover_pointer->set_explosion_movement_x(cover_pointer->get_explosion_movement_x() / explosion_contact_movement_loss);
                cover_pointer->set_explosion_movement_y(cover_pointer->get_explosion_movement_y() / explosion_contact_movement_loss);
                return false;
            }
            {
                if(abs(corner2_in_new_base[0]-corner2_1[0]) + abs(corner2_in_new_base[0]-corner2_3[0]) <= abs(corner2_1[0]-corner2_3[0]) and
                        abs(corner2_in_new_base[1]-corner2_1[1]) + abs(corner2_in_new_base[1]-corner2_3[1]) <= abs(corner2_1[1]-corner2_3[1]))
                {
                    //Om det inte var tillåtet att röra sig så ska objektet som stöttes i få rörelsen istället
                    it->set_forced_x_movement(it->get_forced_x_movement() + cover_pointer->get_forced_x_movement());
                    it->set_forced_y_movement(it->get_forced_y_movement() + cover_pointer->get_forced_y_movement());
                    it->set_explosion_movement_x(it->get_explosion_movement_x() + cover_pointer->get_explosion_movement_x() / explosion_transfer_loss);
                    it->set_explosion_movement_y(it->get_explosion_movement_y() + cover_pointer->get_explosion_movement_y() / explosion_transfer_loss);
                    cover_pointer->set_explosion_movement_x(cover_pointer->get_explosion_movement_x() / explosion_contact_movement_loss);
                    cover_pointer->set_explosion_movement_y(cover_pointer->get_explosion_movement_y() / explosion_contact_movement_loss);
                    return false;
                }
                {
                    if(abs(corner3_in_new_base[0]-corner2_1[0]) + abs(corner3_in_new_base[0]-corner2_3[0]) <= abs(corner2_1[0]-corner2_3[0]) and
                            abs(corner3_in_new_base[1]-corner2_1[1]) + abs(corner3_in_new_base[1]-corner2_3[1]) <= abs(corner2_1[1]-corner2_3[1]))
                    {
                        //Om det inte var tillåtet att röra sig så ska objektet som stöttes i få rörelsen istället
                        it->set_forced_x_movement(it->get_forced_x_movement() + cover_pointer->get_forced_x_movement());
                        it->set_forced_y_movement(it->get_forced_y_movement() + cover_pointer->get_forced_y_movement());
                        it->set_explosion_movement_x(it->get_explosion_movement_x() + cover_pointer->get_explosion_movement_x() / explosion_transfer_loss);
                        it->set_explosion_movement_y(it->get_explosion_movement_y() + cover_pointer->get_explosion_movement_y() / explosion_transfer_loss);
                        cover_pointer->set_explosion_movement_x(cover_pointer->get_explosion_movement_x() / explosion_contact_movement_loss);
                        cover_pointer->set_explosion_movement_y(cover_pointer->get_explosion_movement_y() / explosion_contact_movement_loss);
                        return false;
                    }
                    {
                        if(abs(corner4_in_new_base[0]-corner2_1[0]) + abs(corner4_in_new_base[0]-corner2_3[0]) <= abs(corner2_1[0]-corner2_3[0]) and
                                abs(corner4_in_new_base[1]-corner2_1[1]) + abs(corner4_in_new_base[1]-corner2_3[1]) <= abs(corner2_1[1]-corner2_3[1]))
                        {
                            //Om det inte var tillåtet att röra sig så ska objektet som stöttes i få rörelsen istället
                            it->set_forced_x_movement(it->get_forced_x_movement() + cover_pointer->get_forced_x_movement());
                            it->set_forced_y_movement(it->get_forced_y_movement() + cover_pointer->get_forced_y_movement());
                            it->set_explosion_movement_x(it->get_explosion_movement_x() + cover_pointer->get_explosion_movement_x() / explosion_transfer_loss);
                            it->set_explosion_movement_y(it->get_explosion_movement_y() + cover_pointer->get_explosion_movement_y() / explosion_transfer_loss);
                            cover_pointer->set_explosion_movement_x(cover_pointer->get_explosion_movement_x() / explosion_contact_movement_loss);
                            cover_pointer->set_explosion_movement_y(cover_pointer->get_explosion_movement_y() / explosion_contact_movement_loss);
                            return false;
                        }
                    }
                }
            }

        }
    }


    return true;
}


/*Allowed_to_move_circle(double,double,int)
 * Beräknar huruvida en cirkels nya position är okej att flytta till.
 * Om cirkeln inte fick flytta sig till den nya position så påverkas det objekt som var ivägen på olika sätt,
 * t.ex. så överförs två krafter, en forced_movement och en explosion_movement som påverkar objektets rörelse på olika sätt
 *
 */
bool collision_handler::allowed_to_move_circle(double x_pos, double y_pos, int radius)
{
    //Kollar först så att cirkeln inte försöker smita ut från banan
    if(x_pos - radius < 0 or x_pos + radius > window_height or y_pos - radius < 0 or y_pos + radius > window_width)
        return false;


    //Nu ska vi kolla så att cirkeln inte kolliderar med några rektanglar ifrån cover_listan

    vector<cover>* cover_vector = gamefield_pointer->get_cover_vector();

    for(std::vector<cover>::iterator it = cover_vector->begin(); it != cover_vector->end(); ++it)
    {

        vector<double>corner_vector = it->get_corners(); //corner_vector är en vektor som innehåller rektangelns alla hörn

        //Cirkelns mittpunkt måste vara minst en radie ifrån varje hörn
        for(std::vector<double>::iterator it = corner_vector.begin(); it < corner_vector.end(); it = it + 2)
        {
            if(sqrt(pow((x_pos - *it),2) + pow(y_pos - *(it+1),2)) < radius)
                return false;
        }

        //Skapar en ON-bas där aktuell rektangel är parallell med basvektorerna
        double base_vector_v[2] = {corner_vector[2] - corner_vector[0], corner_vector[3] - corner_vector[1]}; //u2 uttryckt i basen x,y, x1->x2 och y1->y2
        double base_vector_u[2] = {corner_vector[4] - corner_vector[2], corner_vector[5] - corner_vector[3]}; //v2 uttryckt i basen x,y
        //Vi vill normera basvektorerna
        double normalize_u = sqrt(pow(base_vector_u[0],2) + pow(base_vector_u[1],2));
        double normalize_v = sqrt(pow(base_vector_v[0],2) + pow(base_vector_v[1],2));

        base_vector_u[0] = base_vector_u[0] / normalize_u;
        base_vector_u[1] = base_vector_u[1] / normalize_u;
        base_vector_v[0] = base_vector_v[0] / normalize_v;
        base_vector_v[1] = base_vector_v[1] / normalize_v;
        //Skapar en "basbytarmatris" för att lätt kunna byta bas från x,y till u,v.
        //Notera att eftersom baserna är normerade så är Ae->f = (Af->e)^-1 = (Af->e)^t
        double base_change_matrix[2][2] = {base_vector_u[0],base_vector_u[1],base_vector_v[0],base_vector_v[1]};

        //skriver om rektangelns mittpunkt till den nya basen
        double rectangle_position[2] = {it->get_xpos(), it->get_ypos()}; //Mittpunkten i gamla basen
        double rectangle_position_new[2];
        rectangle_position_new[0] = base_change_matrix[0][0]*rectangle_position[0] + base_change_matrix[0][1]*rectangle_position[1];
        rectangle_position_new[1] = base_change_matrix[1][0]*rectangle_position[0] + base_change_matrix[1][1]*rectangle_position[1];


        //Nu ska vi skriva cirkelns koordinater i den nya matrisen, detta görs enkelt med basbytarmatrisen
        double circle_position[2] = {x_pos,y_pos}; //cirkelns position i gamla basen
        double circle_position_new[2]; //cirkelns position i nya basen
        circle_position_new[0] = base_change_matrix[0][0]*circle_position[0] + base_change_matrix[0][1]*circle_position[1];
        circle_position_new[1] = base_change_matrix[1][0]*circle_position[0] + base_change_matrix[1][1]*circle_position[1];
        //circle_position innehåller nu cirkelns koordinater i den nya koordinaten


        //För att cirkeln inte ska kollidera med rektangeln så måste cirkeln vara halva höjden + radien ifrån cirkelns mitt
        //och halva bredden + radien ifrån cirkelns mitt i de riktningar som höjden och bredden avser, förutom
        //vid hörnen men det har redan tagits hand om ovan
        //Notera att bredden på rektangeln är utmed u vektorn och höjden utmed v vektorn
        if(abs(rectangle_position_new[0] - circle_position_new[0]) < it->get_width() + radius and abs(rectangle_position_new[1] - circle_position_new[1]) < it->get_height() + radius)
            return false;
    }
    //Kollision mot rektanglar ifrån cover_listan gjord, dags för karaktärer
    vector<character>* character_vector = gamefield_pointer->get_character_vector();
    for(std::vector<character>::iterator it = character_vector->begin(); it != character_vector->end(); ++it)
    {

        vector<double>corner_vector = it->get_corners(); //corner_vector är en vektor som innehåller rektangelns alla hörn

        //Cirkelns mittpunkt måste vara minst en radie ifrån varje hörn
        for(std::vector<double>::iterator it = corner_vector.begin(); it < corner_vector.end(); it = it + 2)
        {
            if(sqrt(pow((x_pos - *it),2) + pow(y_pos - *(it+1),2)) < radius)
                return false;
        }

        //Skapar en ON-bas där aktuell rektangel är parallell med basvektorerna
        double base_vector_v[2] = {corner_vector[2] - corner_vector[0], corner_vector[3] - corner_vector[1]}; //u2 uttryckt i basen x,y, x1->x2 och y1->y2
        double base_vector_u[2] = {corner_vector[4] - corner_vector[2], corner_vector[5] - corner_vector[3]}; //v2 uttryckt i basen x,y
        //Vi vill normera basvektorerna
        double normalize_u = sqrt(pow(base_vector_u[0],2) + pow(base_vector_u[1],2));
        double normalize_v = sqrt(pow(base_vector_v[0],2) + pow(base_vector_v[1],2));

        base_vector_u[0] = base_vector_u[0] / normalize_u;
        base_vector_u[1] = base_vector_u[1] / normalize_u;
        base_vector_v[0] = base_vector_v[0] / normalize_v;
        base_vector_v[1] = base_vector_v[1] / normalize_v;
        //Skapar en "basbytarmatris" för att lätt kunna byta bas från x,y till u,v.
        //Notera att eftersom baserna är normerade så är Ae->f = (Af->e)^-1 = (Af->e)^t
        double base_change_matrix[2][2] = {base_vector_u[0],base_vector_u[1],base_vector_v[0],base_vector_v[1]};

        //skriver om rektangelns mittpunkt till den nya basen
        double rectangle_position[2] = {it->get_xpos(), it->get_ypos()}; //Mittpunkten i gamla basen
        double rectangle_position_new[2];
        rectangle_position_new[0] = base_change_matrix[0][0]*rectangle_position[0] + base_change_matrix[0][1]*rectangle_position[1];
        rectangle_position_new[1] = base_change_matrix[1][0]*rectangle_position[0] + base_change_matrix[1][1]*rectangle_position[1];


        //Nu ska vi skriva cirkelns koordinater i den nya matrisen, detta görs enkelt med basbytarmatrisen
        double circle_position[2] = {x_pos,y_pos}; //cirkelns position i gamla basen
        double circle_position_new[2]; //cirkelns position i nya basen
        circle_position_new[0] = base_change_matrix[0][0]*circle_position[0] + base_change_matrix[0][1]*circle_position[1];
        circle_position_new[1] = base_change_matrix[1][0]*circle_position[0] + base_change_matrix[1][1]*circle_position[1];
        //circle_position innehåller nu cirkelns koordinater i den nya koordinaten


        //För att cirkeln inte ska kollidera med rektangeln så måste cirkeln vara halva höjden + radien ifrån cirkelns mitt
        //och halva bredden + radien ifrån cirkelns mitt i de riktningar som höjden och bredden avser, förutom
        //vid hörnen men det har redan tagits hand om ovan
        //Notera att bredden på rektangeln är utmed u vektorn och höjden utmed v vektorn
        if(abs(rectangle_position_new[0] - circle_position_new[0]) < it->get_width() + radius and abs(rectangle_position_new[1] - circle_position_new[1]) < it->get_height() + radius)
            return false;
    }
    return true;
}

/*Allowed_to_move_bullet(vector<double>,character*)
 * Var tänkt att bara användas av kulor men användes sedan av alla projektiler för enkelhets skull,
 * behandlar projektilen som en punkt och testar om linjen ifrån dess föregående position till dess nya skär
 * någon linje som ej är tillåten att skära.
 * För missilen och kulan medför en kollision att objektet den kolliderar med tar skada
 * Granatar ska istället för att göra skada på föremålet den träffar studsa mot det.
 */
bool collision_handler::allowed_to_move_bullet(double x_before, double y_before, double x_after, double y_after, bool move_trought_covers, double bullet_speed, double bullet_damage, class character* owner_pointer, class projectile* projectile_pointer)
{   //Kollar först så att inte kulan försöker åka utanför banan, om ja returnera false den!

    //Delar upp i alla olika fall så att studsen ska bli rätt

    if(x_after <= 0 or x_after >=window_width)
    {
        //Som lägget är nu så ska vissa projektiler studsa mot objekt de inte kan röra sig igenom och deras nuvarande position är den som kontrollerades om de kunde flytta till
        //Så vi behöver till en början ändra tillbaka deras position till den senaste godkända positionen
        projectile_pointer->set_x_position(projectile_pointer->get_xpos() - projectile_pointer->get_x_movement());
        projectile_pointer->set_y_position(projectile_pointer->get_ypos() - projectile_pointer ->get_y_movement());
        projectile_pointer->set_x_movement(-projectile_pointer->get_x_movement());
        return false;
    }
    if(y_after <= 0 or y_after >= window_height)
    {
        //Som lägget är nu så ska vissa projektiler studsa mot objekt de inte kan röra sig igenom och deras nuvarande position är den som kontrollerades om de kunde flytta till
        //Så vi behöver till en början ändra tillbaka deras position till den senaste godkända positionen
        projectile_pointer->set_x_position(projectile_pointer->get_xpos() - projectile_pointer->get_x_movement());
        projectile_pointer->set_y_position(projectile_pointer->get_ypos() - projectile_pointer ->get_y_movement());
        projectile_pointer->set_y_movement(-projectile_pointer->get_y_movement());
        return false;
    }
    if(!move_trought_covers)
    {
        //Används i kollisionshanteringen senare, t och s är parametrar för riktningsvektorer
        double t;
        double s;
        double bullet_vector[2] = {x_after - x_before, y_after - y_before};

        vector<cover>* cover_vector = gamefield_pointer->get_cover_vector(); //Hämtar listan med covers i
        for(std::vector<cover>::iterator it = cover_vector->begin(); it != cover_vector->end(); ++it)
        {
            vector<double>corner_vector = it->get_corners();

            //Vektorer mellan hörnen i ordning 1->2,2->3,3->4,4->1
            double corner1_corner2[2] ={corner_vector[2]-corner_vector[0], corner_vector[3] - corner_vector[1]};
            double corner2_corner3[2] ={corner_vector[4]-corner_vector[2], corner_vector[5] - corner_vector[3]};
            double corner3_corner4[2] ={corner_vector[6]-corner_vector[4], corner_vector[7] - corner_vector[5]};
            double corner4_corner1[2] ={corner_vector[0]-corner_vector[6], corner_vector[1] - corner_vector[7]};
            //Onödigt att kolla kollision mot varje rektangel, väljer bara de som befinner sig relativt nära
            //Denna vektor är diagonalen på vektorn, ifrån andra hörnet till 4.
            double help_vector_rec[2] = {corner_vector[2] - corner_vector[6], corner_vector[3] - corner_vector[7]};

            //Längden av diagonalen
            double length_dia = sqrt(pow(help_vector_rec[0],2) + pow(help_vector_rec[1],2));

            //Längden mellan rektanglen och kulan
            double length_between_midpoints = sqrt(pow(x_before - (corner_vector[6] + help_vector_rec[0]/2),2) + pow(y_before - (corner_vector[7] + help_vector_rec[1]/2),2));
            //Kommer alltså bara att kolla på kollision för covers som ligger närmare än avståndet mellan mittpunkten på rektangeln och kulan + kulans hastighet + 1
            if(length_dia + bullet_speed + 1 >= length_between_midpoints)
            {
                //Det är onödigt att kolla om kulan går över alla sidor på rektangeln när det räcker med att kontrollera de 2 närmaste sidorna, de 2 närmaste sidorna
                //är de som båda har hörnet som ligger närmast kulan.
                //Således kontrolleras olika sidor beroende på vilket hörn som ligger närmast

                //Avstånden mellan varje hörn och kulamn
                double distance_corner_1 = sqrt(pow(corner_vector.at(0) - x_before,2) + pow(corner_vector.at(1) - y_before,2));
                double distance_corner_2 = sqrt(pow(corner_vector.at(2) - x_before,2) + pow(corner_vector.at(3) - y_before,2));
                double distance_corner_3 = sqrt(pow(corner_vector.at(4) - x_before,2) + pow(corner_vector.at(5) - y_before,2));
                double distance_corner_4 = sqrt(pow(corner_vector.at(6) - x_before,2) + pow(corner_vector.at(7) - y_before,2));
                //Om hörn 1 ligger närmast, notera att om kulan ligger lika långt ifrån två hörn så spelar det ingen roll vilket hörn som väljs som närmst.
                if(distance_corner_1 <= distance_corner_2 and distance_corner_1 <= distance_corner_3 and distance_corner_1 <= distance_corner_4)
                {
                    //Om hörn 1 ligger närmst ska vi kontrollera mot sidorna med hörn1-hörn2 och hörn1-hörn4
                    //Kollisionen kontrolleras på det sätt att man löser ekvationen för när linjen som sträcker sig utmed kulans pos. innan till efter
                    // med just den riktningsvektorn skär med linjen som går utmed hörn1->hörn2 och hörn1->hörn4 med just de riktningsvektorerna, om
                    // någon av ekvationerna löses med en parameter mellan 0-1 på bägge riktningsvektorer så är det en kollision.
                    // Lösningen på riktnigsparametrarna ges genom följande ekvation (erhållen från Wolfram Alpha)

                    //Börjar med hörn4->hörn1
                    if(bullet_vector[0]*corner4_corner1[1]-bullet_vector[1]*corner4_corner1[0] != 0)//Kontrollerar först så att kulan inte rör sig parallellt med kanten, om ja->EJ KOLLISION
                    {
                        //Dessa lösningar är alltså tagna direkt ifrån wolframalpha
                        t = (corner4_corner1[0]*corner_vector[7] - corner4_corner1[0]*y_before - corner4_corner1[1]*corner_vector[6] + corner4_corner1[1]*x_before)
                                / (bullet_vector[1]*corner4_corner1[0]-bullet_vector[0]*corner4_corner1[1]);

                        s = (bullet_vector[0]*corner_vector[7] - bullet_vector[0]*y_before - bullet_vector[1]*corner_vector[6] + bullet_vector[1]*x_before)
                                / (bullet_vector[1]*corner4_corner1[0] - bullet_vector[0]*corner4_corner1[1]);
                        if(t >= 0 and t <= 1 and s >= 0 and s <= 1) //Om bägge parametrar är mellan 0-1 så skedde en kollision
                        {
                            if(projectile_pointer->get_name() != "grenade")//Om projektilen är en kula så ska kulan göra skada, för de andra projektilerna är det explosionen som gör skada
                                it->set_health(it->get_health() - bullet_damage); //Kulan gör skada på skyddet

                            if(projectile_pointer->get_name() == "grenade") //Om projektilen är en granat så ska den studsa på skyddet
                            {
                                //Sätter tillbaka position till den senaste tillåtna
                                projectile_pointer->set_x_position(projectile_pointer->get_xpos() - projectile_pointer->get_x_movement());
                                projectile_pointer->set_y_position(projectile_pointer->get_ypos() - projectile_pointer->get_y_movement());
                                //Projicerar  bullet_vector på hörn4->hörn1 vektorn
                                double help_movement_vector[2] = {(bullet_vector[0]*corner4_corner1[0] + bullet_vector[1]*corner4_corner1[1])*corner4_corner1[0],(bullet_vector[0]*corner4_corner1[0] + bullet_vector[1]*corner4_corner1[1])*corner4_corner1[1]};
                                help_movement_vector[0] = help_movement_vector[0] / (pow(corner4_corner1[0],2) + pow(corner4_corner1[1],2));
                                help_movement_vector[1] = help_movement_vector[1] / (pow(corner4_corner1[0],2) + pow(corner4_corner1[1],2));

                                //Skapar den nya riktningsvektorn som granaten ska ha
                                double new_movement_vector[2] = {2*help_movement_vector[0] - bullet_vector[0], 2*help_movement_vector[1] - bullet_vector[1]};
                                projectile_pointer->set_x_movement(new_movement_vector[0]);
                                projectile_pointer->set_y_movement(new_movement_vector[1]);
                            }
                            return false;
                        }
                    }

                    //Dags för hörn1->hörn2
                    if(bullet_vector[0]*corner1_corner2[1]-bullet_vector[1]*corner1_corner2[0] != 0)//Kontrollerar först så att kulan inte rör sig parallellt med kanten, om ja->EJ KOLLISION
                    {
                        //Dessa lösningar är alltså tagna direkt ifrån wolframalpha
                        t = (corner1_corner2[0]*corner_vector[1] - corner1_corner2[0]*y_before - corner1_corner2[1]*corner_vector[0] + corner1_corner2[1]*x_before)
                                / (bullet_vector[1]*corner1_corner2[0]-bullet_vector[0]*corner1_corner2[1]);

                        s = (bullet_vector[0]*corner_vector[1] - bullet_vector[0]*y_before - bullet_vector[1]*corner_vector[0] + bullet_vector[1]*x_before)
                                / (bullet_vector[1]*corner1_corner2[0] - bullet_vector[0]*corner1_corner2[1]);
                        if(t >= 0 and t <= 1 and s >= 0 and s <= 1) //Om bägge parametrar är mellan 0-1 så skedde en kollision
                        {
                            if(projectile_pointer->get_name() != "grenade")//Om projektilen är en kula så ska kulan göra skada, för de andra projektilerna är det explosionen som gör skada
                                it->set_health(it->get_health() - bullet_damage); //Kulan gör skada på skyddet

                            if(projectile_pointer->get_name() == "grenade") //Om projektilen är en granat så ska den studsa på skyddet
                            {
                                //Sätter tillbaka position till den senaste tillåtna
                                projectile_pointer->set_x_position(projectile_pointer->get_xpos() - projectile_pointer->get_x_movement());
                                projectile_pointer->set_y_position(projectile_pointer->get_ypos() - projectile_pointer->get_y_movement());
                                //Projicerar  bullet_vector på hörn1->hörn2 vektorn
                                double help_movement_vector[2] = {(bullet_vector[0]*corner1_corner2[0] + bullet_vector[1]*corner1_corner2[1])*corner1_corner2[0],(bullet_vector[0]*corner1_corner2[0] + bullet_vector[1]*corner1_corner2[1])*corner1_corner2[1]};
                                help_movement_vector[0] = help_movement_vector[0] / (pow(corner1_corner2[0],2) + pow(corner1_corner2[1],2));
                                help_movement_vector[1] = help_movement_vector[1] / (pow(corner1_corner2[0],2) + pow(corner1_corner2[1],2));

                                //Skapar den nya riktningsvektorn som granaten ska ha
                                double new_movement_vector[2] = {2*help_movement_vector[0] - bullet_vector[0], 2*help_movement_vector[1] - bullet_vector[1]};
                                projectile_pointer->set_x_movement(new_movement_vector[0]);
                                projectile_pointer->set_y_movement(new_movement_vector[1]);
                            }
                            return false;

                        }
                    }

                }



                //Om hörn 2 ligger närmast, notera att om kulan ligger lika långt ifrån två hörn så spelar det ingen roll vilket hörn som väljs som närmst.
                if(distance_corner_2 <= distance_corner_1 and distance_corner_2 <= distance_corner_3 and distance_corner_2 <= distance_corner_4)
                {
                    //Om hörn 2 ligger närmst ska vi kontrollera mot sidorna med hörn1-hörn2 och hörn2-hörn3
                    //Kollisionen kontrolleras på det sätt att man löser ekvationen för när linjen som sträcker sig utmed kulans pos. innan till efter
                    // med just den riktningsvektorn skär med linjen som går utmed hörn1->hörn2 och hörn1->hörn4 med just de riktningsvektorerna, om
                    // någon av ekvationerna löses med en parameter mellan 0-1 på bägge riktningsvektorer så är det en kollision.
                    // Lösningen på riktnigsparametrarna ges genom följande ekvation (erhållen från Wolfram Alpha)

                    //Börjar med hörn2->hörn3
                    if(bullet_vector[0]*corner2_corner3[1]-bullet_vector[1]*corner2_corner3[0] != 0)//Kontrollerar först så att kulan inte rör sig parallellt med kanten, om ja->EJ KOLLISION
                    {
                        //Dessa lösningar är alltså tagna direkt ifrån wolframalpha
                        t = (corner2_corner3[0]*corner_vector[3] - corner2_corner3[0]*y_before - corner2_corner3[1]*corner_vector[2] + corner2_corner3[1]*x_before)
                                / (bullet_vector[1]*corner2_corner3[0]-bullet_vector[0]*corner2_corner3[1]);

                        s = (bullet_vector[0]*corner_vector[3] - bullet_vector[0]*y_before - bullet_vector[1]*corner_vector[2] + bullet_vector[1]*x_before)
                                / (bullet_vector[1]*corner2_corner3[0] - bullet_vector[0]*corner2_corner3[1]);
                        if(t >= 0 and t <= 1 and s >= 0 and s <= 1) //Om bägge parametrar är mellan 0-1 så skedde en kollision
                        {
                            if(projectile_pointer->get_name() != "grenade")//Om projektilen är en kula så ska kulan göra skada, för de andra projektilerna är det explosionen som gör skada
                                it->set_health(it->get_health() - bullet_damage); //Kulan gör skada på skyddet

                            if(projectile_pointer->get_name() == "grenade") //Om projektilen är en granat så ska den studsa på skyddet
                            {
                                //Sätter tillbaka position till den senaste tillåtna
                                projectile_pointer->set_x_position(projectile_pointer->get_xpos() - projectile_pointer->get_x_movement());
                                projectile_pointer->set_y_position(projectile_pointer->get_ypos() - projectile_pointer->get_y_movement());
                                //Projicerar  bullet_vector på hörn2->hörn3 vektorn
                                double help_movement_vector[2] = {(bullet_vector[0]*corner2_corner3[0] + bullet_vector[1]*corner2_corner3[1])*corner2_corner3[0],(bullet_vector[0]*corner2_corner3[0] + bullet_vector[1]*corner2_corner3[1])*corner2_corner3[1]};
                                help_movement_vector[0] = help_movement_vector[0] / (pow(corner2_corner3[0],2) + pow(corner2_corner3[1],2));
                                help_movement_vector[1] = help_movement_vector[1] / (pow(corner2_corner3[0],2) + pow(corner2_corner3[1],2));

                                //Skapar den nya riktningsvektorn som granaten ska ha
                                double new_movement_vector[2] = {2*help_movement_vector[0] - bullet_vector[0], 2*help_movement_vector[1] - bullet_vector[1]};
                                projectile_pointer->set_x_movement(new_movement_vector[0]);
                                projectile_pointer->set_y_movement(new_movement_vector[1]);
                            }
                            return false;
                        }
                    }

                    //Dags för hörn1->hörn2
                    if(bullet_vector[0]*corner1_corner2[1]-bullet_vector[1]*corner1_corner2[0] != 0)//Kontrollerar först så att kulan inte rör sig parallellt med kanten, om ja->EJ KOLLISION
                    {
                        //Dessa lösningar är alltså tagna direkt ifrån wolframalpha
                        t = (corner1_corner2[0]*corner_vector[1] - corner1_corner2[0]*y_before - corner1_corner2[1]*corner_vector[0] + corner1_corner2[1]*x_before)
                                / (bullet_vector[1]*corner1_corner2[0]-bullet_vector[0]*corner1_corner2[1]);

                        s = (bullet_vector[0]*corner_vector[1] - bullet_vector[0]*y_before - bullet_vector[1]*corner_vector[0] + bullet_vector[1]*x_before)
                                / (bullet_vector[1]*corner1_corner2[0] - bullet_vector[0]*corner1_corner2[1]);
                        if(t >= 0 and t <= 1 and s >= 0 and s <= 1) //Om bägge parametrar är mellan 0-1 så skedde en kollision
                        {
                            if(projectile_pointer->get_name() != "grenade")//Om projektilen är en kula så ska kulan göra skada, för de andra projektilerna är det explosionen som gör skada
                                it->set_health(it->get_health() - bullet_damage); //Kulan gör skada på skyddet

                            if(projectile_pointer->get_name() == "grenade") //Om projektilen är en granat så ska den studsa på skyddet
                            {
                                //Sätter tillbaka position till den senaste tillåtna
                                projectile_pointer->set_x_position(projectile_pointer->get_xpos() - projectile_pointer->get_x_movement());
                                projectile_pointer->set_y_position(projectile_pointer->get_ypos() - projectile_pointer->get_y_movement());
                                //Projicerar  bullet_vector på hörn1->hörn2 vektorn
                                double help_movement_vector[2] = {(bullet_vector[0]*corner1_corner2[0] + bullet_vector[1]*corner1_corner2[1])*corner1_corner2[0],(bullet_vector[0]*corner1_corner2[0] + bullet_vector[1]*corner1_corner2[1])*corner1_corner2[1]};
                                help_movement_vector[0] = help_movement_vector[0] / (pow(corner1_corner2[0],2) + pow(corner1_corner2[1],2));
                                help_movement_vector[1] = help_movement_vector[1] / (pow(corner1_corner2[0],2) + pow(corner1_corner2[1],2));

                                //Skapar den nya riktningsvektorn som granaten ska ha
                                double new_movement_vector[2] = {2*help_movement_vector[0] - bullet_vector[0], 2*help_movement_vector[1] - bullet_vector[1]};
                                projectile_pointer->set_x_movement(new_movement_vector[0]);
                                projectile_pointer->set_y_movement(new_movement_vector[1]);
                            }
                            return false;

                        }
                    }



                }
                //Om hörn 3 ligger närmast:
                if(distance_corner_3 <= distance_corner_2 and distance_corner_3 <= distance_corner_1 and distance_corner_3 <= distance_corner_4)
                {
                    //Börjar med hörn 3->4:
                    if(bullet_vector[0]*corner3_corner4[1]-bullet_vector[1]*corner3_corner4[0] != 0)//Kontrollerar först så att kulan inte rör sig parallellt med kanten, om ja->EJ KOLLISION
                    {
                        //Dessa lösningar är alltså tagna direkt ifrån wolframalpha
                        t = (corner3_corner4[0]*corner_vector[5] - corner3_corner4[0]*y_before - corner3_corner4[1]*corner_vector[4] + corner3_corner4[1]*x_before)
                                / (bullet_vector[1]*corner3_corner4[0]-bullet_vector[0]*corner3_corner4[1]);

                        s = (bullet_vector[0]*corner_vector[5] - bullet_vector[0]*y_before - bullet_vector[1]*corner_vector[4] + bullet_vector[1]*x_before)
                                / (bullet_vector[1]*corner3_corner4[0] - bullet_vector[0]*corner3_corner4[1]);
                        if(t >= 0 and t <= 1 and s >= 0 and s <= 1) //Om bägge parametrar är mellan 0-1 så skedde en kollision
                        {
                            if(projectile_pointer->get_name() != "grenade")//Om projektilen är en kula så ska kulan göra skada, för de andra projektilerna är det explosionen som gör skada
                                it->set_health(it->get_health() - bullet_damage); //Kulan gör skada på skyddet

                            if(projectile_pointer->get_name() == "grenade") //Om projektilen är en granat så ska den studsa på skyddet
                            {
                                //Sätter tillbaka position till den senaste tillåtna
                                projectile_pointer->set_x_position(projectile_pointer->get_xpos() - projectile_pointer->get_x_movement());
                                projectile_pointer->set_y_position(projectile_pointer->get_ypos() - projectile_pointer->get_y_movement());
                                //Projicerar  bullet_vector på hörn3->hörn4 vektorn
                                double help_movement_vector[2] = {(bullet_vector[0]*corner3_corner4[0] + bullet_vector[1]*corner3_corner4[1])*corner3_corner4[0],(bullet_vector[0]*corner3_corner4[0] + bullet_vector[1]*corner3_corner4[1])*corner3_corner4[1]};
                                help_movement_vector[0] = help_movement_vector[0] / (pow(corner3_corner4[0],2) + pow(corner3_corner4[1],2));
                                help_movement_vector[1] = help_movement_vector[1] / (pow(corner3_corner4[0],2) + pow(corner3_corner4[1],2));

                                //Skapar den nya riktningsvektorn som granaten ska ha
                                double new_movement_vector[2] = {2*help_movement_vector[0] - bullet_vector[0], 2*help_movement_vector[1] - bullet_vector[1]};
                                projectile_pointer->set_x_movement(new_movement_vector[0]);
                                projectile_pointer->set_y_movement(new_movement_vector[1]);
                            }
                            return false;
                        }
                    }
                    //dags för hörn 2->3:
                    if(bullet_vector[0]*corner2_corner3[1]-bullet_vector[1]*corner2_corner3[0] != 0)//Kontrollerar först så att kulan inte rör sig parallellt med kanten, om ja->EJ KOLLISION
                    {
                        //Dessa lösningar är alltså tagna direkt ifrån wolframalpha
                        t = (corner2_corner3[0]*corner_vector[3] - corner2_corner3[0]*y_before - corner2_corner3[1]*corner_vector[2] + corner2_corner3[1]*x_before)
                                / (bullet_vector[1]*corner2_corner3[0]-bullet_vector[0]*corner2_corner3[1]);

                        s = (bullet_vector[0]*corner_vector[3] - bullet_vector[0]*y_before - bullet_vector[1]*corner_vector[2] + bullet_vector[1]*x_before)
                                / (bullet_vector[1]*corner2_corner3[0] - bullet_vector[0]*corner2_corner3[1]);
                        if(t >= 0 and t <= 1 and s >= 0 and s <= 1) //Om bägge parametrar är mellan 0-1 så skedde en kollision
                        {
                            if(projectile_pointer->get_name() != "grenade")//Om projektilen är en kula så ska kulan göra skada, för de andra projektilerna är det explosionen som gör skada
                                it->set_health(it->get_health() - bullet_damage); //Kulan gör skada på skyddet

                            if(projectile_pointer->get_name() == "grenade") //Om projektilen är en granat så ska den studsa på skyddet
                            {
                                //Sätter tillbaka position till den senaste tillåtna
                                projectile_pointer->set_x_position(projectile_pointer->get_xpos() - projectile_pointer->get_x_movement());
                                projectile_pointer->set_y_position(projectile_pointer->get_ypos() - projectile_pointer->get_y_movement());
                                //Projicerar  bullet_vector på hörn2->hörn3 vektorn
                                double help_movement_vector[2] = {(bullet_vector[0]*corner2_corner3[0] + bullet_vector[1]*corner2_corner3[1])*corner2_corner3[0],(bullet_vector[0]*corner2_corner3[0] + bullet_vector[1]*corner2_corner3[1])*corner2_corner3[1]};
                                help_movement_vector[0] = help_movement_vector[0] / (pow(corner2_corner3[0],2) + pow(corner2_corner3[1],2));
                                help_movement_vector[1] = help_movement_vector[1] / (pow(corner2_corner3[0],2) + pow(corner2_corner3[1],2));

                                //Skapar den nya riktningsvektorn som granaten ska ha
                                double new_movement_vector[2] = {2*help_movement_vector[0] - bullet_vector[0], 2*help_movement_vector[1] - bullet_vector[1]};
                                projectile_pointer->set_x_movement(new_movement_vector[0]);
                                projectile_pointer->set_y_movement(new_movement_vector[1]);
                            }
                            return false;}
                    }
                }
                //Om hörn 4 ligger närmast:
                if(distance_corner_4 <= distance_corner_2 and distance_corner_4 <= distance_corner_1 and distance_corner_4 <= distance_corner_3)
                {
                    //Börjar med hörn 4->1:
                    if(bullet_vector[0]*corner4_corner1[1]-bullet_vector[1]*corner4_corner1[0] != 0)//Kontrollerar först så att kulan inte rör sig parallellt med kanten, om ja->EJ KOLLISION
                    {
                        //Dessa lösningar är alltså tagna direkt ifrån wolframalpha
                        t = (corner4_corner1[0]*corner_vector[7] - corner4_corner1[0]*y_before - corner4_corner1[1]*corner_vector[6] + corner4_corner1[1]*x_before)
                                / (bullet_vector[1]*corner4_corner1[0]-bullet_vector[0]*corner4_corner1[1]);

                        s = (bullet_vector[0]*corner_vector[7] - bullet_vector[0]*y_before - bullet_vector[1]*corner_vector[6] + bullet_vector[1]*x_before)
                                / (bullet_vector[1]*corner4_corner1[0] - bullet_vector[0]*corner4_corner1[1]);
                        if(t >= 0 and t <= 1 and s >= 0 and s <= 1) //Om bägge parametrar är mellan 0-1 så skedde en kollision
                        {
                            if(projectile_pointer->get_name() != "grenade")//Om projektilen är en kula så ska kulan göra skada, för de andra projektilerna är det explosionen som gör skada
                                it->set_health(it->get_health() - bullet_damage); //Kulan gör skada på skyddet

                            if(projectile_pointer->get_name() == "grenade") //Om projektilen är en granat så ska den studsa på skyddet
                            {

                                //Sätter tillbaka position till den senaste tillåtna
                                projectile_pointer->set_x_position(projectile_pointer->get_xpos() - projectile_pointer->get_x_movement());
                                projectile_pointer->set_y_position(projectile_pointer->get_ypos() - projectile_pointer->get_y_movement());
                                //Projicerar  bullet_vector på hörn4->hörn1 vektorn
                                double help_movement_vector[2] = {(bullet_vector[0]*corner4_corner1[0] + bullet_vector[1]*corner4_corner1[1])*corner4_corner1[0],(bullet_vector[0]*corner4_corner1[0] + bullet_vector[1]*corner4_corner1[1])*corner4_corner1[1]};
                                help_movement_vector[0] = help_movement_vector[0] / (pow(corner4_corner1[0],2) + pow(corner4_corner1[1],2));
                                help_movement_vector[1] = help_movement_vector[1] / (pow(corner4_corner1[0],2) + pow(corner4_corner1[1],2));

                                //Skapar den nya riktningsvektorn som granaten ska ha
                                double new_movement_vector[2] = {2*help_movement_vector[0] - bullet_vector[0], 2*help_movement_vector[1] - bullet_vector[1]};
                                projectile_pointer->set_x_movement(new_movement_vector[0]);
                                projectile_pointer->set_y_movement(new_movement_vector[1]);
                            }
                            return false;
                        }
                    }
                    //Dags för hörn 3->4:
                    if(bullet_vector[0]*corner3_corner4[1]-bullet_vector[1]*corner3_corner4[0] != 0)//Kontrollerar först så att kulan inte rör sig parallellt med kanten, om ja->EJ KOLLISION
                    {
                        //Dessa lösningar är alltså tagna direkt ifrån wolframalpha
                        t = (corner3_corner4[0]*corner_vector[5] - corner3_corner4[0]*y_before - corner3_corner4[1]*corner_vector[4] + corner3_corner4[1]*x_before)
                                / (bullet_vector[1]*corner3_corner4[0]-bullet_vector[0]*corner3_corner4[1]);

                        s = (bullet_vector[0]*corner_vector[5] - bullet_vector[0]*y_before - bullet_vector[1]*corner_vector[4] + bullet_vector[1]*x_before)
                                / (bullet_vector[1]*corner3_corner4[0] - bullet_vector[0]*corner3_corner4[1]);
                        if(t >= 0 and t <= 1 and s >= 0 and s <= 1) //Om bägge parametrar är mellan 0-1 så skedde en kollision
                        {
                            if(projectile_pointer->get_name() != "grenade")//Om projektilen är en kula så ska kulan göra skada, för de andra projektilerna är det explosionen som gör skada
                                it->set_health(it->get_health() - bullet_damage); //Kulan gör skada på skyddet

                            if(projectile_pointer->get_name() == "grenade") //Om projektilen är en granat så ska den studsa på skyddet
                            {
                                //Sätter tillbaka position till den senaste tillåtna
                                projectile_pointer->set_x_position(projectile_pointer->get_xpos() - projectile_pointer->get_x_movement());
                                projectile_pointer->set_y_position(projectile_pointer->get_ypos() - projectile_pointer->get_y_movement());
                                //Projicerar  bullet_vector på hörn3->hörn4 vektorn
                                double help_movement_vector[2] = {(bullet_vector[0]*corner3_corner4[0] + bullet_vector[1]*corner3_corner4[1])*corner3_corner4[0],(bullet_vector[0]*corner3_corner4[0] + bullet_vector[1]*corner3_corner4[1])*corner3_corner4[1]};
                                help_movement_vector[0] = help_movement_vector[0] / (pow(corner3_corner4[0],2) + pow(corner3_corner4[1],2));
                                help_movement_vector[1] = help_movement_vector[1] / (pow(corner3_corner4[0],2) + pow(corner3_corner4[1],2));

                                //Skapar den nya riktningsvektorn som granaten ska ha
                                double new_movement_vector[2] = {2*help_movement_vector[0] - bullet_vector[0], 2*help_movement_vector[1] - bullet_vector[1]};
                                projectile_pointer->set_x_movement(new_movement_vector[0]);
                                projectile_pointer->set_y_movement(new_movement_vector[1]);
                            }
                            return false;
                        }
                    }
                }
            }
        }






        //Nu är det dags för kollision mot karaktärerna
        vector<character>* character_vector = gamefield_pointer->get_character_vector(); //Hämtar listan med covers i
        for(std::vector<character>::iterator it = character_vector->begin(); it != character_vector->end(); ++it)
        {
            vector<double>corner_vector = it->get_corners();
            //Vektorer mellan hörnen i ordning 1->2,2->3,3->4,4->1
            double corner1_corner2[2] ={corner_vector[2]-corner_vector[0], corner_vector[3] - corner_vector[1]};
            double corner2_corner3[2] ={corner_vector[4]-corner_vector[2], corner_vector[5] - corner_vector[3]};
            double corner3_corner4[2] ={corner_vector[6]-corner_vector[4], corner_vector[7] - corner_vector[5]};
            double corner4_corner1[2] ={corner_vector[0]-corner_vector[6], corner_vector[1] - corner_vector[7]};

            //Börjar med hörn4->hörn1
            if(bullet_vector[0]*corner4_corner1[1]-bullet_vector[1]*corner4_corner1[0] != 0)//Kontrollerar först så att kulan inte rör sig parallellt med kanten, om ja->EJ KOLLISION
            {
                //Dessa lösningar är alltså tagna direkt ifrån wolframalpha
                t = (corner4_corner1[0]*corner_vector[7] - corner4_corner1[0]*y_before - corner4_corner1[1]*corner_vector[6] + corner4_corner1[1]*x_before)
                        / (bullet_vector[1]*corner4_corner1[0]-bullet_vector[0]*corner4_corner1[1]);

                s = (bullet_vector[0]*corner_vector[7] - bullet_vector[0]*y_before - bullet_vector[1]*corner_vector[6] + bullet_vector[1]*x_before)
                        / (bullet_vector[1]*corner4_corner1[0] - bullet_vector[0]*corner4_corner1[1]);
                if(t >= 0 and t <= 1 and s >= 0 and s <= 1) //Om bägge parametrar är mellan 0-1 så skedde en kollision
                {
                    if(it->get_pointer_to_yourself()!=owner_pointer)//Kollar så att kollisionen inte var mot spelaren som avfyrade skottet
                    {
                        if(projectile_pointer->get_name() != "grenade")//Om projektilen är en kula så ska kulan göra skada, för de andra projektilerna är det explosionen som gör skada
                            it->set_health(it->get_health() - bullet_damage); //Kulan gör skada på skyddet

                        if(projectile_pointer->get_name() == "grenade") //Om projektilen är en granat så ska den studsa på skyddet
                        {
                            //Sätter tillbaka position till den senaste tillåtna
                            projectile_pointer->set_x_position(projectile_pointer->get_xpos() - projectile_pointer->get_x_movement());
                            projectile_pointer->set_y_position(projectile_pointer->get_ypos() - projectile_pointer->get_y_movement());
                            //Projicerar  bullet_vector på hörn4->hörn1 vektorn
                            double help_movement_vector[2] = {(bullet_vector[0]*corner4_corner1[0] + bullet_vector[1]*corner4_corner1[1])*corner4_corner1[0],(bullet_vector[0]*corner4_corner1[0] + bullet_vector[1]*corner4_corner1[1])*corner2_corner3[1]};
                            help_movement_vector[0] = help_movement_vector[0] / (pow(corner4_corner1[0],2) + pow(corner4_corner1[1],2));
                            help_movement_vector[1] = help_movement_vector[1] / (pow(corner4_corner1[0],2) + pow(corner4_corner1[1],2));

                            //Skapar den nya riktningsvektorn som granaten ska ha
                            double new_movement_vector[2] = {2*help_movement_vector[0] - bullet_vector[0], 2*help_movement_vector[1] - bullet_vector[1]};
                            projectile_pointer->set_x_movement(new_movement_vector[0]);
                            projectile_pointer->set_y_movement(new_movement_vector[1]);
                        }
                        return false;
                    }
                }
            }


            //Dags för hörn1->hörn2
            if(bullet_vector[0]*corner1_corner2[1]-bullet_vector[1]*corner1_corner2[0] != 0)//Kontrollerar först så att kulan inte rör sig parallellt med kanten, om ja->EJ KOLLISION
            {
                //Dessa lösningar är alltså tagna direkt ifrån wolframalpha
                t = (corner1_corner2[0]*corner_vector[1] - corner1_corner2[0]*y_before - corner1_corner2[1]*corner_vector[0] + corner1_corner2[1]*x_before)
                        / (bullet_vector[1]*corner1_corner2[0]-bullet_vector[0]*corner1_corner2[1]);

                s = (bullet_vector[0]*corner_vector[1] - bullet_vector[0]*y_before - bullet_vector[1]*corner_vector[0] + bullet_vector[1]*x_before)
                        / (bullet_vector[1]*corner1_corner2[0] - bullet_vector[0]*corner1_corner2[1]);
                if(t >= 0 and t <= 1 and s >= 0 and s <= 1) //Om bägge parametrar är mellan 0-1 så skedde en kollision
                {
                    if(it->get_pointer_to_yourself()!=owner_pointer)//Kollar så att kollisionen inte var mot spelaren som avfyrade skottet
                    {
                        if(projectile_pointer->get_name() != "grenade")//Om projektilen är en kula så ska kulan göra skada, för de andra projektilerna är det explosionen som gör skada
                            it->set_health(it->get_health() - bullet_damage); //Kulan gör skada på skyddet

                        if(projectile_pointer->get_name() == "grenade") //Om projektilen är en granat så ska den studsa på skyddet
                        {
                            //Sätter tillbaka position till den senaste tillåtna
                            projectile_pointer->set_x_position(projectile_pointer->get_xpos() - projectile_pointer->get_x_movement());
                            projectile_pointer->set_y_position(projectile_pointer->get_ypos() - projectile_pointer->get_y_movement());
                            //Projicerar  bullet_vector på hörn1->hörn2 vektorn
                            double help_movement_vector[2] = {(bullet_vector[0]*corner1_corner2[0] + bullet_vector[1]*corner1_corner2[1])*corner1_corner2[0],(bullet_vector[0]*corner1_corner2[0] + bullet_vector[1]*corner1_corner2[1])*corner1_corner2[1]};
                            help_movement_vector[0] = help_movement_vector[0] / (pow(corner1_corner2[0],2) + pow(corner1_corner2[1],2));
                            help_movement_vector[1] = help_movement_vector[1] / (pow(corner1_corner2[0],2) + pow(corner1_corner2[1],2));

                            //Skapar den nya riktningsvektorn som granaten ska ha
                            double new_movement_vector[2] = {2*help_movement_vector[0] - bullet_vector[0], 2*help_movement_vector[1] - bullet_vector[1]};
                            projectile_pointer->set_x_movement(new_movement_vector[0]);
                            projectile_pointer->set_y_movement(new_movement_vector[1]);
                        }
                        return false;
                    }
                }
            }






            //Kollisionen kontrolleras på det sätt att man löser ekvationen för när linjen som sträcker sig utmed kulans pos. innan till efter
            // med just den riktningsvektorn skär med linjen som går utmed hörn1->hörn2 och hörn1->hörn4 med just de riktningsvektorerna, om
            // någon av ekvationerna löses med en parameter mellan 0-1 på bägge riktningsvektorer så är det en kollision.
            // Lösningen på riktnigsparametrarna ges genom följande ekvation (erhållen från Wolfram Alpha)

            //Börjar med hörn2->hörn3
            if(bullet_vector[0]*corner2_corner3[1]-bullet_vector[1]*corner2_corner3[0] != 0)//Kontrollerar först så att kulan inte rör sig parallellt med kanten, om ja->EJ KOLLISION
            {
                //Dessa lösningar är alltså tagna direkt ifrån wolframalpha
                t = (corner2_corner3[0]*corner_vector[3] - corner2_corner3[0]*y_before - corner2_corner3[1]*corner_vector[2] + corner2_corner3[1]*x_before)
                        / (bullet_vector[1]*corner2_corner3[0]-bullet_vector[0]*corner2_corner3[1]);

                s = (bullet_vector[0]*corner_vector[3] - bullet_vector[0]*y_before - bullet_vector[1]*corner_vector[2] + bullet_vector[1]*x_before)
                        / (bullet_vector[1]*corner2_corner3[0] - bullet_vector[0]*corner2_corner3[1]);
                if(t >= 0 and t <= 1 and s >= 0 and s <= 1) //Om bägge parametrar är mellan 0-1 så skedde en kollision
                {
                    if(it->get_pointer_to_yourself()!=owner_pointer)//Kollar så att kollisionen inte var mot spelaren som avfyrade skottet
                    {
                        if(projectile_pointer->get_name() != "grenade")//Om projektilen är en kula så ska kulan göra skada, för de andra projektilerna är det explosionen som gör skada
                            it->set_health(it->get_health() - bullet_damage); //Kulan gör skada på skyddet

                        if(projectile_pointer->get_name() == "grenade") //Om projektilen är en granat så ska den studsa på skyddet
                        {
                            //Sätter tillbaka position till den senaste tillåtna
                            projectile_pointer->set_x_position(projectile_pointer->get_xpos() - projectile_pointer->get_x_movement());
                            projectile_pointer->set_y_position(projectile_pointer->get_ypos() - projectile_pointer->get_y_movement());
                            //Projicerar  bullet_vector på hörn2->hörn3 vektorn
                            double help_movement_vector[2] = {(bullet_vector[0]*corner2_corner3[0] + bullet_vector[1]*corner2_corner3[1])*corner2_corner3[0],(bullet_vector[0]*corner2_corner3[0] + bullet_vector[1]*corner2_corner3[1])*corner2_corner3[1]};
                            help_movement_vector[0] = help_movement_vector[0] / (pow(corner2_corner3[0],2) + pow(corner2_corner3[1],2));
                            help_movement_vector[1] = help_movement_vector[1] / (pow(corner2_corner3[0],2) + pow(corner2_corner3[1],2));

                            //Skapar den nya riktningsvektorn som granaten ska ha
                            double new_movement_vector[2] = {2*help_movement_vector[0] - bullet_vector[0], 2*help_movement_vector[1] - bullet_vector[1]};
                            projectile_pointer->set_x_movement(new_movement_vector[0]);
                            projectile_pointer->set_y_movement(new_movement_vector[1]);
                        }
                        return false;
                    }
                }
            }




            //Börjar med hörn 3->4:
            if(bullet_vector[0]*corner3_corner4[1]-bullet_vector[1]*corner3_corner4[0] != 0)//Kontrollerar först så att kulan inte rör sig parallellt med kanten, om ja->EJ KOLLISION
            {
                //Dessa lösningar är alltså tagna direkt ifrån wolframalpha
                t = (corner3_corner4[0]*corner_vector[5] - corner3_corner4[0]*y_before - corner3_corner4[1]*corner_vector[4] + corner3_corner4[1]*x_before)
                        / (bullet_vector[1]*corner3_corner4[0]-bullet_vector[0]*corner3_corner4[1]);

                s = (bullet_vector[0]*corner_vector[5] - bullet_vector[0]*y_before - bullet_vector[1]*corner_vector[4] + bullet_vector[1]*x_before)
                        / (bullet_vector[1]*corner3_corner4[0] - bullet_vector[0]*corner3_corner4[1]);
                if(t >= 0 and t <= 1 and s >= 0 and s <= 1) //Om bägge parametrar är mellan 0-1 så skedde en kollision
                {
                    if(it->get_pointer_to_yourself()!=owner_pointer)//Kollar så att kollisionen inte var mot spelaren som avfyrade skottet
                    {
                        if(projectile_pointer->get_name() != "grenade")//Om projektilen är en kula så ska kulan göra skada, för de andra projektilerna är det explosionen som gör skada
                            it->set_health(it->get_health() - bullet_damage); //Kulan gör skada på skyddet

                        if(projectile_pointer->get_name() == "grenade") //Om projektilen är en granat så ska den studsa på skyddet
                        {
                            //Sätter tillbaka position till den senaste tillåtna
                            projectile_pointer->set_x_position(projectile_pointer->get_xpos() - projectile_pointer->get_x_movement());
                            projectile_pointer->set_y_position(projectile_pointer->get_ypos() - projectile_pointer->get_y_movement());
                            //Projicerar  bullet_vector på hörn3->hörn4 vektorn
                            double help_movement_vector[2] = {(bullet_vector[0]*corner3_corner4[0] + bullet_vector[1]*corner3_corner4[1])*corner3_corner4[0],(bullet_vector[0]*corner3_corner4[0] + bullet_vector[1]*corner3_corner4[1])*corner3_corner4[1]};
                            help_movement_vector[0] = help_movement_vector[0] / (pow(corner3_corner4[0],2) + pow(corner3_corner4[1],2));
                            help_movement_vector[1] = help_movement_vector[1] / (pow(corner3_corner4[0],2) + pow(corner3_corner4[1],2));

                            //Skapar den nya riktningsvektorn som granaten ska ha
                            double new_movement_vector[2] = {2*help_movement_vector[0] - bullet_vector[0], 2*help_movement_vector[1] - bullet_vector[1]};
                            projectile_pointer->set_x_movement(new_movement_vector[0]);
                            projectile_pointer->set_y_movement(new_movement_vector[1]);
                        }
                        return false;
                    }
                }
            }
        }


    }
    return true;
}

/*Apply_explosion_damage(double,double,int,int)
 * Applicerar skada på alla objekt som är inom en viss radie från föremålet.
 * Ger dessutom ut en tryckvåg så att objekt som är innanför explosionsradien får en rörelse ifrån explosionen
 */
void collision_handler::apply_explosion_damage(double x_pos, double y_pos, int radius, int damage)
{
    double explosion_power = 2;
    vector<cover>* cover_vector = gamefield_pointer->get_cover_vector();
    for(std::vector<cover>::iterator it = cover_vector->begin(); it != cover_vector->end(); ++it)
    {

        vector<double>corner_vector = it->get_corners(); //corner_vector är en vektor som innehåller rektangelns alla hörn
        bool done_damage = false;//Behöver hålla koll på om vi redan har applicerat skada på objektet
        //Om explosionen är inom en radies avstånd till rektangelns hörn så ska skada appliceras
        for(std::vector<double>::iterator it2 = corner_vector.begin(); it2 < corner_vector.end(); it2 = it2 + 2)
        {
            if(sqrt(pow((x_pos - *it2),2) + pow(y_pos - *(it2+1),2)) < radius)
            {
                it->set_health(it->get_health() - damage);
                it2 = corner_vector.end();//Fullösning för att få for loopen att avsluta så fort den har skadat ett hörn
                //vill ju inte att ett något ska ta dubbel skada bara för den hade två hörn nära explosionen
                done_damage=true;

                //Explosionen ska ge en tryckvåg som gör att objekt som är nära explosionen ska flyga iväg

                //vektorn från explosionens mitt till rektangelns mitt
                double explosion_center_cover_center[2] = {it->get_xpos() - x_pos, it->get_ypos() - y_pos};
                //Tar längden av vektorn
                double normalizer = sqrt(pow(explosion_center_cover_center[0],2) + pow(explosion_center_cover_center[1],2));
                //Nyttjar längden av vektorn för att skala ner vektorn från explosionens mitt till rektangelns mitt, dvs ju längre ifrån mitten är desto mindre blir vektorn
                explosion_center_cover_center[0] = explosion_center_cover_center[0] / pow(normalizer,2);
                explosion_center_cover_center[1]= explosion_center_cover_center[1] / pow(normalizer,2);
                //Skalar vektorn med damage
                explosion_center_cover_center[0] = explosion_center_cover_center[0] * pow(damage,explosion_power);
                explosion_center_cover_center[1] = explosion_center_cover_center[1] * pow(damage,explosion_power);
                //Nu är det dags att lägga till denna nya explosionshastigheten till det berörda objektet
                it->set_explosion_movement_x(it->get_explosion_movement_x() + explosion_center_cover_center[0]);
                it->set_explosion_movement_y(it->get_explosion_movement_y() + explosion_center_cover_center[1]);

            }
        }
        if(!done_damage)
        {
            //Skapar en ON-bas där aktuell rektangel är parallell med basvektorerna
            double base_vector_v[2] = {corner_vector[2] - corner_vector[0], corner_vector[3] - corner_vector[1]}; //u2 uttryckt i basen x,y, x1->x2 och y1->y2
            double base_vector_u[2] = {corner_vector[4] - corner_vector[2], corner_vector[5] - corner_vector[3]}; //v2 uttryckt i basen x,y
            //Vi vill normera basvektorerna
            double normalize_u = sqrt(pow(base_vector_u[0],2) + pow(base_vector_u[1],2));
            double normalize_v = sqrt(pow(base_vector_v[0],2) + pow(base_vector_v[1],2));

            base_vector_u[0] = base_vector_u[0] / normalize_u;
            base_vector_u[1] = base_vector_u[1] / normalize_u;
            base_vector_v[0] = base_vector_v[0] / normalize_v;
            base_vector_v[1] = base_vector_v[1] / normalize_v;
            //Skapar en "basbytarmatris" för att lätt kunna byta bas från x,y till u,v.
            //Notera att eftersom baserna är normerade så är Ae->f = (Af->e)^-1 = (Af->e)^t
            double base_change_matrix[2][2] = {base_vector_u[0],base_vector_u[1],base_vector_v[0],base_vector_v[1]};

            //skriver om rektangelns mittpunkt till den nya basen
            double rectangle_position[2] = {it->get_xpos(), it->get_ypos()}; //Mittpunkten i gamla basen
            double rectangle_position_new[2];
            rectangle_position_new[0] = base_change_matrix[0][0]*rectangle_position[0] + base_change_matrix[0][1]*rectangle_position[1];
            rectangle_position_new[1] = base_change_matrix[1][0]*rectangle_position[0] + base_change_matrix[1][1]*rectangle_position[1];


            //Nu ska vi skriva cirkelns koordinater i den nya matrisen, detta görs enkelt med basbytarmatrisen
            double explosion_position[2] = {x_pos,y_pos}; //cirkelns position i gamla basen
            double explosion_position_new[2]; //cirkelns position i nya basen
            explosion_position_new[0] = base_change_matrix[0][0]*explosion_position[0] + base_change_matrix[0][1]*explosion_position[1];
            explosion_position_new[1] = base_change_matrix[1][0]*explosion_position[0] + base_change_matrix[1][1]*explosion_position[1];
            //circle_position innehåller nu cirkelns koordinater i den nya koordinaten
            //För att explosionen inte ska nå rektangeln så måste rektangeln vara halva höjden + radien ifrån explosionen mitt
            //och halva bredden + radien ifrån explosionens mitt i de riktningar som höjden och bredden avser, förutom
            //vid hörnen men det har redan tagits hand om ovan
            //Notera att bredden på rektangeln är utmed u vektorn och höjden utmed v vektorn
            if(abs(rectangle_position_new[0] - explosion_position_new[0]) < (it->get_width() / 2) + radius and abs(rectangle_position_new[1] - explosion_position_new[1]) < (it->get_height() / 2) + radius)
            {
                it->set_health(it->get_health() - damage);
                //Explosionen ska ge en tryckvåg som gör att objekt som är nära explosionen ska flyga iväg

                //vektorn från explosionens mitt till rektangelns mitt
                double explosion_center_cover_center[2] = {it->get_xpos() - x_pos, it->get_ypos() - y_pos};
                //Tar längden av vektorn
                double normalizer = sqrt(pow(explosion_center_cover_center[0],2) + pow(explosion_center_cover_center[1],2));
                //Nyttjar längden av vektorn för att skala ner vektorn från explosionens mitt till rektangelns mitt, dvs ju längre ifrån mitten är desto mindre blir vektorn
                explosion_center_cover_center[0] = explosion_center_cover_center[0] / pow(normalizer,2);
                explosion_center_cover_center[1]= explosion_center_cover_center[1] / pow(normalizer,2);
                //Skalar vektorn med damage
                explosion_center_cover_center[0] = explosion_center_cover_center[0] * pow(damage,explosion_power);
                explosion_center_cover_center[1] = explosion_center_cover_center[1] * pow(damage,explosion_power);
                //Nu är det dags att lägga till denna nya explosionshastigheten till det berörda objektet
                it->set_explosion_movement_x(it->get_explosion_movement_x() + explosion_center_cover_center[0]);
                it->set_explosion_movement_y(it->get_explosion_movement_y() + explosion_center_cover_center[1]);

            }
        }
    }
    //Nu har vi applicerat explosions skadan på alla covers och det är nu dags för att applicera det på alla karaktärer
    vector<character>* character_vector = gamefield_pointer->get_character_vector();
    for(std::vector<character>::iterator it = character_vector->begin(); it != character_vector->end(); ++it)
    {

        vector<double>corner_vector = it->get_corners(); //corner_vector är en vektor som innehåller rektangelns alla hörn
        bool done_damage = false;//Behöver hålla koll på om vi redan har applicerat skada på objektet
        //Om explosionen är inom en radies avstånd till rektangelns hörn så ska skada appliceras
        for(std::vector<double>::iterator it2 = corner_vector.begin(); it2 < corner_vector.end(); it2 = it2 + 2)
        {
            if(sqrt(pow((x_pos - *it2),2) + pow(y_pos - *(it2+1),2)) < radius)
            {
                it->set_health(it->get_health() - damage);
                it2 = corner_vector.end();//Fullösning för att få for loopen att avsluta så fort den har skadat ett hörn
                //vill ju inte att ett något ska ta dubbel skada bara för den hade två hörn nära explosionen
                done_damage=true;
                //Explosionen ska ge en tryckvåg som gör att objekt som är nära explosionen ska flyga iväg

                //vektorn från explosionens mitt till rektangelns mitt
                double explosion_center_cover_center[2] = {it->get_xpos() - x_pos, it->get_ypos() - y_pos};
                //Tar längden av vektorn
                double normalizer = sqrt(pow(explosion_center_cover_center[0],2) + pow(explosion_center_cover_center[1],2));
                //Nyttjar längden av vektorn för att skala ner vektorn från explosionens mitt till rektangelns mitt, dvs ju längre ifrån mitten är desto mindre blir vektorn
                explosion_center_cover_center[0] = explosion_center_cover_center[0] / pow(normalizer,2);
                explosion_center_cover_center[1]= explosion_center_cover_center[1] / pow(normalizer,2);
                //Skalar vektorn med damage
                explosion_center_cover_center[0] = explosion_center_cover_center[0] * pow(damage,explosion_power);
                explosion_center_cover_center[1] = explosion_center_cover_center[1] * pow(damage,explosion_power);
                //Nu är det dags att lägga till denna nya explosionshastigheten till det berörda objektet
                it->set_explosion_movement_x(it->get_explosion_movement_x() + explosion_center_cover_center[0]);
                it->set_explosion_movement_y(it->get_explosion_movement_y() + explosion_center_cover_center[1]);
                cout << " 1 ";
            }
        }
        if(!done_damage)
        {
            //Skapar en ON-bas där aktuell rektangel är parallell med basvektorerna
            double base_vector_v[2] = {corner_vector[2] - corner_vector[0], corner_vector[3] - corner_vector[1]}; //u2 uttryckt i basen x,y, x1->x2 och y1->y2
            double base_vector_u[2] = {corner_vector[4] - corner_vector[2], corner_vector[5] - corner_vector[3]}; //v2 uttryckt i basen x,y
            //Vi vill normera basvektorerna
            double normalize_u = sqrt(pow(base_vector_u[0],2) + pow(base_vector_u[1],2));
            double normalize_v = sqrt(pow(base_vector_v[0],2) + pow(base_vector_v[1],2));

            base_vector_u[0] = base_vector_u[0] / normalize_u;
            base_vector_u[1] = base_vector_u[1] / normalize_u;
            base_vector_v[0] = base_vector_v[0] / normalize_v;
            base_vector_v[1] = base_vector_v[1] / normalize_v;
            //Skapar en "basbytarmatris" för att lätt kunna byta bas från x,y till u,v.
            //Notera att eftersom baserna är normerade så är Ae->f = (Af->e)^-1 = (Af->e)^t
            double base_change_matrix[2][2] = {base_vector_u[0],base_vector_u[1],base_vector_v[0],base_vector_v[1]};

            //skriver om rektangelns mittpunkt till den nya basen
            double rectangle_position[2] = {it->get_xpos(), it->get_ypos()}; //Mittpunkten i gamla basen
            double rectangle_position_new[2];
            rectangle_position_new[0] = base_change_matrix[0][0]*rectangle_position[0] + base_change_matrix[0][1]*rectangle_position[1];
            rectangle_position_new[1] = base_change_matrix[1][0]*rectangle_position[0] + base_change_matrix[1][1]*rectangle_position[1];


            //Nu ska vi skriva cirkelns koordinater i den nya matrisen, detta görs enkelt med basbytarmatrisen
            double explosion_position[2] = {x_pos,y_pos}; //cirkelns position i gamla basen
            double explosion_position_new[2]; //cirkelns position i nya basen
            explosion_position_new[0] = base_change_matrix[0][0]*explosion_position[0] + base_change_matrix[0][1]*explosion_position[1];
            explosion_position_new[1] = base_change_matrix[1][0]*explosion_position[0] + base_change_matrix[1][1]*explosion_position[1];
            //circle_position innehåller nu cirkelns koordinater i den nya koordinaten

            //För att explosionen inte ska nå rektangeln så måste rektangeln vara halva höjden + radien ifrån explosionen mitt
            //och halva bredden + radien ifrån explosionens mitt i de riktningar som höjden och bredden avser, förutom
            //vid hörnen men det har redan tagits hand om ovan
            //Notera att bredden på rektangeln är utmed u vektorn och höjden utmed v vektorn
            if(abs(rectangle_position_new[0] - explosion_position_new[0]) < (it->get_width() / 2) + radius and abs(rectangle_position_new[1] - explosion_position_new[1]) < (it->get_height() / 2) + radius)
            {

                it->set_health(it->get_health() - damage);
                //Explosionen ska ge en tryckvåg som gör att objekt som är nära explosionen ska flyga iväg

                //vektorn från explosionens mitt till rektangel mitt
                double explosion_center_cover_center[2] = {it->get_xpos() - x_pos, it->get_ypos() - y_pos};
                //Tar längden av vektorn
                double normalizer = sqrt(pow(explosion_center_cover_center[0],2) + pow(explosion_center_cover_center[1],2));
                //Nyttjar längden av vektorn för att skala ner vektorn från explosionens mitt till rektangelns mitt, dvs ju längre ifrån mitten är desto mindre blir vektorn
                explosion_center_cover_center[0] = explosion_center_cover_center[0] / pow(normalizer,2);
                explosion_center_cover_center[1]= explosion_center_cover_center[1] / pow(normalizer,2);
                //Skalar vektorn med damage
                explosion_center_cover_center[0] = explosion_center_cover_center[0] * pow(damage,explosion_power);
                explosion_center_cover_center[1] = explosion_center_cover_center[1] * pow(damage,explosion_power);
                //Nu är det dags att lägga till denna nya explosionshastigheten till det berörda objektet
                it->set_explosion_movement_x(it->get_explosion_movement_x() + explosion_center_cover_center[0]);
                it->set_explosion_movement_y(it->get_explosion_movement_y() + explosion_center_cover_center[1]);
                cout << " 2 ";
            }
        }
    }
    return;
}

