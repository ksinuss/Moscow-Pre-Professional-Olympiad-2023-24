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

from http.server import BaseHTTPRequestHandler, HTTPServer
import time

class ServerHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        global flag, message_to_send, gruzy
        print("GET request, path:", self.path)
        Request = self.requestline
        Request = Request[5:int(len(Request)-9)]
        print(Request)
        if Request in gruzy.keys():
            flag = 1
        # send from rasp to server
        # message_to_send = Request
        bytes_to_send = bytes(message_to_send, "utf")
        self.send_response(200)
        self.send_header('Content-Type', 'text/plain')
        self.send_header('Content-Length', len(bytes_to_send))
        self.end_headers()
        self.wfile.write(bytes_to_send)
        # sleep(5)
        # self.wfile.write(bytes("q", "utf"))

def server_thread():
    server_address = ('192.168.0.14', 8080)
    httpd = HTTPServer(server_address, ServerHandler)
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        pass
    httpd.server_close()

flag = 0
if __name__ == '__main__':
    server_thread()
    message_to_send = ''
    if flag == 1:
        message_to_send = 'a'
        time.sleep(5)

