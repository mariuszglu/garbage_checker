#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>
#include <stdlib.h>

// Structure to store responses from the server
typedef struct
{
    char *memory; // Pointer to the buffer storing the response
    size_t size;  // Current size of data in buffer
} Memory_struct;

// structure with helpful urls
typedef struct
{
    const char *main_url;  // We use const for the URL (https://cyclusnv.nl)
    char url1[200];        // first URL request, we need id Basisregistratie Adressen en Gebouwen
    char url2[100];        // second request URL to get json content info about garbage flows
    const char *str_adres; // piece of url address
} URL_data;

// Structure with data location
typedef struct
{
    char postcode[10];   // We use the character table for the postal code
    char housenumber[5]; // We use the character table for the house number
    char bag_id[20];     // We need id Basisregistratie Adressen en Gebouwen (BAG) to next request
} Adres;

// Structure garbage collection date, finally we need this data
typedef struct
{
    char date[15];
    char name_garbage[30];
    int index; // index in garbage_array
    int size;  // size garbage_array
} Garbage;
// We create an array of 5 Garbage type elements
Garbage garbage_array[5];

// // Function to save the response in a structure, buffer to accomamade data
static size_t write_memory_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb; // We calculate the actual size of the data portion
    Memory_struct *mem;

    mem = (Memory_struct *)userp; // We calculate the actual size of the data portion

    // Dynamically expand buffer to accommodate new data
    mem->memory = realloc(mem->memory, mem->size + realsize + 1);
    if (mem->memory == NULL)
    { // We check if memory allocation was successful
        printf("Cannot allocate memory!\n");
        return 0;
    }
    else
    {
        // printf("Memory successfully allocate\n");
    }

    // We copy a new portion of data to the buffer
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize; // We update the data size

    mem->memory[mem->size] = '\0'; // End buffer with '\0'
    return realsize;
}

// Function to send GET request
char *send_get_request(const char *url)
{
    CURL *curl;
    CURLcode res;

    Memory_struct chunk;
    chunk.memory = malloc(1);
    chunk.size = 0;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_memory_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            curl_easy_cleanup(curl);
            free(chunk.memory);
            return NULL;
        }
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return chunk.memory; // We return the response as text (JSON format)
}

const char *translate_nl_to_en(const char *nl)

{
    if (nl == NULL)
    {
        return "NULL input"; // Error handling: NULL
    }
    else if (strcmp(nl, "Restafval") == 0)
    {
        return "Residual waste";
    }
    else if (strcmp(nl, "Plastic, metaal en drankenkartons") == 0)

    {
        return "Plastic, metal";
    }
    else if (strcmp(nl, "Groente-, fruit- en tuinafval") == 0)
    {
        return "Vegetable, fruit";
    }
    else if (strcmp(nl, "Oud papier & karton.") == 0)
    {
        return "Old paper & cardboard";
    }
    else
    {
        return 0;
    }
}

/*
Function we need to extract data like bag_id (Basisregistratie Adressen en Gebouwen (BAG)) and
garbage collection date, name_garbage

*/
void extract_data_from_JSON(const char *json_content, Adres *address, Garbage *garbage, Garbage garbage_array[])
{

    // Parsing the entire JSON response
    cJSON *json_array = cJSON_Parse(json_content);
    if (json_array == NULL)
    {
        printf("JSON parsing error!!.\n");
        return;
    }
    else
    {
        printf("JSON parsing OK!!.\n");
    }

    // Checking if we are dealing with a JSON array
    if (!cJSON_IsArray(json_array))
    {
        printf("JSON is not an array!!.\n");
        cJSON_Delete(json_array);
        return;
    }
    else
    {
        printf("JSON is an array!!.\n");
    }

    int array_size = cJSON_GetArraySize(json_array);

    int index = 0;
    for (int i = 0; i < array_size; i++)
    {
        cJSON *item = cJSON_GetArrayItem(json_array, i);
        cJSON *bagid = cJSON_GetObjectItem(item, "bagid");
        cJSON *ophaaldatum = cJSON_GetObjectItem(item, "ophaaldatum");
        cJSON *title = cJSON_GetObjectItem(item, "title");

        if (cJSON_IsString(bagid) && (bagid->valuestring != NULL))
        {
            strncpy(address->bag_id, bagid->valuestring, sizeof(address->bag_id) - 1);
        }

        if (cJSON_IsString(ophaaldatum) && (ophaaldatum->valuestring != NULL))

        {

            strncpy(garbage_array[garbage->index].date, ophaaldatum->valuestring, sizeof(garbage_array[garbage->index].date) - 1);
            strncpy(garbage_array[garbage->index].name_garbage, translate_nl_to_en(title->valuestring), sizeof(garbage_array[garbage->index].name_garbage) - 1);

            garbage->index++;
        }
    }
    cJSON_Delete(json_array); // Freeing up memory
}

// Comparison function for qsort
int compare_by_date(const void *a, const void *b)
{
    Garbage *garbageA = (Garbage *)a;
    Garbage *garbageB = (Garbage *)b;
    return strcmp(garbageA->date, garbageB->date);
}

// Function to sort the global array - garbage_array, sorting the array by date, ascending
void sort_garbage_array(int length)
{
    qsort(garbage_array, length, sizeof(Garbage), compare_by_date);
}

int main(void)
{

    // Creating an instance of the Address, URL_data, Garbage structure
    Adres address = {};
    URL_data urls;
    Garbage garbage = {};
    strcpy(address.postcode, "2861XC");
    strcpy(address.housenumber, "10");
    urls.main_url = "https://cyclusnv.nl";
    urls.str_adres = "/adressen/";

    // first URL example https://cyclusnv.nl/adressen/2861XC:10
    sprintf(urls.url1, "%s%s%s:%s", urls.main_url, urls.str_adres, address.postcode, address.housenumber);
    printf("%s\n", urls.url1);

    // in the first query we will receive JSON containing the bag_id
    char *response1 = send_get_request(urls.url1);

    if (response1 != NULL)
    {
        extract_data_from_JSON(response1, &address, &garbage, &garbage_array[0]);
        free(response1);
    }
    else
    {
        printf("Empty response");
    }

    // second URL https://cyclusnv.nl/rest/adressen/0513200000005956/afvalstromen
    sprintf(urls.url2, "%s/rest%s%s/afvalstromen", urls.main_url, urls.str_adres, address.bag_id);
    printf("%s\n", urls.url2);

    // in the second query w will receive JSON containig array with date and name_garbage
    char *response2 = send_get_request(urls.url2);

    if (response2 != NULL)
    {
        extract_data_from_JSON(response2, &address, &garbage, &garbage_array[0]);
        free(response2);
    }
    else
    {
        printf("Empty response");
    }
    // length of garbage_array
    int length = (sizeof(garbage_array) / sizeof(garbage_array[0])) - 1;

    sort_garbage_array(length);
    for (int i = 0; i < length; i++)
    {
        printf("Date of export: %s, Type of garbage: %s\n", garbage_array[i].date, garbage_array[i].name_garbage);
    }

    printf("End program!!\n");
    return 0;
}