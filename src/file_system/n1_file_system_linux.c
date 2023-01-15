#include <sys/stat.h>
#include <fcntl.h>  //open
#include <unistd.h> //read

FileContent read_entire_file(const char* file_path, n1_Allocator allocator){
  
  FileContent file_content = {0, 0};

  int file = open(file_path, O_RDONLY);

  if(file != -1){
    struct stat file_stat;
    int error = stat(file_path, &file_stat);

    if(error){
      return file_content;
    }
      
    file_content.size = file_stat.st_size;
    file_content.data = allocator.alloc(file_content.size + 1);
            
    read(file, file_content.data, file_content.size);
    ((char*)file_content.data)[file_content.size] = 0;
    close(file);
  }
  
  return file_content;
}
