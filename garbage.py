import requests

# The URL of the endpoint to which you want to send data

url = 'https://cyclusnv.nl/adressen/2861XH:10'

#The data to be sent in the GET request
data = {
    'postcode': '2861XH',
    'huisnummer': '10'         
}

# Send request GET
# response = requests.get(url, data=data)
response = requests.get(url)


# Sprawdzenie odpowiedzi z serwera
if response.status_code == 200:
    print("Response server:")
    print(response.text)  # Wyświetlenie zawartości odpowiedzi
else:
    print(f"An error occurred: {response.status_code}")
