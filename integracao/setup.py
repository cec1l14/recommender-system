from setuptools import setup
from pybind11.setup_helpers import Pybind11Extension, build_ext

ext_modules = [
    Pybind11Extension(
        "meu_solver",
        ["solver.cpp", "../src/similaridade.cpp", "../src/recomendacao.cpp", "../src/similaridadeCsr.cpp"], 
        include_dirs=["../src"],
        cxx_std=17,
    )
]

setup(
    name="meu_solver",
    version="0.1.0",
    description="Sistema de Recomendação",
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
    zip_safe=False,
)