import requests

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


# Sprawdzenie odpowiedzi z serwera
if response.status_code == 200:
    print("Response server:")
    print(response.text)  # Wyświetlenie zawartości odpowiedzi
else:
    print(f"An error occurred: {response.status_code}")
