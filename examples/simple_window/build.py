import time
start_time = time.time()

project_name     = "simple_window"
output_name      = f"{project_name}.exe"
preprocessor     = ""
warnings         = "/WX"
include_folders  = """
-I ../../src/
-I ../../dependencies/
-I ../../dependencies/GLEW/include/
"""
src              = "src/main.c"
compiler_options = """
/nologo 
/Fo./build/obj/ 
-Zi 

"""
libs             = """
Gdi32.lib
User32.lib
Opengl32.lib
Shlwapi.lib
../../dependencies/GLEW/lib/glew32s.lib
"""
linker_options   = f"/link /OUT:./build/{output_name} /PDB:./build/vc140.pdb"

def print_exit_time():
    global start_time
    end_time = time.time()
    print("time: {:.2f}s".format(end_time - start_time))

import os

# set working directory
os.chdir(os.path.dirname(os.path.realpath(__file__)))
cwd = os.getcwd()

# create build dir
if not os.path.isdir("build"):
    os.makedirs("build", 0o666)

if not os.path.isdir("build/obj"):
    os.makedirs("build/obj/", 0o666)
    
command = f"cl {compiler_options} {warnings} {preprocessor} {include_folders} {src} {libs} {linker_options}".replace('\n', ' ');

print(command);
os.system(command);

print_exit_time()

