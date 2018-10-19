import ctypes
import numpy as np

# COLOR IN C
# 1: WHITE
# 2: BLACK

class GomokuAPI(object):
  def __init__(self):
    self.__so = ctypes.cdll.LoadLibrary
    self.__lib = self.__so("../c/linux_proj/libgomoku_judge.so")

  def api_do_judge(self, board_readable, last_x, last_y, count):
    [height, width] = board_readable.shape
    arr_line = ctypes.c_int * width

    arr = arr_line * height

    arr_inst = arr()

    for i in range(0, height):
      for j in range(0, width):
        if board_readable[i][j] == 2:
          arr_inst[i][j] = 1
        elif board_readable[i][j] == 1:
          arr_inst[i][j] = 2
        else:
          arr_inst[i][j] = 0

    return self.__lib.JudgeAPIDoJudge(arr_inst, ctypes.c_int(last_x), ctypes.c_int(last_y), ctypes.c_int(count))

  def api_get_best_set(self, board_readable, count):
    [height, width] = board_readable.shape
    arr_line = ctypes.c_int * width

    arr = arr_line * height

    arr_inst = arr()

    for i in range(0, height):
      for j in range(0, width):
        if board_readable[i][j] == 2:
          arr_inst[i][j] = 1
        elif board_readable[i][j] == 1:
          arr_inst[i][j] = 2
        else:
          arr_inst[i][j] = 0

    tmp = self.__lib.AIAPIGetBestSet(arr_inst, ctypes.c_int(count))
    x = tmp % 100
    y = tmp // 100
    return x, y

gomoku_api_inst = GomokuAPI()