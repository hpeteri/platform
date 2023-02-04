#!/usr/bin/env python3

import time
import os
import sys
from dataclasses import dataclass

start_time = time.time()

@dataclass
class CompilerCmdOptions:
    project_name     : str  = "simple_window"
    output_name      : str  = "simple_window"
    cc               : str  = ""
    preprocessor     : str  = ""
    warnings         : str  = ""
    include_folders  : str  = ""
    src              : str  = ""
    compiler_options : str  = ""
    libs             : str  = "" 
    linker_options   : str  = ""
    
    is_os_linux      : bool = False
    is_os_windows    : bool = False
    is_debug         : bool = False
    is_release       : bool = False

def set_src(options : CompilerCmdOptions) -> None:
    options.src += "./src/main.c"

# Set output name based on os
# also set default compiler
def set_output_name(options : CompilerCmdOptions) -> None:
    if sys.platform == "linux":
        options.output_name += ".a"
        options.is_os_linux = True
        
    elif sys.platform == "win32":
        options.output_name   += ".exe"
        options.is_os_windows = True

# ========== RELEASE & DEBUG ==========

# flag as release for when compiler is known
def flag_for_release_options(options : CompilerCmdOptions) -> None:
    
    if options.is_debug:
        print("both debug and release flag set, ignoring later options...")
        
    options.is_release = True

# set release mode flags based on cc
def set_release_options(options : CompilerCmdOptions) -> None:
    
    print("release build")
    
    options.preprocessor +=  "-D RELEASE_BUILD "

    if options.cc == "gcc":
        options.compiler_options += "-O3"
        options.preprocessor += "-s -pipe"
        
# flag as debug for when compiler is known
def flag_for_debug_options(options : CompilerCmdOptions) -> None:

    if options.is_release:
        print("debug and release flag set, ignoring later options...")
        
    options.is_debug = True

# set debug mode flags based on cc
def set_debug_options(options : CompilerCmdOptions) -> None:

    print("debug build")
    
    options.preprocessor += """
    -D DEBUG_BUILD 
    -D SGLR_DEBUG_BUILD 
    """

    if options.cc == "gcc":
        options.compiler_options += "-O0"
        options.preprocessor += "-g -pipe"

    elif options.cc == "cl":
        options.compiler_options += "-O2"

# ========== COMPILER ==========
        
def set_compiler_to_gcc(options : CompilerCmdOptions) -> None:

    options.cc = "gcc"
    
    ## libs
    if options.is_os_linux:
        options.libs += """
        -lX11
        -pthread
        -lGL
        -lm
        ../../dependencies/GLEW/lib/libGLEW.a
        """
    elif options.is_os_windows:
        options.libs += """
        -lGdi32 
        -lUser32 
        -lShlwapi 
        -lOpengl32  
        -lKernel32 
        ../../dependencies/GLEW/lib/glew32s.lib 
        """

    # linker
    options.linker_options += f"-o ./build/{options.output_name}"

    
def set_compiler_to_cl(options : CompilerCmdOptions) -> None:

    options.cc = "cl"
    
    options.compiler_options += """ 
    /nologo 
    /Fo./build/obj/ 
    """
    
    options.libs += """
    Gdi32.lib
    User32.lib
    Shlwapi.lib
    Opengl32.lib
    ../../dependencies/GLEW/lib/glew32s.lib
    """

    # linker
    options.linker_options += f"/link /OUT:./build/{options.output_name} /PDB:./build/vc140.pdb"

# set default compiler based on os if cc is not set
def set_default_compiler(options : CompilerCmdOptions) -> None:

    # compiler is already set
    if options.cc != "":
        return
    
    if options.is_os_linux:
        set_compiler_to_gcc(options)
        
    elif options.is_os_windows:
        set_compiler_to_cl(options)


# ========== INCLUDE ==========

# gcc and cl use same include syntax, but maybe we should be more specific
def set_include_folders(options : CompilerCmdOptions) -> None:
    
    options.include_folders += """
    -I ../../src/
    -I ../../dependencies/
    -I ../../dependencies/GLEW/include
    """

# ========== WARNING ==========

# set warnings based on cc
def set_warnings(options : CompilerCmdOptions) -> None:
    if options.cc == "gcc":
        options.warnings += """
        -Wformat=2 
        -Wmain 
        -Wparentheses 
        -Wuninitialized
        -Wsign-compare 
        -Werror
        -Wreturn-type
        -Wshadow
        -Wundef
        -Wall
        """
        
    elif options.cl == "cl":
        options.warnings += """
        /WX
        """
        
def set_command_line_options(options : CompilerCmdOptions) -> None:

    set_src(options)
    set_output_name(options)

    all_options = {
        "release" : flag_for_release_options,
        "debug"   : flag_for_debug_options,
        "gcc"     : set_compiler_to_gcc,
        "cl"      : set_compiler_to_cl,        
    }
    
    for arg in sys.argv[1:]:
        try:
            all_options[arg](options)
        except:
            print(f"'{arg}' option not found!")

            
    if options.cc == "":
        set_default_compiler(options)


    if not options.is_release and not options.is_debug:
        options.is_debug = True

    # release mode
    if options.is_release:
        set_release_options(options)

    # debug mode
    elif options.is_debug:
        set_debug_options(options)

    
    set_warnings(options)
    set_include_folders(options)
            
def main(options : CompilerCmdOptions) -> None:
    
    # === set working directory ===
    os.chdir(os.path.dirname(os.path.realpath(__file__)))
    
    # === create build dirs ===
    if not os.path.isdir("build"):
        os.makedirs("build", 0o777)

    if not os.path.isdir("build/obj"):
        os.makedirs("build/obj/", 0o777)
    
    # === build and link ===
    command = f"""{options.cc} 
                  {options.compiler_options} 
                  {options.warnings} 
                  {options.preprocessor} 
                  {options.include_folders}
                  {options.src}
                  {options.libs} 
                  {options.linker_options}
                  """.replace('\n', ' ')
    command = " ".join(command.split())
    
    print(command)
    os.system(command)
    
    print_exit_time()

def print_exit_time():
    end_time = time.time()
    print("time: {:.2f}s".format(end_time - start_time))

if __name__ == "__main__":
    
    ops = CompilerCmdOptions()

    set_command_line_options(ops)
    main(ops)

    
