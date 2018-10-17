

from __future__ import print_function
import random
import numpy as np
from collections import defaultdict, deque
# from game import Board, Game
from gomoku import GomokuServer, GomokuBase
# from mcts_pure import MCTSPlayer as MCTS_Pure
from mcts import MCTSPlayer
from CNN_policy import PolicyValueNet  # Theano and Lasagne
# from policy_value_net_pytorch import PolicyValueNet  # Pytorch
# from policy_value_net_tensorflow import PolicyValueNet # Tensorflow
# from policy_value_net_keras import PolicyValueNet # Keras


class PlayGomoku():
  def __init__(self, init_model=None):
    # params of the board and the game
    self.board_width = 8
    self.board_height = 8
    self.n_to_win = 5
    self.board = GomokuBase(width=self.board_width,
                       height=self.board_height,
                       n_to_win=self.n_to_win)
    self.game = GomokuServer(self.board)
    # training params
    self.learn_rate = 2e-3
    self.lr_multiplier = 1.0  # adaptively adjust the learning rate based on KL
    self.temp = 1.0  # the temperature param
    self.n_playout = 400  # num of simulations for each move
    self.c_puct = 5
    self.buffer_size = 10000
    self.batch_size = 512  # mini-batch size for training
    self.data_buffer = deque(maxlen=self.buffer_size)
    self.play_batch_size = 1
    self.epochs = 5  # num of train_steps for each update
    self.kl_targ = 0.02
    self.check_freq = 50
    self.game_batch_num = 1500
    self.best_win_ratio = 0.0
    # num of simulations used for the pure mcts, which is used as
    # the opponent to evaluate the trained policy
    self.pure_mcts_playout_num = 1000
    if init_model:
      # start training from an initial policy-value net
      self.policy_value_net = PolicyValueNet(self.board_width,
                                             self.board_height,
                                             model_file=init_model)
    else:
      # start training from a new policy-value net
      self.policy_value_net = PolicyValueNet(self.board_width,
                                             self.board_height)
    self.mcts_player = MCTSPlayer(self.policy_value_net.policy_value_fn,
                                  c_puct = self.c_puct,
                                  n_playout = self.n_playout,
                                  is_selfplay = 0)

  def play():
    self.game.start_play(player2_fn = self.mcts_player.get_action)

if __name__ == '__main__':
  play = PlayGomoku("current_policy.model")
  play.game.player1_fn = play.mcts_player.get_action
  play.game.player1_args = {"board": play.board, "temp": 1e-3, "return_prob": 0}
  play.game.player2_fn = play.mcts_player.get_action
  play.game.player2_args = {"board": play.board, "temp": 1e-3, "return_prob": 0}
  play.game.start_play(output_fn = play.game.graphic)