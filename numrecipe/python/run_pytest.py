import sys
import pytest
import os


if __name__ == "__main__":
    sys.exit(pytest.main([
        "--cov=numrecipe",
        "--cov-report=xml",
        "--cov-report=html",
        os.path.join("numrecipe", "python"),
    ]))
