import requests

api_key = 'DN91XJ1M41F83KCS'

def fetch_and_save_stock_data(symbol, output_size='full', datatype='csv'):
    url = f'https://www.alphavantage.co/query'
    params = {
        'function': 'TIME_SERIES_DAILY',
        'symbol': symbol,
        'apikey': api_key,
        'outputsize': output_size,
        'datatype': datatype
    }

    response = requests.get(url, params=params)

    if response.status_code == 200:
        with open(f'{symbol}_stock_data.csv', 'w') as file:
            file.write(response.text)
        print(f"Data saved to {symbol}_stock_data.csv")
    else:
        print("Error: Unable to fetch data from Alpha Vantage")

symbol = 'ZOMATO.BSE'
fetch_and_save_stock_data(symbol, output_size='full', datatype='csv')
