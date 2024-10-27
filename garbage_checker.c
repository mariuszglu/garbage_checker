#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>


// Structure to store responses with the server
struct MemoryStruct {
    char *memory;
    size_t size;
};

typedef struct {
    const char* main_url; //We use const for the URL (https://cyclusnv.nl)
    char url1[100]; //first URL request, we need id Basisregistratie Adressen en Gebouwen
    char url2[100]; //second request URL to get json content info about garbage flows
} URLData;




//Structure definition
typedef struct{
    char postcode[10]; //We use the character table for the postal code
    char housenumber[5]; //We use the character table for the house number
    char bag_id[20]; //We need id Basisregistratie Adressen en Gebouwen (BAG) to next request
} Adres;


//Structure garbage collection date, finally we need this data
typedef struct{
    char date[15];
    char name_garbage[30];
}Garbage;



int main(void) {
 
    //Creating an instance of the Address structure
    Adres address;
    URLData urls;
    strcpy(address.postcode, "2867CG");
    strcpy(address.housenumber, "8");
    urls.main_url ="https://cyclusnv.nl";

    return 0;
}