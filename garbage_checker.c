#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>


// Structure to store responses with the server
struct MemoryStruct {
    char *memory;   // Pointer to the buffer storing the response
    size_t size;    // Current size of data in buffer
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




// Function to save the response in a structure
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb; // We calculate the actual size of the data portion
    struct MemoryStruct *mem = (struct MemoryStruct *)userp; // We calculate the actual size of the data portion

// Dynamically expand buffer to accommodate new data
    mem->memory = realloc(mem->memory, mem->size + realsize + 1);
    if (mem->memory == NULL) { // We check if memory allocation was successful
        printf("Cannot allocate memory!\n");
        return 0;
    }

// We copy a new portion of data to the buffer
    memcpy(&(mem->memory[mem->size]), contents, realsize); 
    mem->size += realsize; // We update the data size
    mem->memory[mem->size] = '\0'; // End buffer with '\0'

    return realsize;
}






int main(void) {
 
    //Creating an instance of the Address structure
    Adres address;
    URLData urls;
    strcpy(address.postcode, "2867CG");
    strcpy(address.housenumber, "8");
    urls.main_url ="https://cyclusnv.nl";



    return 0;
}