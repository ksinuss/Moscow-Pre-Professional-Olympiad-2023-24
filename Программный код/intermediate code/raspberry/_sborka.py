# подключение библиотек
import cv2
from serial import Serial
import time

# объявление переменных
flag = 0
data = ''
gruz = ''
gruzy = {
    'винт': b'a',
    'гайка': b'b',
    'шайба': b'c',
    'шпилька': b'd',
    'подшипнк': b'e',
    'направл': b'f',
    'вал': b'g',
    'двигатель': b'h',
    'датчик': b'i'
}

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

flag = 1

while flag:
    # получаем изображение с камеры
    cap = cv2.VideoCapture(0)
    detector = cv2.QRCodeDetector()
    # декодируем и передаем информацию о распознанном грузе
    data = decod(cap, detector)
    if data in gruzy:
        gruz = gruzy[data]
        ser.write(gruz)
        time.sleep(1)
        data = ''
        # flag = 0

# завершение программы
cap.release()
cv2.destroyAllWindows()
