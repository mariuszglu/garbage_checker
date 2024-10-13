import requests
import json

#The data to be sent in the GET request
data = {
    'postcode': '2861XH',
    'huisnummer': '10'         
}

# The URL of the endpoint to which you want to send data
main_url = 'https://cyclusnv.nl'
url = main_url + '/adressen/' + data["postcode"] +":"+ data["huisnummer"]



# Send request GET
# response = requests.get(url, data=data)
response = requests.get(url)


# Checking the response from the server
if response.status_code == 200:
    print("Response server:")
    print(response.text) # Display the content of the response
    content_json = json.loads(response.text) # Parsing a JSON string to a Python object
    bag_id = content_json[0]['bagid'] # we ned id Basisregistratie Adressen en Gebouwen (BAG)
else:
    print(f"An error occurred: {response.status_code}")
print(bag_id)