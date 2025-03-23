from get_data import get_GLOD_price
from send_mail import send_GLOD_price
import time
# import math
from datetime import datetime

def gg():
    ST_P = get_GLOD_price()
    send_GLOD_price(ST_P)

    while True:
        time.sleep(20)
        price = get_GLOD_price()
        date_time = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        print(f'{date_time} 当前金价: {price:.2f} 人民币/克')
        if (abs(price - ST_P) > 0.5):
            send_GLOD_price(price, price > ST_P)
            ST_P = price

if __name__ == '__main__':
    print(datetime.now().strftime("%m-%d %H:%M:%S"))
    gg()