import requests
import json

main_url = 'https://cyclusnv.nl'

#The data to be sent in the GET request
data = {
    'postcode': '2861XH',
    'huisnummer': '10'         
}

def get_content_json(url):
    # Send request GET
    response = requests.get(url)
    # Checking the response from the server
    if response.status_code == 200:
        content_json = json.loads(response.text) # Parsing a JSON string to a Python object
        return content_json
    else:
        print(f"An error occurred: {response.status_code}")



info_location = get_content_json(main_url + '/adressen/' + data["postcode"] +":"+ data["huisnummer"])
print(info_location)


bag_id = info_location[0]['bagid'] # we need id Basisregistratie Adressen en Gebouwen (BAG) to next request
print(bag_id)
# content info about garbage flows
info_waste_flows = get_content_json(main_url + '/rest/adressen/' + bag_id +"/afvalstromen")
print(info_waste_flows)

