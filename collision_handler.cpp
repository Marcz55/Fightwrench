#include "collision_handler.h"
collision_handler::collision_handler(gamefield* gamefield_object_pointer)
{
    gamefield_pointer = gamefield_object_pointer;
    //cover_vector = gamefield_object_pointer->get_cover_vector;
    window_height = gamefield_object_pointer->get_window_height();
    window_width = gamefield_object_pointer->get_window_width();
    return;
}
bool collision_handler::allowed_to_move_rectangle(vector<double> corner_vector_to_check)/*(double x1,double y1,double x2,double y2,double x3,double y3,double x4,double y4)*/
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
      //  cout /*<< " " << length_dia_1 << " " << length_dia_2 <<*/ << length_between_midpoints << " ";
        if(length_dia_1/2 + length_dia_2/2 >= length_between_midpoints)
        {   cout << " HEJ ";
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
                return false;
            }
            {
                if(abs(corner_to_check2[0]-corner_1[0]) + abs(corner_to_check2[0]-corner_3[0]) <= abs(corner_1[0]-corner_3[0]) and
                        abs(corner_to_check2[1]-corner_1[1]) + abs(corner_to_check2[1]-corner_3[1]) <= abs(corner_1[1]-corner_3[1]))
                {
                    return false;
                }
                {
                    if(abs(corner_to_check3[0]-corner_1[0]) + abs(corner_to_check3[0]-corner_3[0]) <= abs(corner_1[0]-corner_3[0]) and
                            abs(corner_to_check3[1]-corner_1[1]) + abs(corner_to_check3[1]-corner_3[1]) <= abs(corner_1[1]-corner_3[1]))
                    {
                        return false;
                    }
                    {
                        if(abs(corner_to_check4[0]-corner_1[0]) + abs(corner_to_check4[0]-corner_3[0]) <= abs(corner_1[0]-corner_3[0]) and
                                abs(corner_to_check4[1]-corner_1[1]) + abs(corner_to_check4[1]-corner_3[1]) <= abs(corner_1[1]-corner_3[1]))
                        {
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
                return false;
            }
            {
                if(abs(corner2_in_new_base[0]-corner2_1[0]) + abs(corner2_in_new_base[0]-corner2_3[0]) <= abs(corner2_1[0]-corner2_3[0]) and
                        abs(corner2_in_new_base[1]-corner2_1[1]) + abs(corner2_in_new_base[1]-corner2_3[1]) <= abs(corner2_1[1]-corner2_3[1]))
                {
                    return false;
                }
                {
                    if(abs(corner3_in_new_base[0]-corner2_1[0]) + abs(corner3_in_new_base[0]-corner2_3[0]) <= abs(corner2_1[0]-corner2_3[0]) and
                            abs(corner3_in_new_base[1]-corner2_1[1]) + abs(corner3_in_new_base[1]-corner2_3[1]) <= abs(corner2_1[1]-corner2_3[1]))
                    {
                        return false;
                    }
                    {
                        if(abs(corner4_in_new_base[0]-corner2_1[0]) + abs(corner4_in_new_base[0]-corner2_3[0]) <= abs(corner2_1[0]-corner2_3[0]) and
                                abs(corner4_in_new_base[1]-corner2_1[1]) + abs(corner4_in_new_base[1]-corner2_3[1]) <= abs(corner2_1[1]-corner2_3[1]))
                        {
                            return false;
                        }
                    }
                }
            }


        }
    }
    //HAR VI TAGIT OSS HIT SÅ HAR REKTANGELN KOLLAT KOLLISION MOT ALLA REKTANGLAR I COVER-LISTAN I GAMEFIELD
    //om vi vill att rektanglar ska kunna kollidera med annat än just rektanglar så får vi alltså lägga till det.
    return true;
}




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
            if(pow(pow(x_pos - corner_vector.at(*it),2) + pow(y_pos - corner_vector.at(*(it+1)),2),1/2) < radius)
                return false;
        }

        //Skapar en ON-bas där aktuell rektangel är parallell med basvektorerna
        double base_vector_u[2] = {corner_vector[2] - corner_vector[0], corner_vector[3] - corner_vector[1]}; //u2 uttryckt i basen x,y, x1->x2 och y1->y2
        double base_vector_v[2] = {corner_vector[4] - corner_vector[2], corner_vector[5] - corner_vector[3]}; //v2 uttryckt i basen x,y
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
        rectangle_position_new[0] = base_change_matrix[0][0]*rectangle_position[0] + base_change_matrix[0][0]*rectangle_position[1];
        rectangle_position_new[1] = base_change_matrix[0][0]*rectangle_position[0] + base_change_matrix[0][0]*rectangle_position[1];


        //Nu ska vi skriva cirkelns koordinater i den nya matrisen, detta görs enkelt med basbytarmatrisen
        double circle_position[2] = {x_pos,y_pos}; //cirkelns position i gamla basen
        double circle_position_new[2]; //cirkelns position i nya basen
        circle_position_new[0] = base_change_matrix[0][0]*circle_position[0] + base_change_matrix[0][0]*circle_position[1];
        circle_position_new[1] = base_change_matrix[1][0]*circle_position[0] + base_change_matrix[1][1]*circle_position[1];
        //circle_position innehåller nu cirkelns koordinater i den nya koordinaten


        //För att cirkeln inte ska kollidera med rektangeln så måste cirkeln vara halva höjden + radien ifrån cirkelns mitt
        //och halva bredden + radien ifrån cirkelns mitt i de riktningar som höjden och bredden avser, förutom
        //vid hörnen men det har redan tagits hand om ovan
        //Notera att bredden på rektangeln är utmed u vektorn och höjden utmed v vektorn
        if(abs(rectangle_position_new[0] - circle_position_new[0]) < it->get_width() + radius or abs(rectangle_position_new[1] - circle_position_new[1]) < it->get_height() + radius)
            return false;
    }
    return true;
}
