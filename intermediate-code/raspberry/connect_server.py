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

flag = 0
flagg = 0

from http.server import BaseHTTPRequestHandler, HTTPServer
import time

class ServerHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        global flag, flagg, gruzy, pr
        message_to_send = ''
        print("GET request, path:", self.path)
        Request = self.path
        Request = Request[1:]
        print(Request)
        if Request == 'a':
            message_to_send = 'a'
        if Request == 'b':
            message_to_send = 'b'
        if Request == 'i':
            message_to_send = 'i'
            flagg = 1
            pr()
            # self.close_connection = True
            # return
        if flag == 1:
            time.sleep(5)
            message_to_send = 'q'
        # send from rasp to server
        # message_to_send = Request
        bytes_to_send = bytes(message_to_send, "utf")
        self.send_response(200)
        self.send_header('Content-Type', 'text/plain')
        self.send_header('Content-Length', len(bytes_to_send))
        self.end_headers()
        self.wfile.write(bytes_to_send)
        return

def server_thread():
    server_address = ('192.168.100.125', 8080)
    httpd = HTTPServer(server_address, ServerHandler)
    print('Starting server:')
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        pass
    httpd.server_close()

def pr():
    global flag
    print(flagg)
    flag = 1

server_thread()

#from xyu import wifi ip adress please

