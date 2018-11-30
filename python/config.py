class GomokuConfig(object):
	def __init__(self):
		# Gomoku params
		self.board_width = 15
		self.board_height = 15
		self.n_to_win = 5
		self.use_forbidden = True

		self.dirichlet = 0.05

		self.learn_rate = 2e-4
		self.lr_multiplier = 1.0
		self.temp = 1.0
		self.n_playout = 2000
		self.n_playout_play = 8000
		self.c_puct = 5
		self.buffer_size = 10000
		self.batch_size = 512
		self.play_batch_size = 1
		self.epochs = 5
		self.kl_targ = 0.01
		self.check_freq = 50
		self.game_batch_num = 15000
		self.model_dir = './'
		self.model_name = 'current_policy.model'
		self.model_path = self.model_dir + self.model_name
