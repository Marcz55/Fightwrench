#include "collision_handler.h"
collision_handler::collision_handler(gamefield* gamefield_object_pointer)
{
    gamefield_pointer = gamefield_object_pointer;
    //cover_vector = gamefield_object_pointer->get_cover_vector;
    return;
}
bool collision_handler::allowed_to_move_rectangle(double x1,double y1,double x2,double y2,double x3,double y3,double x4,double y4)
{
    vector<cover>* cover_vector = gamefield_pointer->get_cover_vector();
    bool colide = false;
    //Skapar den nya basen för rektangeln
    double base_vector_u[2] = {x2 - x1, y2 - y1}; //u uttryckt i basen x,y
    double base_vector_v[2] = {x3 - x2, y3 - y2}; //v uttryckt i basen x,y
    //Vi vill normera basvektorerna
    base_vector_u[0] = base_vector_u[0] / sqrt(pow(base_vector_u[0],2) + pow(base_vector_u[1],2));
    base_vector_u[1] = base_vector_u[1] / sqrt(pow(base_vector_u[0],2) + pow(base_vector_u[1],2));
    base_vector_v[0] = base_vector_v[0] / sqrt(pow(base_vector_v[0],2) + pow(base_vector_v[1],2));
    base_vector_v[1] = base_vector_v[1] / sqrt(pow(base_vector_v[0],2) + pow(base_vector_v[1],2));

    //Skapar en "basbytarmatris" för att lätt kunna byta bas från x,y till u,v.
    //Notera att eftersom baserna är normerade så är Ae->f = (Af->e)^-1 = (Af->e)^t
    double base_change_matrix[2][2] = {base_vector_u[0],base_vector_u[1],base_vector_v[0],base_vector_v[1]};

    //Tar ut koordinaterna för rektangelns hörn i den nya koordinaten, notera att jag bara behöver
    //ta ut två hörn, de "motsatta" eftersom vi gör det i en nya bas där rektangeln nu är vinkelrät
    //relativt koordinataxlarna.
    double corner_1[2];
    corner_1[0] = base_change_matrix[0][0]*x1 + base_change_matrix[0][1]*y1;
    corner_1[1] = base_change_matrix[1][0]*x1 + base_change_matrix[1][1]*y1;

    double corner_3[2];
    corner_3[0] = base_change_matrix[0][0]*x3 + base_change_matrix[0][1]*y3;
    corner_3[1] = base_change_matrix[1][0]*x3 + base_change_matrix[1][1]*y3;

    //Nu har vi initierat klart och behöver alltså kolla igenom om den nya koordinaten är okej att flytta till.
    //Vi börjar med att gå igenom cover listan (som just nu antas bara bestå av rektangelobjekt.
    for(std::vector<cover>::iterator it = cover_vector->begin(); it != cover_vector->end(); ++it)
    {

        vector<double>corner_vector = it->get_corners(); //Tänker att get_corner returnerar
        //x1,y1,x2,y2.. för de olika hörnen i en vektor i den ordningen.
        //Skriver rektangelns hörn i de nya koordinaterna u,v.
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

        //Kollar om någon av rektangelns hörn ligger inuti rektangeln som vi kollar kollision för
        if(abs(corner_to_check1[0]-corner_1[0]) + abs(corner_to_check1[0]-corner_3[0]) <= abs(corner_1[0]-corner_3[0]) and
                abs(corner_to_check1[1]-corner_1[1]) + abs(corner_to_check1[1]-corner_3[1]) <= abs(corner_1[1]-corner_3[1]))
        {
            colide = true;
        }
        {
            if(abs(corner_to_check2[0]-corner_1[0]) + abs(corner_to_check2[0]-corner_3[0]) <= abs(corner_1[0]-corner_3[0]) and
                    abs(corner_to_check2[1]-corner_1[1]) + abs(corner_to_check2[1]-corner_3[1]) <= abs(corner_1[1]-corner_3[1]))
            {
                colide = true;
            }
            {
                if(abs(corner_to_check3[0]-corner_1[0]) + abs(corner_to_check3[0]-corner_3[0]) <= abs(corner_1[0]-corner_3[0]) and
                        abs(corner_to_check3[1]-corner_1[1]) + abs(corner_to_check3[1]-corner_3[1]) <= abs(corner_1[1]-corner_3[1]))
                {
                    colide = true;
                }
                {
                    if(abs(corner_to_check4[0]-corner_1[0]) + abs(corner_to_check4[0]-corner_3[0]) <= abs(corner_1[0]-corner_3[0]) and
                            abs(corner_to_check4[1]-corner_1[1]) + abs(corner_to_check4[1]-corner_3[1]) <= abs(corner_1[1]-corner_3[1]))
                        colide = true;
                }
            }
        }

        if(colide)
            return colide;
        //Har vi tagit oss hit har vi inte fått någon kollission, vad som krävs nu är att vi gör ytterliggare ett basbyte, men nu till rektangeln i cover listan
        double base_vector_u2[2] = {corner_vector[2] - corner_vector[0], corner_vector[3] - corner_vector[1]}; //u2 uttryckt i basen x,y
        double base_vector_v2[2] = {corner_vector[4] - corner_vector[2], corner_vector[5] - corner_vector[3]}; //v2 uttryckt i basen x,y
        //Vi vill normera basvektorerna
        base_vector_u2[0] = base_vector_u2[0] / sqrt(pow(base_vector_u2[0],2) + pow(base_vector_u2[1],2));
        base_vector_u2[1] = base_vector_u2[1] / sqrt(pow(base_vector_u2[0],2) + pow(base_vector_u2[1],2));
        base_vector_v2[0] = base_vector_v2[0] / sqrt(pow(base_vector_v2[0],2) + pow(base_vector_v2[1],2));
        base_vector_v2[1] = base_vector_v2[1] / sqrt(pow(base_vector_v2[0],2) + pow(base_vector_v2[1],2));

        //Skapar en "basbytarmatris" för att lätt kunna byta bas från x,y till u2,v2.
        //Notera att eftersom baserna är normerade så är Ae->f = (Af->e)^-1 = (Af->e)^t
        double base_change_matrix2[2][2] = {base_vector_u2[0],base_vector_u2[1],base_vector_v2[0],base_vector_v2[1]};

        //Tar ut koordinaterna för rektangelns hörn i den nya koordinaten, notera att jag bara behöver
        //ta ut två hörn, de "motsatta" eftersom vi gör det i en nya bas där rektangeln nu är vinkelrät
        //relativt koordinataxlarna.
        double corner2_1[2];
        corner2_1[0] = base_change_matrix2[0][0]*corner_vector[0] + base_change_matrix[0][1]*corner_vector[1];
        corner2_1[1] = base_change_matrix2[1][0]*corner_vector[0] + base_change_matrix[1][1]*corner_vector[1];

        double corner2_3[2];
        corner2_3[0] = base_change_matrix2[0][0]*corner_vector[4] + base_change_matrix[0][1]*corner_vector[5];
        corner2_3[1] = base_change_matrix2[1][0]*corner_vector[4] + base_change_matrix[1][1]*corner_vector[5];

        //Nu behöver vi kolla om rektangeln i cover "skär" in i den rektangeln vi kollar kollission för

        //skapar ny arrays för att hålla hörnen i den nya basen
        double corner1_in_new_base[2];
        double corner2_in_new_base[2];
        double corner3_in_new_base[2];
        double corner4_in_new_base[2];
        corner1_in_new_base[0] = base_change_matrix2[0][0]*x1 + base_change_matrix2[0][1]*y1;
        corner1_in_new_base[1] = base_change_matrix2[1][0]*x1 + base_change_matrix2[1][1]*y1;

        corner2_in_new_base[0] = base_change_matrix2[0][0]*x2 + base_change_matrix2[0][1]*y2;
        corner2_in_new_base[1] = base_change_matrix2[1][0]*x2 + base_change_matrix2[1][1]*y2;

        corner3_in_new_base[0] = base_change_matrix2[0][0]*x3 + base_change_matrix2[0][1]*y3;
        corner3_in_new_base[1] = base_change_matrix2[1][0]*x3 + base_change_matrix2[1][1]*y3;

        corner4_in_new_base[0] = base_change_matrix2[0][0]*x4 + base_change_matrix2[0][1]*y4;
        corner4_in_new_base[1] = base_change_matrix2[1][0]*x4 + base_change_matrix2[1][1]*y4;



        //Kollar om någon av rektangelns (vars kollission vi undersöker) hörn ligger inuti rektangeln från cover-listan
        if(abs(corner1_in_new_base[0]-corner2_1[0]) + abs(corner1_in_new_base[0]-corner2_3[0]) <= abs(corner2_1[0]-corner2_3[0]) and
                abs(corner1_in_new_base[1]-corner2_1[1]) + abs(corner1_in_new_base[1]-corner2_3[1]) <= abs(corner2_1[1]-corner2_3[1]))
        {
            colide = true;
        }
        {
            if(abs(corner2_in_new_base[0]-corner2_1[0]) + abs(corner2_in_new_base[0]-corner2_3[0]) <= abs(corner2_1[0]-corner2_3[0]) and
                    abs(corner2_in_new_base[1]-corner2_1[1]) + abs(corner2_in_new_base[1]-corner2_3[1]) <= abs(corner2_1[1]-corner2_3[1]))
            {
                colide = true;
            }
            {
                if(abs(corner3_in_new_base[0]-corner2_1[0]) + abs(corner3_in_new_base[0]-corner2_3[0]) <= abs(corner2_1[0]-corner2_3[0]) and
                        abs(corner3_in_new_base[1]-corner2_1[1]) + abs(corner3_in_new_base[1]-corner2_3[1]) <= abs(corner2_1[1]-corner2_3[1]))
                {
                    colide = true;
                }
                {
                    if(abs(corner4_in_new_base[0]-corner2_1[0]) + abs(corner4_in_new_base[0]-corner2_3[0]) <= abs(corner2_1[0]-corner2_3[0]) and
                            abs(corner4_in_new_base[1]-corner2_1[1]) + abs(corner4_in_new_base[1]-corner2_3[1]) <= abs(corner2_1[1]-corner2_3[1]))
                    colide = true;
                }
            }
        }

        if(colide)
            return colide;
    }
    //HAR VI TAGIT OSS HIT SÅ HAR REKTANGELN KOLLAT KOLLISION MOT ALLA REKTANGLAR I COVER-LISTAN I GAMEFIELD
    //om vi vill att rektanglar ska kunna kollidera med annat än just rektanglar så får vi alltså lägga till det.
return colide;
}



/*
bool collision_handler::allowed_to_move_circle(int x, int y, int radius)
{

}
*/
