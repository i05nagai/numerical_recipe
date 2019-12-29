import fnmatch
import os
import re

import setuptools
from setuptools.command.install import install as InstallCommandBase
from distutils.command.install_headers import install_headers as InstallHeadersBase
from setuptools.dist import Distribution


class BinaryDistribution(Distribution):

    def has_ext_modules(self):
        return True


class InstallCommand(InstallCommandBase):
    """Override the dir where the headers go."""

    def finalize_options(self):
        ret = InstallCommandBase.finalize_options(self)
        # self.install_headers = os.path.join(self.install_purelib, 'recipe', 'include')
        # self.install_lib = self.install_platlib
        return ret


class InstallHeaders(InstallHeadersBase):
    """Override how headers are copied.

    The install_headers that comes with setuptools copies all files to
    the same directory. But we need the files to be in a specific directory
    hierarchy for -I <include_dir> to work correctly.
    """

    def mkdir_and_copy_file(self, header):
        install_dir = os.path.join(self.install_dir, os.path.dirname(header))
        # Get rid of some extra intervening directories so we can have fewer
        # directories for -I
        install_dir = re.sub('/google/protobuf_archive/src', '', install_dir)

        external_header_locations = [
        ]
        for location in external_header_locations:
            if location in install_dir:
                extra_dir = install_dir.replace(location, '')
            if not os.path.exists(extra_dir):
                self.mkpath(extra_dir)
            self.copy_file(header, extra_dir)

        if not os.path.exists(install_dir):
            self.mkpath(install_dir)
        return self.copy_file(header, install_dir)

    def run(self):
        hdrs = self.distribution.headers
        if not hdrs:
            return

        self.mkpath(self.install_dir)
        for header in hdrs:
            (out, _) = self.mkdir_and_copy_file(header)
            self.outfiles.append(out)


def find_files(pattern, root):
    """Return all the files matching pattern below root dir."""
    for dirpath, _, files in os.walk(root):
        for filename in fnmatch.filter(files, pattern):
            yield os.path.join(dirpath, filename)


def _package_data():
    so_lib_paths = [
        i for i in os.listdir('.')
        if os.path.isdir(i) and fnmatch.fnmatch(i, '_solib_*')
    ]

    matches = []
    for path in so_lib_paths:
        matches.extend(
            ['./' + x for x in find_files('*', path) if '.py' not in x]
        )
    EXTENSION_NAME = 'recipe/python/_pywrap_recipe.so'
    return matches + [
        EXTENSION_NAME
    ]


def main():
    headers = (
        list(find_files('*', 'third_party/eigen3'))
    )
    print(headers)
    print(setuptools.find_packages())
    print(_package_data())

    setuptools.setup(
        name="recipe",
        version="0.0.1.dev0",
        author="i05nagai",
        author_email="i05nagai.cellphone@gmail.com",
        description="Numerical Recipes",
        long_description="Numerical Recipes.",
        long_description_content_type="text/markdown",
        url="https://github.com/i05nagai/numerical_recipe",
        packages=setuptools.find_packages(),
        python_requires='>=3.6',
        # ext_modules=ext_modules,
        zip_safe=False,
        install_requires=[
        ],
        tests_require=[
            "pytest"
        ],
        include_package_data=True,
        package_data={
            "": _package_data(),
        },
        cmdclass={
            'install_headers': InstallHeaders,
            'install': InstallCommand,
        },
        distclass=BinaryDistribution,
        headers=headers,
        classifiers=[
            'Development Status :: 5 - Production/Stable',
            'Intended Audience :: Developers',
            'Intended Audience :: Education',
            'Intended Audience :: Science/Research',
            'License :: OSI Approved :: Apache Software License',
            'Programming Language :: Python :: 3',
            'Programming Language :: Python :: 3.6',
            'Programming Language :: Python :: 3.7',
            'Topic :: Scientific/Engineering',
            'Topic :: Scientific/Engineering :: Mathematics',
            'Topic :: Scientific/Engineering :: Artificial Intelligence',
            'Topic :: Software Development',
            'Topic :: Software Development :: Libraries',
            'Topic :: Software Development :: Libraries :: Python Modules',
        ],
        license="Apache 2.0",
        keywords="machine learning",
    )


if __name__ == '__main__':
    main()
