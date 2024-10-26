#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>

//Structure definition
typedef struct{
    char postcode[10]; //We use the character table for the postal code
    char housenumber[5]; //We use the character table for the house number
    char main_url[20]; //We use the character table for the URL (https://cyclusnv.nl)
    char bag_id[20]; //We need id Basisregistratie Adressen en Gebouwen (BAG) to next request
} Adres;


int main(void) {
 
    //Tworzenie instancji struktury Address
    Adres address;
    

    strcpy(address.postcode, "2867CG");
    strcpy(address.housenumber, "8");
    strcpy(address.main_url, "https://cyclusnv.nl");


    //Displaying content
    printf("Postcode: %s\n", address.postcode);
    printf("Number house: %s\n", address.postcode);
    printf("URL: %s\n", address.main_url);
   

    return 0;
}