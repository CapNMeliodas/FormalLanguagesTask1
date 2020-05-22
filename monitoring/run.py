import os
import logging
import time
import unicodedata
import graphyte


from selenium import webdriver
from bs4 import BeautifulSoup

logging.getLogger().setLevel(logging.INFO)

BASE_URL = 'http://tikr.ru/stock'
COMPANIES_NUMBER = 3

def parse_page(page):
    stonks_table = page.find('table', {'class': 'tablest'})
    # if (stonks_table == None):
    #     stonks = []
    #     stonks.append(('GTL', 2.0))
    #     stonks.append(('Yandex', 3.0))
    #     stonks.append(('Abrau-Durso', 4.0))
    #     return stonks


    body = stonks_table.find('tbody')
    rows = body.findAll('tr')
    stonks = []

    numbers = []
    cnt = 0
    for row in rows:
        cnt += 1
        number = float(row.find('span').text.replace('%', ''))
        numbers.append(number)
        if cnt == COMPANIES_NUMBER: 
            break
    
    stonks.append(('GTL', numbers[0]))
    stonks.append(('Yandex', numbers[1]))
    stonks.append(('Abrau-Durso', numbers[2]))

    return stonks


GRAPHITE_HOST = 'graphite'

def send_metrics(stonks):
    sender = graphyte.Sender(GRAPHITE_HOST, prefix='stonks')
    for stonk in stonks:
        sender.send(stonk[0], stonk[1])

def main():

    driver = webdriver.Remote(
        command_executor='http://selenium:4444/wd/hub',
        desired_capabilities={'browserName': 'chrome', 'javascriptEnabled': True}
    )

    driver.get('http://tikr.ru/stock')
    time.sleep(5)
    html = driver.page_source
    soup = BeautifulSoup(html, 'html.parser')

    metric = parse_page(soup)
    send_metrics(metric)

    driver.quit()

    logging.info('Accessed %s ..', BASE_URL)
    logging.info('Page title: %s', driver.title)

if __name__ == '__main__':
    main()
