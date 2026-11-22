import os
import sys
import unittest

HERE = os.path.dirname(os.path.abspath(__file__))
for sub in ('', '..\\pw2', '..\\pw1'):
    sys.path.insert(0, os.path.normpath(os.path.join(HERE, sub)))
import pw3_constants as C3  # noqa: E402
import pw3_replay as R      # noqa: E402


def rec(v, nbytes=100):
    return {'items': {'': v}, 'bytes': nbytes}


class Bytes(unittest.TestCase):
    def test_percept_frames(self):
        self.assertEqual(R.percept_bytes(100), 100 + 41)
        self.assertEqual(R.percept_bytes(208), 208 + 41)
        self.assertEqual(R.percept_bytes(209), 209 + 82)       # splits into two frames
        self.assertEqual(C3.SALIENT_FRAME, 53)


class Gate(unittest.TestCase):
    def test_steady_series_transmits_only_first_record(self):
        r = R.replay('motion', [[rec(100) for _ in range(50)]], 96)
        self.assertEqual(r['tx'], 1)
        self.assertEqual(r['gate'][''].body, 100)
        self.assertLess(r['bytes_gate'], r['bytes_full'] / 10)

    def test_big_jump_is_transmitted_and_receiver_follows(self):
        # pi defaults to 128, so eps = pe*128//255; pe=255 -> 128 >= 96 transmits
        segs = [[rec(0) for _ in range(5)] + [rec(16000)] + [rec(16000) for _ in range(5)]]
        r = R.replay('motion', segs, 96)
        self.assertGreaterEqual(r['tx'], 2)
        self.assertEqual(r['full'][''].body, r['gate'][''].body)

    def test_small_drift_is_not_transmitted_and_receiver_stays_stale(self):
        segs = [[rec(1000 + i) for i in range(40)]]
        r = R.replay('motion', segs, 96)
        self.assertEqual(r['tx'], 1)
        self.assertTrue(R.agree('motion', r['gate'][''], r['full']['']))   # drift stays within pe_agree

    def test_unfounded_receiver_counts_as_disagreement(self):
        self.assertFalse(R.agree('motion', None, R.R2.Belief()))


class Verdict(unittest.TestCase):
    def test_rules(self):
        c = lambda **k: dict({'beliefs': 50, 'disagree_rate': 0.0, 'fall': 0.5}, **k)
        self.assertEqual(R.verdict(c()), 'PASS')
        self.assertEqual(R.verdict(c(disagree_rate=0.06)), 'KILL')
        self.assertEqual(R.verdict(c(fall=0.29)), 'KILL')
        self.assertEqual(R.verdict(c(beliefs=10)), 'INCONCLUSIVE')


if __name__ == '__main__':
    unittest.main()
