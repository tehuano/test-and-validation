import unittest
from volume import volume
from math import pi

class TestVolumeVolume(unittest.TestCase):
    def testTypes(self):
	    self.assertRaises(TypeError, volume, 3 + 5j)
	    self.assertRaises(TypeError, volume, "Radio")
	    self.assertRaises(TypeError, volume, True)
    
    def test_values(self):
        self.assertAlmostEqual(volume(2), 33.510321638291124)
        self.assertAlmostEqual(volume(0), 0)

    def test_llimits(self):
        self.assertRaises(ValueError, volume, -1)

if __name__ == '__main__':
    unittest.main()