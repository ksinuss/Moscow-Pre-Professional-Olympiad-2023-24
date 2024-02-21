# подключение библиотек
import os
import cv2
import time
from serial import Serial
from http.server import BaseHTTPRequestHandler, HTTPServer

# инициализация переменных
flag = 0
data = ''
gruz = ''
gruzy = {
    'a': 'винт',
    'b': 'гайка',
    'c': 'шайба',
    'd': 'шпилька',
    'e': 'подшипнк',
    'f': 'направл',
    'g': 'вал',
    'h': 'двигатель',
    'i': 'датчик'
}
bgruzy = {
    'a': b'VINT ',
    'b': b'GAIKA ',
    'c': b'SHAIBA ',
    'd': b'SHPILKA ',
    'e': b'PODSHIPNIK ',
    'f': b'NAPRAVLYAUSHAYA ',
    'g': b'VAL ',
    'h': b'DVIGATEL ',
    'i': b'DATCHIK '
}
zakaz = {}
finish = 0
take = 0
option = []
line = ''

# инициализация последовательного интерфейса
path = ''
if os.path.exists('/dev/ttyUSB0'):
    path = '/dev/ttyUSB0'
else:
    path = '/dev/ttyUSB1'
ser = Serial(path, 9600, timeout=1)
ser.flush()

# функция декодирования qr-кода
def decod(cap, detector):
    _, img = cap.read()
    data, bbox, _ = detector.detectAndDecode(img)
    if(bbox is not None):
        for i in range(len(bbox)):
            cv2.line(img, tuple(bbox[i][0]), tuple(bbox[(i+1) % len(bbox)][0]), color=(255,
                     0, 255), thickness=2)
        cv2.putText(img, data, (int(bbox[0][0][0]), int(bbox[0][0][1]) - 10), cv2.FONT_HERSHEY_SIMPLEX,
                    0.5, (0, 255, 0), 2)
        if data: return data
        else: return ''

# взаимодействие с мобильным приложением
class ServerHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        global gruzy, zakaz, ser, flag, finish, option, take, line
        message_to_send = ''
        print("GET request, path:", self.path)
        Request = self.path
        Request = Request[1:]
        print(Request)
        #message_to_send = Request
        # формирование заказа
        if 2 <= len(Request) <= 3:
            for request in Request:
                if request in gruzy.keys():
                    name = gruzy[request]
                    zakaz[name] = request
        if Request == '1' and zakaz:
            # старт механической подсистемы
            # ser.write(b'1')
            # option = list(zakaz.values())
            # print(option)
            flag = 1
            print(len(zakaz))
            if len(zakaz) == 2:
                ser.write(b'2')
            else:
                ser.write(b'3')
        if Request == '0':
            ser.write(b'0')
            finish = 1
            flag = 0
            print(0)
        # if flag == len(zakaz):
        #     ser.write(b'k')
        #     ser.write()
        #     flag = 0
            #message_to_send = 'q'
        if flag == 1:
            message_to_send = get_data(zakaz)
            #ser.write(b'1')
        if take == 1:
            line = ser.readline().decode('utf-8').rstrip()
            if line == 't':
                take = 0
                line = ''
            if line == 'q':
                message_to_send = b'q'
        # if message_to_send in option:
        #     flag += 1
        #     print(message_to_send)
        print(message_to_send)
        # send from rasp to server
        #message_to_send = Request
        bytes_to_send = bytes(message_to_send, "utf")
        self.send_response(200)
        self.send_header('Content-Type', 'text/plain')
        self.send_header('Content-Length', len(bytes_to_send))
        self.end_headers()
        self.wfile.write(bytes_to_send)
        return

# распознавание
def get_data(zakaz):
    global path, flag, take
    ser = Serial(path, 9600, timeout=1)
    # получаем изображение с камеры
    cap = cv2.VideoCapture(0)
    detector = cv2.QRCodeDetector()
    # декодируем и передаем информацию о распознанном грузе
    data = decod(cap, detector)
    # проверяем на наличие груза в заказе
    if data in zakaz:
        gruz = zakaz[data]
        ser.write(bgruzy[gruz])
        print(gruz)
        data = ''
        take = 1
        #flag += 1
        return gruz
        ## flag = 0
    else:
        #ser.write(b'n')
        return ''

# открываем сервер
server_address = ('192.168.100.199', 8080)
httpd = HTTPServer(server_address, ServerHandler)
print('Starting server:')
httpd.serve_forever()
