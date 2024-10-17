import requests
import json
from datetime import datetime

main_url = 'https://cyclusnv.nl'

#The data to be sent in the GET request
data = {
    'postcode': '2861XH',
    'huisnummer': '10'         
}
# function to request api and get content json
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


bag_id = info_location[0]['bagid'] # we need id Basisregistratie Adressen en Gebouwen (BAG) to next request
# content info about garbage flows
content_waste_flows = get_content_json(main_url + '/rest/adressen/' + bag_id +"/afvalstromen")


garbage_collection_date = []
for deadline_list in content_waste_flows:
    if deadline_list['ophaaldatum'] != None:
        garbage_date = {"date" : deadline_list['ophaaldatum'] , "garbage" : deadline_list['title']}
        garbage_collection_date.append(garbage_date)

garbage_collection_date_sorted = sorted(garbage_collection_date, key=lambda x:datetime.strptime(x["date"],'%Y-%m-%d'))

print(json.dumps(garbage_collection_date_sorted, indent = 4))