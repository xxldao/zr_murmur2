from __future__ import absolute_import
from __future__ import division
from __future__ import print_function
from __future__ import unicode_literals

import inspect
import unittest

import zr_murmur2


def unittest_verbosity():
    """Return the verbosity setting of the currently running unittest
    program, or 0 if none is running.

    """
    frame = inspect.currentframe()
    while frame:
        self = frame.f_locals.get('self')
        if isinstance(self, unittest.TestProgram):
            return self.verbosity
        frame = frame.f_back
    return 0


class TestMurmur2(unittest.TestCase):

    def test_hash32n_seed_0(self):
        tests = [
            ("2e600bad-026a-4258-ba1d-bab4a1517057", 905537245,  12663884967105887186, 0),
            ("e0ecd024-3ec4-40f7-a32b-ec2f00eff363", 3607209597,  3120769584583207945, 0),
            ("7ad601ce-a502-43be-aa2a-affb64023f98", 3252205157,  4502774551569173743, 0),
            ("7eddc716-ef9e-4e79-8cb4-72ee7e436544", 2510473605,  4384643139622357124, 0),
            ("3fb3866a-56b6-4583-a553-a6e0d2c99c35", 2304971705,  2811045690476767142, 0),
            ("190d52d9-5c2b-4a6d-be2d-8505e36ff8f1", 1030520654, 12692695311468879749, 0),
            ("6e99cab1-1572-40e1-a5cb-43f66fe8be25", 1828794305,  8909722122948793137, 0),
            ("7564f454-e4ba-49a4-b4c3-dc3dad5a1a84", 2998747286, 15063865511914197403, 0),
            ("4d1d9fb7-bc3b-4cc1-a84f-73efd6aa4868", 2000265019, 10725163274303152332, 0),
            ("1b5e450c-a5ef-4da1-a922-9ba6bb6be07f", 2830422493, 15584511931482467118, 0),
        ]                                                                              

        verbosity = unittest_verbosity()
        if verbosity > 0:
            print()

        for str_, hash32n, hash64b, seed in tests:
            if verbosity > 1:
                print("Testing hash_32n and hash_64b of", str_)

            self.assertEqual(zr_murmur2.hash_32n(str_, seed), hash32n)
            self.assertEqual(zr_murmur2.hash_32n(str_.encode('utf-8')), hash32n)
            # assert murmur2.murmur64a(str_, len(str_), seed) == hash64b
            self.assertEqual(zr_murmur2.hash_64b(str_, seed), hash64b)


if __name__ == '__main__':
    unittest.main()
