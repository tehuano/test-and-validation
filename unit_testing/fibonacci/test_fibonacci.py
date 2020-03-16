"""
high level support for doing this and that.
"""
import unittest
from fibonacci import fibonacci
from math import pi

class TestFibonacciFibonacci(unittest.TestCase):
    """
    high level support for doing this and that.
    """
    def test_types(self):
        """
        high level support for doing this and that.
        """
        self.assertRaises(TypeError, fibonacci, 3 + 5j)
        self.assertRaises(TypeError, fibonacci, "Fibo")
        self.assertRaises(TypeError, fibonacci, True)
    def test_values(self):
        """
        high level support for doing this and that.
        """
        #self.assertAlmostEqual(fibonacci(83), [99194853094755497,True])
        self.assertEqual(fibonacci(43), [433494437, True])
        self.assertEqual(fibonacci(29), [514229, True])
        self.assertEqual(fibonacci(0), [0, False])
    def test_llimits(self):
        """
        high level support for doing this and that.
        """
        self.assertRaises(ValueError, fibonacci, -1)

if __name__ == '__main__':
    unittest.main()
