#include <stdio.h>
#include <string.h>

//Structure definition
struct Adres {
    char postcode[10]; //We use the character table for the postal code
    char housenumber[5]; //We use the character table for the house number
    char main_url[20]; //We use the character table for the URL (https://cyclusnv.nl)
    char bag_id[20]; //We need id Basisregistratie Adressen en Gebouwen (BAG) to next request
    

};

char imie[10];

int main(void) {
 
    //Declaration of a struct variable Address
    struct Adres data;
    

    strcpy(data.postcode, "2867CG");
    strcpy(data.housenumber, "8");
    strcpy(data.main_url, "https://cyclusnv.nl");


    //Displaying content
    printf("Postcode: %s\n", data.postcode);
    printf("Number house: %s\n", data.postcode);
    printf("URL: %s\n", data.main_url);
   

    return 0;
}