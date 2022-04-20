#WEBSCRAPER & HTML PARSER - ANDY GARCIA
from bs4 import BeautifulSoup
import requests
import re
from csv import writer

product = input()
page = 0
#LIST OF URL'S TO QUERY
url_list = [f"https://www.ebay.com/sch/i.html?_from=R40&_trksid=p2380057.m570.l1313&_nkw={product}&_sacat=0",f"https://www.zappos.com/{product}/.zso?t={product}&p={page}"]
header = ['Item', 'Price', 'Rating', 'URL']

for url in url_list:
    webpage = requests.get(url).text
    doc = BeautifulSoup(webpage, "html.parser")

    if 'zappos' in url:
        #FINDS NUMBER OF PAGES ON SITE
        webpage_pagination = doc.find(class_ = "Yv-z")
        pages = int(str(webpage_pagination).split(" ")[-1].split("<")[-3].split(">")[-1])

        for page in range(1, pages + 1):
            url = f"https://www.zappos.com/{product}/.zso?t={product}&p={page}"
            page = requests.get(url).text
            doc = BeautifulSoup(page, "html.parser")
            div = doc.find(class_="Bu-z")
            items = div.find_all(text = re.compile(product))

            #RETRIEVES ITEM NAME, PRICE, AND LINK
            for item in items:  
                parent = item.parent

                if parent.name != "a":
                    continue
                link = parent['href']
                
                rating = parent.text.split('$')[-1]

                if ' ' in rating:
                    price = rating.split('. ')[0]
                    rating = rating.split('. ')[-1]
                if len(rating) == 0:
                    rating = "0.0 out of 5 stars"
    if 'ebay' in url:
        for page in range(1, 50):
            url = f"https://www.ebay.com/sch/i.html?_from=R40&_trksid=p2380057.m570.l1313&_nkw={product}&_sacat={page}"
            page = requests.get(url).text
            doc = BeautifulSoup(page, "html.parser")
            div = doc.find(class_="srp-river-results clearfix")
            items = div.find_all(text = re.compile(product))
            span = doc.find_all("span", attrs={'class':'s-item__price'})
            for item in items:  
                print (item, )
