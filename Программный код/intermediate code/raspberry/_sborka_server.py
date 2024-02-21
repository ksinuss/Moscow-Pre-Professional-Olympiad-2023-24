# подключение библиотек
import os
import cv2
import time
from serial import Serial
from http.server import BaseHTTPRequestHandler, HTTPServer

# объявление переменных
flag = 0
data = ''
gruz = ''
# gruzy = {
#     'винт': b'a',
#     'гайка': b'b',
#     'шайба': b'c',
#     'шпилька': b'd',
#     'подшипнк': b'e',
#     'направл': b'f',
#     'вал': b'g',
#     'двигатель': b'h',
#     'датчик': b'i'
# }
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
zakaz = {}
finish = 0

# инициализация последовательного интерфейса
ser = Serial('/dev/ttyUSB1', 9600, timeout=1)
ser.flush()

# декодирование qr-кода
def decod(cap, detector):
    _, img = cap.read()
    data, bbox, _ = detector.detectAndDecode(img)
    
    if (bbox is not None):
        for i in range(len(bbox)):
            cv2.line(img, tuple(bbox[i][0]), tuple(bbox[(i+1) % len(bbox)][0]), color=(255,
                     0, 255), thickness=2)
        cv2.putText(img, data, (int(bbox[0][0][0]), int(bbox[0][0][1]) - 10), cv2.FONT_HERSHEY_SIMPLEX,
                    0.5, (0, 255, 0), 2)
        if data: return data
        else: return ''

# «прогрев» камеры
time.sleep(0.1)

# связь с мобильным приложением
class ServerHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        global gruzy, zakaz, ser, flag, finish
        message_to_send = ''
        ## print("GET request, path:", self.path)
        # get data from app
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
        elif Request == '0':
            ser.write(b'0')
        message_to_send = get_data(zakaz)
        print(message_to_send)
        if message_to_send:
            flag += 1
        if flag == len(zakaz):
            ser.write(b'k')
        line = ''
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').rstrip()
        if line:
            message_to_send = 'q'
            finish = 1
            get_data()
        # send from rasp to server
        ## message_to_send = Request
        bytes_to_send = bytes(message_to_send, "utf")
        self.send_response(200)
        self.send_header('Content-Type', 'text/plain')
        self.send_header('Content-Length', len(bytes_to_send))
        self.end_headers()
        self.wfile.write(bytes_to_send)
        if finish == 1:
            self.close_connection = True
        return

def get_data(zakaz):
    global ser, finish
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
        ser.write(bytes(gruz, "utf")) # bykvy na ino
        time.sleep(1)
        data = ''
        return gruz
        ## flag = 0
    else:
        return ''

def server_thread():
    server_address = ('192.168.0.10/24', 8080)
    httpd = HTTPServer(server_address, ServerHandler)
    print('Starting server:')
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        pass
    httpd.server_close()
