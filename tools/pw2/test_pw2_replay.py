import os
import sys
import unittest

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import pw2_constants as C  # noqa: E402
import pw2_replay as R     # noqa: E402


class Rules(unittest.TestCase):
    def test_fixed_flips_on_every_contradiction(self):
        b = R.Belief(); b.body = 10; b.conf = 200
        self.assertEqual(R.update_fixed(b, 99, 100), (True, True))
        self.assertEqual((b.body, b.rev, b.conf), (99, 1, 184))

    def test_gain_cannot_revise_above_152_in_one_step(self):
        for conf in range(152, 256):
            b = R.Belief(); b.body = 10; b.conf = conf
            flipped, _ = R.update_gain(b, 99, 200, 255)
            self.assertFalse(flipped, conf)
            self.assertTrue(b.flag)

    def test_gain_revises_a_weak_belief(self):
        b = R.Belief(); b.body = 10; b.conf = 40
        self.assertTrue(R.update_gain(b, 99, 200, 255)[0])   # K = 255*255//295 = 220
        self.assertEqual((b.body, b.conf, b.rev), (99, 127, 1))

    def test_gain_corroboration(self):
        b = R.Belief(); b.body = 10; b.conf = 100
        R.update_gain(b, 10, 0, 200)
        self.assertEqual(b.conf, 100 + (155 * 200) // 510)


class WorkspaceTests(unittest.TestCase):
    def test_ignite_capacity_and_decay(self):
        ws = R.Workspace()
        ws.offer('a', 50, 0)
        self.assertEqual(ws.t, {})                       # below theta_ign
        for i in range(C.WORKSPACE_W):
            ws.offer('t%d' % i, 200, 0)
        ws.offer('x', 150, 0)                            # full, weaker than every trace
        self.assertNotIn('x', ws.t)
        ws.offer('y', 250, 0)                            # stronger: reclaims one
        self.assertIn('y', ws.t)
        ws.offer('z', 0, 4 * C.WORKSPACE_HALF_LIFE_MS)   # everything decayed below theta_off
        self.assertEqual(ws.t, {})


class Replay(unittest.TestCase):
    def series(self):
        # 200 windows of a steady level, then a persistent step
        return {('n', 'motion', ''): [[100] * 200 + [9000] * 50]}

    def test_workspace_does_not_change_store(self):
        s = self.series()
        for rule in ('fixed', 'gain'):
            for inj in (False, True):
                off, _ = R.run_all(s, rule, inj, False)
                on, _ = R.run_all(s, rule, inj, True)
                self.assertEqual(R.store_hash(off), R.store_hash(on))

    def test_canary_misuse_changes_the_update(self):
        ws = R.Workspace(); ws.t['k'] = [200, 0]
        plain = R.Belief(); plain.body = 10; plain.conf = 100
        canary = R.Belief(); canary.body = 10; canary.conf = 100
        self.assertFalse(R.update_gain(plain, 99, 200, 120, ws, False, 'k')[0])
        self.assertTrue(R.update_gain(canary, 99, 200, 120, ws, True, 'k')[0])

    def test_gain_follows_genuine_step_and_flips_less_under_noise(self):
        s = self.series()
        fx, _ = R.run_all(s, 'fixed', True, False)
        gn, _ = R.run_all(s, 'gain', True, False)
        k = 'n|motion|'
        self.assertGreater(fx[k]['final'][2], gn[k]['final'][2])
        g0, _ = R.run_all(s, 'gain', False, False)
        self.assertEqual(g0[k]['final'][0], 9000)        # followed the real step

    def test_noise_deterministic(self):
        s = self.series()
        a, _ = R.run_all(s, 'gain', True, False)
        b, _ = R.run_all(s, 'gain', True, False)
        self.assertEqual(R.store_hash(a), R.store_hash(b))


if __name__ == '__main__':
    unittest.main()
