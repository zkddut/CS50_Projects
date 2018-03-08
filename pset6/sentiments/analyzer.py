import nltk

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize Analyzer."""
        self.d_pos = []
        self.d_neg = []
        with open(positives) as f_p:
            for line in f_p:
                if line[0] != ";":
                    self.d_pos.append(line[:-1]);

        with open(negatives) as f_n:
            for line in f_n:
                if line[0] != ";":
                    self.d_neg.append(line[:-1]);


    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""
        total_score = 0
        tokenizer = nltk.tokenize.TweetTokenizer()
        tokens = tokenizer.tokenize(text)
        for word in tokens:
            if (word in self.d_pos):
                total_score += 1
            elif (word in self.d_neg):
                total_score -= 1
        return total_score