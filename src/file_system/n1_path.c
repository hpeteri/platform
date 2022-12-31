#include "n1_path.h"
#include <unistd.h>
#include <linux/limits.h>
#include <libgen.h>

const char* get_cwd(){
  static char cwd[PATH_MAX];
  getcwd(cwd, PATH_MAX);

  return cwd;
}

void set_cwd(const char* cwd){
  chdir(cwd);
}

const char* get_exe_path(){
  static char exe_path[PATH_MAX];

  if(!exe_path[0]){
    readlink("/proc/self/exe", exe_path, PATH_MAX);
  }

  return exe_path;  
}

const char* get_exe_dir(){
  
  static char exe_dir[PATH_MAX];
  if(!exe_dir[0]){
    const char* exe_path = get_exe_path();

    for(int i = 0; i < PATH_MAX; i++){
      exe_dir[i] = exe_path[i];
      if(exe_dir[i] == 0)
        break;
    }  
    dirname(exe_dir);    
  }
  return exe_dir;
}
