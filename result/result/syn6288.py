# -*- coding: GBK -*-
import serial

class SYN6288:
    def __init__(self) -> None:
        # self.__ser = serial.Serial('/dev/ttyAMA0', 9600, timeout=0.5)
        self.__ser = serial.Serial('/dev/ttyS0', 9600, timeout=0.5)
    def __del__(self) -> None:
        self.__ser.close()

    def play_text(self, text: str) -> bool:
        gbk = text.encode('GBK')
        if len(gbk) > 200:
            print(len(gbk))
            gbk = gbk[:200]
        frame = self.__gen_frame(b'\x01\x01', data=gbk)
        print("encode(GBK): starting...")
        self.__ser.write(frame)
        print("Frame_Write: starting...")
        while True:
            state = self.__ser.read(1)
            if state  == b'O' or state  == b'N':
                continue
            return state == b'A'

    def query_state(self) -> bool:
        # 空闲时返回True，忙时返回False
        frame = self.__gen_frame(b'\x21')
        self.__ser.write(frame)
        while True:
            state = self.__ser.read(1)
            if state  == b'A' or state  == b'E':
                continue
            return state == b'O'

    def stop_synthesis(self):
        frame = self.__gen_frame(b'\02')
        self.__ser.write(frame)
        self.__ser.read(1)

    def pause_synthesis(self):
        frame = self.__gen_frame(b'\03')
        self.__ser.write(frame)
        self.__ser.read(1)

    def continue_synthesis(self):
        frame = self.__gen_frame(b'\04')
        self.__ser.write(frame)
        self.__ser.read(1)

    @staticmethod
    def __calc_bcc(bytes: bytes) -> bytes:
        result = 0
        for byte in bytes:
            result = result ^ byte
        return result.to_bytes(1, 'big')

    @staticmethod
    def __gen_frame(cmd_word: bytes, data: bytes = b'') -> bytes:
        result = b'\xfd'
        limited_data = data
        if len(data) > 200:
            limited_data = data[:200]
        data_len = (len(cmd_word) + len(limited_data) + 1).to_bytes(2, 'big')
        result += data_len + cmd_word + data
        bcc = SYN6288.__calc_bcc(result)
        return result + bcc

