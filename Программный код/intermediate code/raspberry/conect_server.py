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

# transmit = {
#     'винт': 'screw',
#     'гайка': 'gaika',
#     'шайба': 'puck',
#     'шпилька': 'hairpin',
#     'подшипнк': 'bearing',
#     'направл': 'napravlyayushchaya',
#     'вал': 'shaft',
#     'двигатель': 'engine',
#     'датчик': 'sensor'
# }

zakaz = {}

from http.server import BaseHTTPRequestHandler, HTTPServer
from time import sleep
class RequestHandler_httpd(BaseHTTPRequestHandler):
    def do_GET(self):
        global Request, gruzy, zakaz
        while True:
            # get data from app
            Request = self.requestline
            Request = Request[5:int(len(Request)-9)]
            print(Request)
            for request in Request:
                if request in gruzy.keys():
                    gruz = gruzy[request]
                    # if gruz == 'подшипнк': name = 'подшипник'
                    # elif gruz == 'направл': name = 'направляющая'
                    # else: name = gruz
                    name = request
                    zakaz[gruz] = name
            
            # send from rasp to server
            # message_to_send = bytes("Hello World!", "utf")
            message_to_send = ' '.join(list(zakaz.values()))
            # message_to_send = bytes(message_to_send, "koi8-r")
            message_to_send = bytes(message_to_send, "utf")
            # message_to_send = Request
            # message_to_send = bytes(message_to_send, "utf")
            self.send_response(200)
            self.send_header('Content-Type', 'text/plain')
            self.send_header('Content-Length', len(message_to_send))
            self.end_headers()
            self.wfile.write(message_to_send)
            # sleep(5)
            # self.wfile.write(bytes("q", "utf"))
            zakaz = {}
            return
# sudo nano /etc/dhcpcd.conf - linux
# ipconfig - win
server_address_httpd = ('192.168.0.14', 8080)
httpd = HTTPServer(server_address_httpd, RequestHandler_httpd)
print('Starting server:')
httpd.serve_forever()
                                         