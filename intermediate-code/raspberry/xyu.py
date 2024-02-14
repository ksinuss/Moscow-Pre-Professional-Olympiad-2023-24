import os
import cv2
import time
from serial import Serial
from http.server import BaseHTTPRequestHandler, HTTPServer

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
    'a': b'a',
    'b': b'b',
    'c': b'c',
    'd': b'd',
    'e': b'e',
    'f': b'f',
    'g': b'g',
    'h': b'h',
    'i': b'i'
}
zakaz = {}
finish = 0

# инициализация последовательного интерфейса
path = ''
if os.path.exists('/dev/ttyUSB0'):
    path = '/dev/ttyUSB0'
else:
    path = '/dev/ttyUSB1'
ser = Serial(path, 9600, timeout=1)
ser.flush()

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

class ServerHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        global gruzy, zakaz, ser, flag, finish
        message_to_send = ''
        print("GET request, path:", self.path)
        Request = self.path
        Request = Request[1:]
        print(Request)
        # формирование заказа
        if 2 <= len(Request) <= 3:
            for request in Request:
                if request in gruzy.keys():
                    name = gruzy[request]
                    zakaz[name] = request
        elif Request == '1' and zakaz:
            # старт механической подсистемы
            ser.write(b'1')
            print(1)
        elif Request == '0':
            ser.write(b'0')
            print(0)
        message_to_send = get_data(zakaz)
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

def get_data(zakaz):
    global path, finish
    ser = Serial(path, 9600, timeout=1)
    # получаем изображение с камеры
    cap = cv2.VideoCapture(0)
    detector = cv2.QRCodeDetector()
    # для завершения программы:
    if finish == 1:
        cap.release()
        cv2.destroyAllWindows()
        return
    # декодируем и передаем информацию о распознанном грузе
    data = decod(cap, detector)
    # проверяем на наличие груза в заказе
    if data in zakaz:
        gruz = zakaz[data]
        ser.write(bgruzy[gruz])
        print(gruz)
        time.sleep(1)
        data = ''
        return gruz
        ## flag = 0
    else:
        return ''

server_address = ('192.168.100.125', 8080)
httpd = HTTPServer(server_address, ServerHandler)
print('Starting server:')
httpd.serve_forever()
