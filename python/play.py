from __future__ import print_function
import random
import numpy as np
from collections import defaultdict, deque
from gomoku import GomokuServer, GomokuBase, GomokuPlayer
from mcts import MCTSPlayer
from CNN_policy import PolicyValueNet

from config import GomokuConfig


class PlayGomoku():
  def __init__(self, player1 = GomokuPlayer.Human, player2 = GomokuPlayer.Human):
    # params of the board and the game
    self.config = GomokuConfig()
    self.board = GomokuBase(width = self.config.board_width,
                       height=self.config.board_height,
                       n_to_win=self.config.n_to_win)
    self.game = GomokuServer(self.board, player1, player2)
    # num of simulations used for the pure mcts, which is used as
    # the opponent to evaluate the trained policy
    # start training from an initial policy-value net
    if player1 == GomokuPlayer.AI or player2 == GomokuPlayer.AI:
      self.policy_value_net = PolicyValueNet(self.config.board_width,
                                             self.config.board_height,
                                             model_file = self.config.model_path)
      self.mcts_player = MCTSPlayer(self.policy_value_net.policy_value_fn,
                                    c_puct = self.config.c_puct,
                                    n_playout = self.config.n_playout_play,
                                    is_selfplay = False)

  def play():
    self.game.start_play(player2_fn = self.mcts_player.get_action)

if __name__ == '__main__':
  choice = input('Choose player1:\n1-Human, 2-SimpleAI, 3-AlphaZero\n')
  player1 = GomokuPlayer(int(choice))
  choice = input('Choose player2:\n1-Human, 2-SimpleAI, 3-AlphaZero\n')
  player2 = GomokuPlayer(int(choice))


  play = PlayGomoku(player1, player2)
  if player1 == GomokuPlayer.AI:
    play.game.player1_fn = play.mcts_player.get_action
  # play.game.player1_args = {"board": play.board, "return_prob": 0, "temp" : 1000}
    play.game.player1_args = {"board": play.board, "return_prob": 0}
  if player2 == GomokuPlayer.AI:
    play.game.player2_fn = play.mcts_player.get_action
  # play.game.player2_args = {"board": play.board, "return_prob": 0, "temp" : 1000}
    play.game.player2_args = {"board": play.board, "return_prob": 0}
  play.game.start_play(output_fn = play.game.graphic)