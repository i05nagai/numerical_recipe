import sys
import pytest
import os


if __name__ == "__main__":
    print(os.listdir())
    print(os.listdir("numrecipe/python"))
    sys.exit(pytest.main([os.path.join("numrecipe", "python")]))
