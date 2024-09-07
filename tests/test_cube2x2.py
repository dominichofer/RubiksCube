import unittest
from rubikscube import Cube2x2


class TestCube2x2(unittest.TestCase):
    def test_solved(self):
        cube = Cube2x2()
        self.assertTrue(cube.is_solved())

        cube.L()
        self.assertFalse(cube.is_solved())

    def test_4L_is_solved(self):
        cube = Cube2x2()
        for _ in range(4):
            cube.L()
        self.assertTrue(cube.is_solved())


if __name__ == "__main__":
    unittest.main()
