from enum import Enum
import numpy as np
import ctypes
import time

class BoardState(Enum):
  Empty = 0
  Black = 1
  White = 2


class GomokuBase(object):
  def __init__(self, **kwargs):
    self.width = int(kwargs.get('width', 15))
    self.height = int(kwargs.get('height', 15))
    self.n_to_win = int(kwargs.get('n_to_win', 5))

  def init_board(self):
    self.__board = []
    self.__available = list(range(self.width * self.height))
    self.__next_player_black = True

  def get_board_readable(self):
    board = np.zeros((self.height, self.width))
    for index, one_set in enumerate(self.__board):
      x, y = self.num_to_coor(one_set)
      if index % 2 == 0:
        player = BoardState.Black.value
      else:
        player = BoardState.White.value
      board[y][x] = player

    return board

  def get_available(self):
    return self.__available

  def get_next_player(self):
    if len(self.__board) % 2 == 0:
      return BoardState.Black.value
    else:
      return BoardState.White.value

  def num_to_coor(self, num):
    return num % self.width, num // self.width

  def coor_to_num(self, x, y):
    return y * self.width + x

  def do_chess(self, num):
    self.__board.append(num)
    self.__available.remove(num)


class GomokuAPI(object):
  def __init__(self, gomoku_base):
    self.__so = ctypes.cdll.LoadLibrary
    self.__lib = self.__so("../c/linux_proj/libgomoku_judge.so")
    self.__gomoku_base = gomoku_base

  def table_api_table_reset(self):
    self.__lib.TableAPITableReset()

  def api_set_and_judge(self, num):
    x, y = self.__gomoku_base.num_to_coor(num)
    player = self.__gomoku_base.get_next_player()
    self.table_api_set(y, x, player)
    return self.judge_api_do_judge(y, x, player)
    # ATTENTION: THE PLAYER AND COLOR IS NOT EQUAL!

  def table_api_set(self, x, y, color):
    self.__lib.TableAPISet(x, y, color)

  def judge_api_do_judge(self, x, y, color):
    return self.__lib.JudgeAPIDoJudge(x, y, color)

  def ai_api_get_best_set(self):
    tmp = self.__lib.AIAPIGetBestSet()
    x = tmp % 100
    y = tmp // 100
    return self.__gomoku_base.coor_to_num(x, y)

class GomokuPlayer(Enum):
  NotDefine = 0
  Human = 1
  SimpleAI = 2
  AI = 3


class GomokuServer(object):
  def __init__(self, gomoku_base):
    self.__gomoku_base = gomoku_base
    self.__gomoku_api = GomokuAPI(gomoku_base)

  def graphic(self):
    width = self.__gomoku_base.width
    height = self.__gomoku_base.height
    board = self.__gomoku_base.get_board_readable()

    """Draw the board and show game info"""

    print("Player Black", "with X".rjust(3))
    print("Player White", "with O".rjust(3))
    print(" ", end = ' ')
    for x in range(width):
      print("{0:4x}".format(x), end='')
    print('\n')
    for i in range(height):
      print("{0:4x}".format(i), end='')
      for j in range(width):
        p = board[i][j]
        if p == BoardState.Black.value:
          print('X'.center(4), end='')
        elif p == BoardState.White.value:
          print('O'.center(4), end='')
        else:
          print('_'.center(4), end='')
      print('\n')

  def input_by_key(self):
    str_in = input('with format: x,y\n')
    x, y = str_in.split(',')
    x = int(x)
    y = int(y)

    return self.__gomoku_base.coor_to_num(x, y)

  def start_play(self, player1 = GomokuPlayer.Human, player2 = GomokuPlayer.Human, output_func = None):
    self.__gomoku_api.table_api_table_reset()
    output_func()
    while True:
      next_player = self.__gomoku_base.get_next_player()
      if next_player == 1:
        next_player = 'Black'
        num = self.one_set(player1, next_player)
      else:
        next_player = 'White'
        num = self.one_set(player2, next_player)

      self.__gomoku_base.do_chess(num)
      output_func()
      result = self.__gomoku_api.api_set_and_judge(num)
      if result != 0:
        break
      if player1 == GomokuPlayer.SimpleAI and player2 == GomokuPlayer.SimpleAI:
        time.sleep(0.2)


  def one_set(self, player, next_player, input_func = None):
    if player == GomokuPlayer.Human:
      print("Turn to Human using %s..."%next_player)
      if input_func is None:
        return self.input_by_key()
      else:
        return input_func
    elif player == GomokuPlayer.SimpleAI:
      print("Turn to SimpleAI using %s..."%next_player)
      return self.__gomoku_api.ai_api_get_best_set()
    elif player == GomokuPlayer.AI:
      print("This AI is under building...")
      return 0

if __name__ == '__main__':
  # aaa = Gomoku(width = 8, height = 8)
  aaa = GomokuBase()
  aaa.init_board()
  bbb = GomokuServer(aaa)
  bbb.start_play(GomokuPlayer.Human, GomokuPlayer.SimpleAI, bbb.graphic)
# class GomokuJudge(Object):


# class GomokuPainter(Object):
