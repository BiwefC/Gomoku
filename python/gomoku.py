from enum import Enum
import numpy as np

class BoardState(Enum):
  Empty = 0
  Black = 1
  White = 2

class Gomoku(object):
  def __init__(self, **kwargs):
    self.width = int(kwargs.get('width', 15))
    self.height = int(kwargs.get('height', 15))
    # self.n_to_win = int(kwargs.get('n_to_win', 5))
    self.n_to_win = 5

  def init_board(self):
    self.__board = np.zeros((self.height, self.width))
    self.__available = list(range(self.width * self.height))
    self.__next_player_black = True

  def get_board(self):
    return self.__board

  def get_available(self):
    return self.__available

  def get_next_player(self):
    if self.__next_player_black:
      return BoardState.Black
    else:
      return BoardState.White

  def change_next_player(self):
    self.__next_player_black = not self.__next_player_black

  def num_to_coor(self, num):
    return num % self.width, num // self.width

  def coor_to_num(self, x, y):
    return y * self.width + x

  def do_chess_basic(self, num, player):
    x, y = self.num_to_coor(num)
    self.__board[y][x] = player.value
    self.__available.remove(num)

  def do_chess(self, num):
    player = self.get_next_player()
    self.do_chess_basic(num, player)
    self.change_next_player()

  def judge_winner(self):
    print('the judge is missing!')

  def judge_end(self):
    if len(self.__available) == 0:
      return True

class PlayGomoku(object):
  def __init__(self, gomoku):
    self.gomoku = gomoku

  def graphic(self):
    width = self.gomoku.width
    height = self.gomoku.height
    board = self.gomoku.get_board()

    """Draw the board and show game info"""

    print("Player Black", "with X".rjust(3))
    print("Player White", "with O".rjust(3))
    for x in range(width):
      print("{0:6x}".format(x), end='')
    print('\n')
    for i in range(height):
      print("{0:4x}".format(i), end='')
      for j in range(width):
        p = board[i][j]
        if p == BoardState.Black.value:
          print('X'.center(6), end='')
        elif p == BoardState.White.value:
          print('O'.center(6), end='')
        else:
          print('_'.center(6), end='')
      print('\n\n')

  def input_by_key(self):
    str_in = input()
    x, y = str_in.split(',')
    x = int(x)
    y = int(y)

    return self.gomoku.coor_to_num(x, y)

  def start_play(self, input_func = None, output_func = None):
    while True:
      output_func()
      next_player = self.gomoku.get_next_player()
      print("Turn to %s" %next_player)
      num = input_func()
      self.gomoku.do_chess(num)

      # if self.gomoku.judge_end

if __name__ == '__main__':
  # aaa = Gomoku(width = 8, height = 8)
  aaa = Gomoku()
  aaa.init_board()
  bbb = PlayGomoku(aaa)
  bbb.start_play(bbb.input_by_key, bbb.graphic)
# class GomokuJudge(Object):


# class GomokuPainter(Object):
