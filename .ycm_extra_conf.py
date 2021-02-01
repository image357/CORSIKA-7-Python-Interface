import subprocess
import os

def get_cpp_flags():
    flags = []
    flags += get_root_flags()
    flags += get_coast_flags()
    flags += get_python_flags()
    flags += get_default_flags()

    return [i for i in flags if i]


def get_python_sys_path():
    sys_path = [
            os.path.join(os.environ["COAST_USER_LIB"], "python", "packages"),
    ]

    return [i for i in sys_path if i]


def Settings(**kwargs):
    language = kwargs["language"]

    if language == "cfamily":
        return {
                "flags": get_cpp_flags(),
        }

    if language == "python":
        return {
                "interpreter_path": "python3",
                "sys_path": get_python_sys_path(),
        }

    return {}


def get_root_flags():
    flags = []

    retval = subprocess.check_output(["root-config", "--cflags"])[:-1]
    flags += retval.decode("utf8").split(" ")

    retval = subprocess.check_output(["root-config", "--ldflags"])[:-1]
    flags += retval.decode("utf8").split(" ")

    retval = subprocess.check_output(["root-config", "--libs"])[:-1]
    flags += retval.decode("utf8").split(" ")

    return flags


def get_coast_flags():
    flags = []

    coast_dir = os.environ["COAST_DIR"]
    flags += [
            "-I" + coast_dir + "/include",
    ]
    flags += [
            "-L" + coast_dir + "/lib",
            "-lCorsikaIntern",
            "-lCorsikaFileIO",
            "-lCorsikaROOT",
            "-lCorsikaToROOT",
    ]

    return flags


def get_python_flags():
    flags = ["-D USE_PYTHON_INTERFACE"]

    retval = subprocess.check_output(["python3-config", "--cflags"])[:-1]
    flags += retval.decode("utf8").split(" ")

    retval = subprocess.check_output(["python3-config", "--ldflags"])[:-1]
    flags += retval.decode("utf8").split(" ")

    retval = subprocess.check_output(["python3-config", "--libs"])[:-1]
    flags += retval.decode("utf8").split(" ")

    return flags


def get_default_flags():
    flags = [
            "-x",
            "c++",
            "-std=c++17",
            "-stdlib=libc++",
            "-Wall",
            "-Wextra",
            "-D EXPERIMENTAL_FILESYSTEM",
    ]

    return flags

