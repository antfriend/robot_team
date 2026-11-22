"""Tests for PW-1b (synthetic records only; nothing here reads master/).

    python -m unittest tools/pw1b/test_pw1b_run.py      (or run this file)
"""
import os
import sys
import tempfile
import unittest

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import pw1b_run as R      # noqa: E402
import pw1b_constants as B  # noqa: E402

F, K = R.F, R.F.K


def _rec(lane, lon, body):
    return '@LAT%dLON%d | created:0 | updated:0 | relates:x@LAT0LON0\n\n%s\n\n---\n\n' % (lane, lon, body)


def _load(text):
    with tempfile.TemporaryDirectory() as d:
        with open(os.path.join(d, 'node_1.md'), 'w', encoding='utf-8') as fh:
            fh.write(text)
        return F.load_archive(d)


class Spans(unittest.TestCase):
    def setUp(self):
        self.saved = (K.PE_SPAN_ACOUSTIC, K.PE_SPAN_MOTION, K.PE_SPAN_LINK)

    def tearDown(self):
        K.PE_SPAN_ACOUSTIC, K.PE_SPAN_MOTION, K.PE_SPAN_LINK = self.saved

    def test_constants_are_the_registered_ones(self):
        # Pinned so an edit to pw1b_constants.py after registration fails loudly.
        self.assertEqual((B.PE_SPAN_ACOUSTIC, B.PE_SPAN_MOTION, B.PE_SPAN_LINK), (900, 60, 90))
        self.assertEqual((B.SATURATED_AT, B.DISTINCT_BY), (247, 24))

    def test_apply_spans_returns_pw1_values_and_leaves_the_rest(self):
        before = {k: getattr(K, k) for k in dir(K) if k.isupper() and not k.startswith('PE_SPAN')}
        old = R.apply_spans()
        self.assertEqual(old, (32767, 16000, 100))
        self.assertEqual((K.PE_SPAN_ACOUSTIC, K.PE_SPAN_MOTION, K.PE_SPAN_LINK), (900, 60, 90))
        after = {k: getattr(K, k) for k in dir(K) if k.isupper() and not k.startswith('PE_SPAN')}
        self.assertEqual(before, after)       # PI_SCALE, thresholds, lanes: untouched

    def test_pw1_parser_uses_the_new_spans(self):
        R.apply_spans()
        s, _ = _load(
            _rec(94, 0, '**ACOUSTICWIN** t_ms:60000 stream:0xaa\n**ACOUSTIC** rms_mean:1000 rms_max:1 peak:1') +
            _rec(94, 1, '**ACOUSTICWIN** t_ms:120000 stream:0xaa\n**ACOUSTIC** rms_mean:1300 rms_max:1 peak:1') +
            _rec(95, 0, '**MOTIONWIN** t_ms:60000 stream:0xaa\n**MOTION** state:still dev_mean_mg:8') +
            _rec(95, 1, '**MOTIONWIN** t_ms:120000 stream:0xaa\n**MOTION** state:still dev_mean_mg:20') +
            _rec(97, 0, '**LINKWIN** t_ms:1000 stream:0xaa\n**LINK** peer:0x1 proto:ble n:5 rssi_min:-1 rssi_med:-80 rssi_max:-1') +
            _rec(97, 1, '**LINKWIN** t_ms:2000 stream:0xaa\n**LINK** peer:0x1 proto:ble n:5 rssi_min:-1 rssi_med:-71 rssi_max:-1'))
        self.assertEqual(s[('node', 'acoustic')]['exp'], [300 * 255 // 900])    # 85
        self.assertEqual(s[('node', 'motion')]['exp'], [12 * 255 // 60])       # 51
        self.assertEqual(s[('node', 'link')]['exp'], [9 * 255 // 90])          # 25

    def test_change_beyond_span_clamps_to_255(self):
        R.apply_spans()
        s, _ = _load(
            _rec(95, 0, '**MOTIONWIN** t_ms:60000 stream:0xaa\n**MOTION** state:moving dev_mean_mg:10') +
            _rec(95, 1, '**MOTIONWIN** t_ms:120000 stream:0xaa\n**MOTION** state:moving dev_mean_mg:500'))
        self.assertEqual(s[('node', 'motion')]['exp'], [255])


class Q6(unittest.TestCase):
    def fake(self, m):
        return {'median': {K.PI_SCALE: m}}

    def test_threshold_is_inclusive_at_247(self):
        r = R.q6(self.fake({'acoustic': 247, 'motion': 246, 'link': 255}))
        self.assertTrue(r['acoustic'][1])
        self.assertFalse(r['motion'][1])
        self.assertEqual(r['motion'][2], "PW-1's span was too wide for this channel")
        self.assertEqual(r['link'][2], 'quiet at its declared scale')

    def test_missing_channel_is_none_not_saturated(self):
        self.assertIsNone(R.q6(self.fake({'link': 250}))['acoustic'])

    def test_distinct_pairs(self):
        d = R.distinct_pairs(self.fake({'acoustic': 200, 'motion': 225, 'link': 224, 'entity': 10}))
        self.assertEqual([(a, b, x) for a, b, x, _ in d],
                         [('acoustic', 'motion', True), ('acoustic', 'link', False),
                          ('motion', 'link', False)])      # entity is not one of the three


class EndToEnd(unittest.TestCase):
    def tearDown(self):
        K.PE_SPAN_ACOUSTIC, K.PE_SPAN_MOTION, K.PE_SPAN_LINK = 32767, 16000, 100

    def test_main_writes_a_report_on_a_synthetic_archive(self):
        recs = []
        for i in range(70):   # >= 2 x MIN_RESIDUALS so stability halves exist
            t = 60000 * (i + 1)
            recs.append(_rec(94, i, '**ACOUSTICWIN** t_ms:%d stream:0xaa\n**ACOUSTIC** rms_mean:%d rms_max:1 peak:1'
                             % (t, 1000 + (i % 3) * 200)))
            recs.append(_rec(95, i, '**MOTIONWIN** t_ms:%d stream:0xaa\n**MOTION** state:still dev_mean_mg:%d'
                             % (t, 8 + i % 2)))
            recs.append(_rec(97, i, '**LINKWIN** t_ms:%d stream:0xaa\n**LINK** peer:0x1 proto:ble n:5 '
                             'rssi_min:-1 rssi_med:%d rssi_max:-1' % (t, -70 - (i % 2) * 3)))
        with tempfile.TemporaryDirectory() as d:
            with open(os.path.join(d, 'node_1.md'), 'w', encoding='utf-8') as fh:
                fh.write(''.join(recs))
            out = os.path.join(d, 'r.md')
            self.assertEqual(R.main([d, '--report', out]), 0)
            txt = open(out, encoding='utf-8').read()
        self.assertTrue(txt.startswith('PW-1b: '))
        self.assertIn('## Open question 6', txt)
        for ch in R.SCALARS:
            self.assertIn('| %s | ' % ch, txt)


if __name__ == '__main__':
    unittest.main()
