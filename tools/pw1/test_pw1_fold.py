import os
import sys
import tempfile
import unittest

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import pw1_fold as F  # noqa: E402


class HandWorked(unittest.TestCase):
    def test_five_residuals(self):
        # var0=0
        # r=10:  (100-0)>>4      = 6     -> 6
        # r=0:   (0-6)>>4        = -1    -> 5    (floor shift of a negative)
        # r=20:  (400-5)>>4      = 24    -> 29
        # r=5:   (25-29)>>4      = -1    -> 28
        # r=255: (65025-28)>>4   = 4062  -> 4090
        # pi = 255*8192 // (8192+4090) = 2088960 // 12282 = 170
        rs = [10, 0, 20, 5, 255]
        self.assertEqual(F.fold_var(rs), 4090)
        self.assertEqual(F.pi_from_var(4090), 170)
        # plain mean r^2 = (100+0+400+25+65025)//5 = 13110 -> 2088960 // 21302 = 98
        self.assertEqual(F.pi_mean(rs), 98)


def _write(d, name, text):
    p = os.path.join(d, name)
    with open(p, 'w', encoding='utf-8') as fh:
        fh.write(text)


def _rec(lane, lon, body):
    return '@LAT%dLON%d | created:0 | updated:0 | relates:x@LAT0LON0\n\n%s\n\n---\n\n' % (lane, lon, body)


class Lanes(unittest.TestCase):
    def run_series(self, name, text):
        with tempfile.TemporaryDirectory() as d:
            _write(d, name, text)
            return F.load_archive(d)

    def test_acoustic(self):
        s, _ = self.run_series('node_1.md',
            _rec(94, 0, '**ACOUSTICWIN** t_ms:60000 stream:0xaa\n**ACOUSTIC** rms_mean:1000 rms_max:1 peak:1') +
            _rec(94, 1, '**ACOUSTICWIN** t_ms:120000 stream:0xaa\n**ACOUSTIC** rms_mean:2000 rms_max:1 peak:1'))
        self.assertEqual(s[('node', 'acoustic')]['exp'], [1000 * 255 // 32767])

    def test_motion_run_expanded(self):
        s, _ = self.run_series('node_1.md',
            _rec(95, 0, '**MOTIONWIN** t_ms:60000 stream:0xaa\n**MOTION** state:still dev_mean_mg:10\n**RUN** windows_since_last:1 reason:first max_run:30') +
            _rec(95, 1, '**MOTIONWIN** t_ms:300000 stream:0xaa\n**MOTION** state:still dev_mean_mg:1610\n**RUN** windows_since_last:4 reason:changed max_run:30'))
        v = s[('node', 'motion')]
        self.assertEqual(v['exp'], [0, 0, 0, 1600 * 255 // 16000])   # n=4 -> 3 zeros
        self.assertEqual(v['unexp'], [1600 * 255 // 16000])

    def test_entity_jaccard(self):
        e = lambda ids: '\n'.join('**ENTITY** kind:wifi_ap id:%s n:1 rssi:-50' % i for i in ids)
        s, _ = self.run_series('node_1.md',
            _rec(96, 0, '**ENTWIN** t_ms:1000 stream:0xaa\n' + e(['aa', 'bb'])) +
            _rec(96, 1, '**ENTWIN** t_ms:2000 stream:0xaa\n' + e(['bb', 'cc'])))
        self.assertEqual(s[('node', 'entity')]['exp'], [255 * 2 // 3])   # |U|=3, |I|=1

    def test_link_pooled_and_belief_push_excluded(self):
        l = lambda a, b: ('**LINKWIN** t_ms:%d stream:0xaa\n' % a) + \
            '**LINK** peer:0x1 proto:ble n:5 rssi_min:-1 rssi_med:%d rssi_max:-1' % b
        s, log = self.run_series('node_1.md',
            _rec(97, 0, l(1000, -80)) + _rec(97, 1, l(2000, -60)) +
            _rec(97, 2, '**BELIEF-PUSH** id:1 node:k10_1 bytes:9 crc:1'))
        self.assertEqual(s[('node', 'link')]['exp'], [20 * 255 // 100])
        self.assertEqual(sum(log['excluded'].values()), 1)

    def test_dedup_and_stream_break(self):
        a = _rec(94, 0, '**ACOUSTICWIN** t_ms:60000 stream:0xaa\n**ACOUSTIC** rms_mean:100 rms_max:1 peak:1')
        b = _rec(94, 1, '**ACOUSTICWIN** t_ms:60000 stream:0xbb\n**ACOUSTIC** rms_mean:30000 rms_max:1 peak:1')
        with tempfile.TemporaryDirectory() as d:
            _write(d, 'n_1.md', a + b)
            _write(d, 'n_2.md', a)           # duplicate of a record in n_1
            s, log = F.load_archive(d)
        self.assertEqual(sum(log['dups'].values()), 1)
        self.assertEqual(s[('n', 'acoustic')]['exp'], [])    # never across two streams

    def test_lane_101_never_parsed(self):
        with tempfile.TemporaryDirectory() as d:
            _write(d, 'n_1.md', _rec(101, 0, '**FIELD** t_ms:1 stream:0xaa'))
            s, log = F.load_archive(d)
        self.assertEqual(s, {})
        self.assertEqual(sum(log['records'].values()), 0)


if __name__ == '__main__':
    unittest.main()
