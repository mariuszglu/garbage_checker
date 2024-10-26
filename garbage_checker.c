#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>


// Structure to store responses with the server
struct MemoryStruct {
    char *memory;
    size_t size;
};



//Structure definition
typedef struct{
    char postcode[10]; //We use the character table for the postal code
    char housenumber[5]; //We use the character table for the house number
    char main_url[20]; //We use the character table for the URL (https://cyclusnv.nl)
    char bag_id[20]; //We need id Basisregistratie Adressen en Gebouwen (BAG) to next request
} Adres;


//Structure garbage collection date
typedef struct{
    char date[15];
    char name_garbage[30];
}Garbage;



int main(void) {
 
    //Creating an instance of the Address structure
    Adres address;
    strcpy(address.postcode, "2867CG");
    strcpy(address.housenumber, "8");
    strcpy(address.main_url, "https://cyclusnv.nl");







    return 0;
}